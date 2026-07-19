#pragma once

#include <memory.h>
#include "chip8_structures.h"
#include "chip8_interface.h"


void execute_assig_instruction(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_bcd_instruction(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_bitop_instruction(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_call_instruction(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_cond_instruction(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_const_instruction(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_display_instruction(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_flow_instruction(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_keyop_instruction(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_mem_instruction(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_math_instruction(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_rand_instruction(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_sound_instruction(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

void execute_timer_instruction(Chip8VM* vm, const DecodedOpcode* decoded_opcode);

