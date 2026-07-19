#include "chip8_memory.h"

static void chip8_load_rom(
    Memory* mem, 
    const char* rom_name
){
    assert(rom_name != NULL);
    assert(mem != NULL);
    
    FILE* rom = NULL; 
    if ((rom = fopen(rom_name, "rb")) == NULL){
        fprintf(stderr, "ERROR: Unable to open the ROM named %s\n", rom_name);
        exit(1);
    }

    fseek(rom, 0, SEEK_END);
    mem->rom_size = ftell(rom);

    if (mem->rom_size > MEM_MAX_SIZE - PC_INITIAL_OFFSET){
        fprintf(stderr, "ERROR:The ROM has a size of %i, but should be less than or equal to %i\n", MEM_MAX_SIZE - PC_INITIAL_OFFSET);
        fclose(rom);
        exit(1);
    }

    mem->rom = calloc(mem->rom_size, sizeof(byte));

    fseek(rom, 0, SEEK_SET);
    fread(
        mem->rom,  
        mem->rom_size, 
        sizeof(byte),
        rom
    );

    fclose(rom);
}

void chip8_memory_destroy(
    Memory* mem
){
    assert(mem != NULL);
    free(mem->rom);
}

Memory chip8_memory_construct(
    const char* rom_name
){
    assert(rom_name != NULL);

    Memory mem = {
        .fontset = {
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
        }
    };

    chip8_load_rom(&mem, rom_name);

    mem.write = chip8_memory_write;
    mem.read = chip8_memory_read;
    
    return mem;
}

byte chip8_memory_read(
    Memory* mem, 
    const addr address
){
    assert(mem != NULL);
    assert(address < mem->rom_size + PC_INITIAL_OFFSET);

    if (
        address >= FONTSET_INITIAL_OFFSET && 
        address < FONTSET_INITIAL_OFFSET + sizeof(mem->fontset)
    )
        return mem->fontset[address - FONTSET_INITIAL_OFFSET];
    
    return mem->rom[address - PC_INITIAL_OFFSET];
}

void chip8_memory_write(
    Memory* mem, 
    const addr address, 
    const byte bt
){
    assert(mem != NULL);
    assert(address < mem->rom_size + PC_INITIAL_OFFSET);

    if (
        address >= FONTSET_INITIAL_OFFSET && 
        address < FONTSET_INITIAL_OFFSET + sizeof(mem->fontset)
    ){
        mem->fontset[address - FONTSET_INITIAL_OFFSET] = bt;
        return;
    }

    mem->rom[address - PC_INITIAL_OFFSET] = bt;
}


