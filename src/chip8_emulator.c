#include "chip8_emulator.h"

void chip8_run(
    const char* rom_name
){
    assert(rom_name != NULL);

    Chip8VM vm = chip8_vm_construct();

    chip8_load_rom(rom_name, &vm);

    const void** opcode_map = chip8_decoder_dispatcher();


    char **instructions_alias = chip8_load_instructions(
            vm.memory, 
            MEM_SIZE, 
            (const void (**)(const addr*, DecodedOpcode*))opcode_map
        );

    memcpy(
        vm.instructions_alias, 
        instructions_alias, 
        ((MEM_SIZE - PC_INITIAL_OFFSET) * 50) * sizeof(char)
    );

    free(instructions_alias);

    chip8_construct_display();

    while(!WindowShouldClose()){
        chip8_emulate_cycle(&vm, (const void (**)(const addr*, DecodedOpcode*))opcode_map);
    }

    chip8_destroy_display();
}

static void chip8_load_rom(
    const char* rom_name, 
    Chip8VM* vm
){
    
    assert(rom_name != NULL);
    assert(vm != NULL);
    
    FILE* rom = NULL; 
    if ((rom = fopen(rom_name, "rb")) == NULL){
        fprintf(stderr, "ERROR: Unable to open the ROM named %s\n", rom_name);
        abort();
    }

    fseek(rom, 0, SEEK_END);
    long rom_size = ftell(rom);

    if (rom_size > MEM_SIZE - PC_INITIAL_OFFSET){
        fprintf(stderr, "ERROR:The ROM has a size of %i, but should be less than or equal to %i\n", MEM_SIZE - PC_INITIAL_OFFSET);
        fclose(rom);
        abort();
    }

    fseek(rom, 0, SEEK_SET);
    fread(&vm->memory[PC_INITIAL_OFFSET], sizeof(byte), rom_size, rom);
    fclose(rom);
}

static char** chip8_load_instructions(
    const byte* memory, 
    const size_t memory_size, 
    const void (*decoder_dispatcher[16])(const addr*, DecodedOpcode*)
){

    assert(memory != NULL);
    assert(memory_size > 0);
    assert(decoder_dispatcher != NULL);

    char **instructions = calloc((MEM_SIZE - PC_INITIAL_OFFSET) * 50, sizeof(char));

    for (
        size_t i = PC_INITIAL_OFFSET, offset = 0; 
        i < memory_size - 1; 
        i += 2, offset++ 
    ){
        addr opcode = (addr)((memory[i] << 8) | memory[i + 1]);

        byte opcode_class = (opcode & 0xF000) >> 12;
        void(*opcode_decoder)(const addr*, DecodedOpcode*) = decoder_dispatcher[opcode_class];

        DecodedOpcode decoded_opcode = {0};
        decoded_opcode.decoder_class = (opcode & 0xF000) >> 12;

        (*opcode_decoder)(&opcode, &decoded_opcode);
        strcpy(instructions[offset], decoded_opcode.instruction_alias);
    }

    return instructions;
}

static void chip8_emulate_cycle(
    Chip8VM* vm, 
    const void (*decoder_dispatcher[16])(const addr*, DecodedOpcode*)
){
    assert(vm != NULL);
    assert(decoder_dispatcher);

    if (vm->pc >= MEM_SIZE - 1){
        abort();
    }
    
    addr opcode = (addr)((vm->memory[vm->pc] << 8) | vm->memory[vm->pc + 1]);
    
    vm->pc += 2;

    byte opcode_class = (opcode & 0xF000) >> 12;
    const void(*opcode_decoder)(const addr*, DecodedOpcode*) = decoder_dispatcher[opcode_class];

    assert(opcode_decoder != NULL);

    DecodedOpcode decoded_opcode = {0};
    decoded_opcode.decoder_class = (opcode & 0xF000) >> 12;
   
    opcode_decoder(&opcode, &decoded_opcode);

    decoded_opcode.execute(vm, &decoded_opcode);

    chip8_update_display(vm);

    if (vm->delay_timer > 0) vm->delay_timer -= 1;
    if (vm->sound_timer > 0) vm->sound_timer -= 1;
}

static Chip8VM chip8_vm_construct(){
    Chip8VM vm = {0};

    for(int i = 0; i < sizeof(vm.stack)/sizeof(addr); i++)
        vm.stack[i] = 0;
    for(int i = 0; i < sizeof(vm.keys); i ++)
        vm.keys[i] = 0;
    for(int i = 0; i < sizeof(vm.display); i++)
        vm.display[i] = 0;
    
    vm.I = FONTSET_INITIAL_OFFSET;
    vm.pc = PC_INITIAL_OFFSET;
    byte chip8_fontset[FONTSET_INITIAL_OFFSET] ={
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    for (int i = 0; i < sizeof(chip8_fontset); i++)
        vm.memory[FONTSET_INITIAL_OFFSET + i] = chip8_fontset[i];
    
    return vm;
}
