#pragma once

#include <memory.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include "chip8_structures.h"
#include "chip8_decoder.h"
#include "chip8_interface.h"




void chip8_emulator_run(const char* room_name);

static Chip8VM chip8_vm_construct(const char* rom_name);

static void chip8_vm_destroy(Chip8VM* vm);

static void chip8_emulate_cycle(Chip8VM* vm, void (*opcode_class_dispatcher[16])(const addr*, DecodedOpcode*));

static char** chip8_dissasembler_construct(Memory* mem, void (*opcode_class_dispatcher[16])(const addr*, DecodedOpcode*));

static void chip8_dissasembler_destroy(Chip8VM* vm);

