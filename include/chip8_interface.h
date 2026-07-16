#pragma once

#include "raylib.h"
#include "chip8_structures.h"

static Font font;
static const int DISPLAY_WIDHT  = 1280;
static const int DISPLAY_HEIGHT = 720;


static void chip8_draw_hardware_components(
    const Vector2 pos, 
    const char* name, 
    const char* value,
    const int spacing,
    const Color color,
    const int font_size,
    const int font_spacing
);

static void chip8_draw_display_area(const Chip8VM* vm);

static void chip8_draw_hardware_components_area(const Chip8VM* vm);

static void chip8_draw_memory_line(
    const Vector2 pos,
    const char* instruction, 
    const char* memory_address, 
    const int spacing,
    const Color color,
    const int font_size,
    const int font_spacing
);

static void chip8_draw_memory_area(const Chip8VM* vm);

int chip8_press_key(Chip8VM* vm);

void chip8_update_display(Chip8VM* vm);

inline void chip8_construct_display();

inline void chip8_destroy_display();