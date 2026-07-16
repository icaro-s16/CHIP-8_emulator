#pragma once

#include <memory.h>
#include "chip8_structures.h"
#include "chip8_decoder.h"
#include "chip8_interface.h"



void chip8_run(const char* room_name);

static void chip8_load_rom(const char* room_name, Chip8VM* vm);

static char** chip8_load_instructions(const byte* memory,const size_t memory_size, const void (*opcode_class_dispatcher[16])(const addr*, DecodedOpcode*));

static Chip8VM chip8_vm_construct();

static void chip8_emulate_cycle(Chip8VM* vm, const void (*opcode_class_dispatcher[16])(const addr*, DecodedOpcode*));