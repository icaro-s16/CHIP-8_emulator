#include "chip8_emulator.h"


void chip8_emulator_run(
    const char* rom_name
){
    assert(rom_name != NULL);
        
    Chip8VM vm = chip8_vm_construct(rom_name);  

    void (**decoder_dispatcher)(const addr *, DecodedOpcode *) = (void (**)(const addr *, DecodedOpcode *))chip8_decoder_dispatcher();

    vm.dissasembly = chip8_dissasembler_construct(&vm.memory, decoder_dispatcher);
    
    chip8_construct_display();

    const size_t instruction_per_sec = 700;
    struct timeval last = {0};
    gettimeofday(&last, NULL);
    size_t instruction_counter = 0;
    
    while(!WindowShouldClose()){
        struct timeval now = {0};
        chip8_emulate_cycle(&vm, decoder_dispatcher);
    }

    free(decoder_dispatcher);
    chip8_destroy_display();
    chip8_vm_destroy(&vm);
}

static char** chip8_dissasembler_construct(
    Memory* mem, 
    void (**decoder_dispatcher)(const addr*, DecodedOpcode*)
){  
    assert(mem != NULL);
    assert(decoder_dispatcher != NULL);

    char **dissasembly = calloc(mem->rom_size/2, sizeof(char*));
    for(int i = 0; i < mem->rom_size/2; i++)
        dissasembly[i] = calloc(50, sizeof(char));

    for(
        int pc = 0, offset = 0; 
        pc < mem->rom_size; 
        pc += 2, offset ++
    ){
        addr opcode = (
            (mem->read(mem, pc + PC_INITIAL_OFFSET) << 8) | 
            mem->read(mem, pc + PC_INITIAL_OFFSET + 1)
        );

        byte opcode_class = (opcode & 0xF000) >> 12;
        void(*opcode_decoder)(const addr*, DecodedOpcode*) = decoder_dispatcher[opcode_class];
        assert(opcode_decoder != NULL);

        DecodedOpcode decoded_opcode = {0};
        decoded_opcode.decode_class = (opcode & 0xF000) >> 12;
        
        opcode_decoder(&opcode, &decoded_opcode);
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
    void (*decoder_dispatcher[16])(const addr*, DecodedOpcode*)
){
    assert(vm != NULL);
    assert(decoder_dispatcher != NULL);
    
    addr opcode = (
        (vm->memory.read(&vm->memory, vm->pc) << 8) | 
        vm->memory.read(&vm->memory, vm->pc + 1)
    );
    
    vm->pc += 2;

    if (vm->pc >= vm->memory.rom_size + PC_INITIAL_OFFSET){
        fprintf(stderr, "ERROR: Program counter exceeds available memory limits...\n");
        exit(1);
    }

    byte opcode_class = (opcode & 0xF000) >> 12;
    void(*opcode_decoder)(const addr*, DecodedOpcode*) = decoder_dispatcher[opcode_class];

    DecodedOpcode decoded_opcode = {0};
    decoded_opcode.decode_class = (opcode & 0xF000) >> 12;
   
    opcode_decoder(&opcode, &decoded_opcode);
    decoded_opcode.execute(vm, &decoded_opcode);

    chip8_update_display(vm);

    // TODO: Implement sound

    if (vm->delay_timer > 0) vm->delay_timer -= 1;
    if (vm->sound_timer > 0) vm->sound_timer -= 1;
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
    assert(vm->memory.rom != NULL);
    assert(vm->dissasembly != NULL);
    chip8_dissasembler_destroy(vm);
    chip8_memory_destroy(&vm->memory);
}