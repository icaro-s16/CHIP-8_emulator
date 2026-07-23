#pragma once

#include <memory.h>
#include "chip8_core.h"


int chip8_press_key(Chip8VM* vm);

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

static void execute_err(const DecodedOpcode* decoded_opcode);