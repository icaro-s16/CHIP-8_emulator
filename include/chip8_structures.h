#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define CHIP8_DISPLAY_WIDGHT   64

#define CHIP8_DISPLAY_HEIGHT   32

#define KEYS_SIZE              16

#define MEM_SIZE               4096

#define V_REG_SIZE             16

#define PC_INITIAL_OFFSET      512

#define FONTSET_INITIAL_OFFSET 80

typedef uint8_t byte;

typedef uint16_t addr;

typedef struct Chip8VM Chip8VM;
struct Chip8VM{
    char instructions_alias[MEM_SIZE - PC_INITIAL_OFFSET][50];
    byte memory[MEM_SIZE];                                    // TODO: Change the memory logic to union memory with a struct
    byte display[CHIP8_DISPLAY_HEIGHT * CHIP8_DISPLAY_WIDGHT];
    addr stack[16];
    byte keys[KEYS_SIZE];
    byte V[V_REG_SIZE];
    addr I;
    addr pc;
    byte sp;
    byte delay_timer;
    byte sound_timer;     
};

typedef struct DecodedOpcode DecodedOpcode;
struct DecodedOpcode{
    char instruction_alias[50];
    union{

        addr address;       
        
        struct{
            byte vx; 
            byte vy;
            byte constant;      
        };

    };
    const void (*execute)(Chip8VM*, const DecodedOpcode*);
    byte decoder_class;
};