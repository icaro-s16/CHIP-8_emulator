#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "chip8_memory.h"

typedef uint8_t byte;

typedef uint16_t addr;

typedef struct Chip8VM Chip8VM;
struct Chip8VM{
    char **dissasembly;
    Memory memory;                                   // TODO: Change the memory logic to union memory with a struct
    byte display[CHIP8_DISPLAY_HEIGHT][CHIP8_DISPLAY_WIDGHT];
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
    char mnemonic[50];
    union{

        addr address;       
        
        struct{
            byte vx; 
            byte vy;
            byte constant;      
        };

    };
    void (*execute)(Chip8VM*, const DecodedOpcode*);
    byte decode_class;
};