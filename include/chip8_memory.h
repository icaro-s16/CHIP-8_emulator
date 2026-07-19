#pragma once

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


#define CHIP8_DISPLAY_WIDGHT   64

#define CHIP8_DISPLAY_HEIGHT   32

#define KEYS_SIZE              16

#define MEM_MAX_SIZE               4096

#define V_REG_SIZE             16

#define PC_INITIAL_OFFSET      512

#define FONTSET_INITIAL_OFFSET 80

typedef uint8_t byte;

typedef uint16_t addr;

typedef struct Memory Memory;
struct Memory{
    byte fontset[80];
    size_t rom_size;
    byte *rom;
    byte (*read)(Memory*, const addr);
    void (*write)(Memory*, const addr, const byte);
};

static void chip8_load_rom(Memory* mem, const char* rom_name);

void chip8_memory_destroy(Memory* mem);

Memory chip8_memory_construct(const char* rom_name);

byte chip8_memory_read(Memory* mem, const addr address);

void chip8_memory_write(Memory* mem, const addr address, const byte bt);
