#include "chip8_emulator.h"


static inline ulong sec_to_nsec(
    ulong sec
){
    return sec * 1000000000;
}

static void chip8_sync_execution(
    const struct timespec last, 
    const struct timespec now, 
    const ulong time_per_op
){
    ulong delta = (
        (now.tv_sec * sec_to_nsec(1) + now.tv_nsec) -
        (last.tv_sec * sec_to_nsec(1) + last.tv_nsec)
    );

    if (delta >= time_per_op)
        return;

    struct timespec delta_sleep = {
        .tv_sec = (time_per_op - delta) / sec_to_nsec(1),
        .tv_nsec = (time_per_op - delta) % sec_to_nsec(1) 
    };

    nanosleep(&delta_sleep, NULL);
    
}

void chip8_emulator_run(
    const char* rom_name,
    const ulong op_per_sec
){
    assert(rom_name != NULL);

    srand(time(NULL));
        
    Chip8VM vm = chip8_vm_construct(rom_name);  

    void (**decoder_dispatcher)(const addr, DecodedOpcode *) = (void (**)(const addr , DecodedOpcode *))chip8_decoder_dispatcher();

    vm.dissasembly = chip8_dissasembler_construct(&vm.memory, decoder_dispatcher);
    
    chip8_construct_display();

    size_t time_per_op = sec_to_nsec(1) / op_per_sec; 
    struct timespec last = {0};
    clock_gettime(CLOCK_MONOTONIC, &last);
    
    while(!WindowShouldClose()){
        chip8_emulate_cycle(&vm, decoder_dispatcher);
        
        struct timespec now = {0};
        clock_gettime(CLOCK_MONOTONIC, &now);
        chip8_sync_execution(
            last,
            now,
            time_per_op
        );
        last = now;
    }

    free(decoder_dispatcher);
    chip8_destroy_display();
    chip8_vm_destroy(&vm);
}

static char** chip8_dissasembler_construct(
    Memory* mem, 
    void (**decoder_dispatcher)(const addr, DecodedOpcode*)
){  
    assert(mem != NULL);
    assert(decoder_dispatcher != NULL);

    printf("ASSEMBLY:\n");

    char **dissasembly = calloc(mem->rom_size/2, sizeof(char*));
    for(int i = 0; i < mem->rom_size/2; i++)
        dissasembly[i] = calloc(50, sizeof(char));

    for(
        int pc = PC_INITIAL_OFFSET, offset = 0; 
        pc < mem->rom_size + PC_INITIAL_OFFSET; 
        pc += 2, offset ++
    ){
        addr opcode = (
            (mem->read(mem, pc ) << 8) | 
            mem->read(mem, pc + 1)
        );

        byte opcode_class = (opcode & 0xF000) >> 12;
        void(*opcode_decoder)(const addr, DecodedOpcode*) = decoder_dispatcher[opcode_class];
        assert(opcode_decoder != NULL);

        DecodedOpcode decoded_opcode = {0};
        decoded_opcode.optype= chip8_get_optype(opcode);
        opcode_decoder(opcode, &decoded_opcode);
        
        printf("%s\n", decoded_opcode.mnemonic);

        dissasembly[offset] = calloc(50, sizeof(char));
        strcpy(dissasembly[offset], decoded_opcode.mnemonic);
    }

    return dissasembly;
}

static void chip8_dissasembler_destroy(
    Chip8VM* vm
){
    assert(vm != NULL);
    assert(vm->dissasembly != NULL);

    for(int i = 0; i < vm->memory.rom_size / 2; i ++)
        free(vm->dissasembly[i]);
    
    free(vm->dissasembly);

}

static void chip8_emulate_cycle(
    Chip8VM* vm, 
    void (*decoder_dispatcher[16])(const addr, DecodedOpcode*)
){
    assert(vm != NULL);
    assert(decoder_dispatcher != NULL);
    
    addr opcode = (
        (vm->memory.read(&vm->memory, vm->pc) << 8) | 
        vm->memory.read(&vm->memory, vm->pc + 1)
    );
    
    vm->pc += 2;

    byte opcode_class = (opcode & 0xF000) >> 12;
    void(*opcode_decoder)(const addr, DecodedOpcode*) = decoder_dispatcher[opcode_class];

    DecodedOpcode decoded_opcode = {0};
    decoded_opcode.optype = chip8_get_optype(opcode);
    chip8_set_executer(&decoded_opcode);

    opcode_decoder(opcode, &decoded_opcode);
    decoded_opcode.execute(vm, &decoded_opcode);

    chip8_update_display(vm);

    // TODO: Implement sound

    if (vm->delay_timer > 0) vm->delay_timer -= 1;
    if (vm->sound_timer > 0) vm->sound_timer -= 1;

    if (vm->pc >= MEM_MAX_SIZE){
        fprintf(stderr, "ERROR: Program counter exceeds available memory limits...\n");
        exit(1);
    }
}

static Chip8VM chip8_vm_construct(const char* rom_name){
    assert(rom_name != NULL);

    Chip8VM vm = {0};
    vm.memory = chip8_memory_construct(rom_name);
    vm.pc = PC_INITIAL_OFFSET;
    return vm;
}

static void chip8_vm_destroy(
    Chip8VM* vm
){
    assert(vm != NULL);
    assert(vm->dissasembly != NULL);
    chip8_dissasembler_destroy(vm);
}