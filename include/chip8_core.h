#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "chip8_memory.h"

typedef uint8_t byte;

typedef uint16_t addr;

/*

Instruction type | Opcode

F represent, in some cases, a generic value,
so when you use it with a and bitwise, it ignore
the values, so when can work with just values that
identify the opcode, and ignore those varidical
values, like registers number, constant or addresses 

*/
#define INSTRUCTION_TABLE(X)                        \
    X(CLS, 0x00E0, execute_cls)                     \
    X(RTS, 0x00EE, execute_rts)                     \
    X(CALL, 0x0FFF, execute_call)                   \
    X(JMP, 0x1FFF, execute_jmp)                     \
    X(JSR, 0x2FFF, execute_jsr)                     \
    X(SKEQ_RC, 0x3FFF, execute_skeq_rc)             \
    X(SKNE_RC, 0x4FFF, execute_skne_rc)             \
    X(SKEQ_RR, 0x5FF0, execute_skeq_rr)             \
    X(MOV_RC, 0x6FFF, execute_mov_rc)               \
    X(ADD_RC, 0x7FFF, execute_add_rc)               \
    X(MOV_RR, 0x8FF0, execute_mov_rr)               \
    X(OR_RR, 0x8FF1, execute_or_rr)                 \
    X(AND_RR, 0x8FF2, execute_and_rr)               \
    X(XOR_RR, 0x8FF3, execute_xor_rr)               \
    X(ADD_RR, 0x8FF4, execute_add_rr)               \
    X(SUB_RR, 0x8FF5, execute_sub_rr)               \
    X(SHR, 0x8FF6, execute_shr)                     \
    X(RSB, 0x8FF7, execute_rsb)                     \
    X(SHL, 0x8FFE, execute_shl)                     \
    X(SKNE_RR, 0x9FF0, execute_skne_rr)             \
    X(MVI, 0xAFFF, execute_mvi)                     \
    X(JMI, 0xBFFF, execute_jmi)                     \
    X(RAND, 0xCFFF, execute_rand)                   \
    X(SPRITE, 0xDFFF, execute_sprite)               \
    X(SKPR, 0xEF9E, execute_skpr)                   \
    X(SKUP, 0xEFA1, execute_skup)                   \
    X(GDELAY, 0xFF07, execute_gdelay)               \
    X(KEY, 0xFF0A, execute_key)                     \
    X(SDELAY, 0xFF15, execute_sdelay)               \
    X(SSOUND, 0xFF18, execute_ssound)               \
    X(ADDI, 0xFF1E, execute_addi)                   \
    X(FONT, 0xFF29, execute_font)                   \
    X(BCD, 0xFF33, execute_bcd)                     \
    X(STR, 0xFF55, execute_str)                     \
    X(LDR, 0xFF65, execute_ldr)                  

#define X(name, mask, func) name, 

typedef enum OpType OpType;
enum OpType{
    INSTRUCTION_TABLE(X) 
    RAW  
};

#undef X


typedef struct Chip8VM Chip8VM;
struct Chip8VM{
    char **dissasembly;
    Memory memory;                                              // Done: Change the memory logic
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
    OpType optype;
    union{

        addr address;       
        
        struct{
            byte vx; 
            byte vy;
            byte constant;      
        };

    };
    void (*execute)(Chip8VM*, const DecodedOpcode*);
};

OpType chip8_get_optype(const addr opcode);

void chip8_set_executer(DecodedOpcode* decoded_opcode);


// Foward declaration of the executer functions 

void execute_mov_rr(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_bcd(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_or_rr(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_and_rr(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_xor_rr(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_shr(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_shl(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_call(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_skeq_rc(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_skne_rc(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_skeq_rr(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_skne_rr(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_mov_rc(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_add_rc(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_sprite(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_cls(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_rts(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_jmp(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_jsr(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_jmi(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_skpr(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_skup(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_key(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_addi(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_font(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_str(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_ldr(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_mvi(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_add_rr(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_sub_rr(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_rsb(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_rand(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_ssound(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_gdelay(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_sdelay(Chip8VM* vm, const DecodedOpcode* decoded_opcode);
