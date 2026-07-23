#pragma once

#include <memory.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "chip8_core.h"
#include "chip8_decoder.h"
#include "chip8_interface.h"

static ulong sec_to_nsec(const ulong sec);

static void chip8_sync_execution(const struct timespec last, const struct timespec now, const ulong time_per_op);

void chip8_emulator_run(const char* room_name, const ulong op_per_sec);

static Chip8VM chip8_vm_construct(const char* rom_name);

static void chip8_vm_destroy(Chip8VM* vm);

static void chip8_emulate_cycle(Chip8VM* vm);

static char** chip8_dissasembler_construct(Memory* mem);

static void chip8_dissasembler_destroy(Chip8VM* vm);

