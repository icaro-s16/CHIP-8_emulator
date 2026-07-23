#include "chip8_interface.h"

// TODO: Refac this file

static void chip8_draw_hardware_components(
    const Vector2 pos, 
    const char* name, 
    const char* value,
    const int spacing,
    const Color color,
    const int font_size,
    const int font_spacing
){
    DrawTextEx(
        font,
        name,
        pos,
        font_size,
        font_spacing,
        color
    );
    DrawTextEx(
        font,
        "=",
        (Vector2){
            pos.x + spacing,
            pos.y
        },
        font_size,
        font_spacing,
        color
    );
    DrawTextEx(
        font,
        value,
        (Vector2){
            pos.x + spacing + 25,
            pos.y
        },
        font_size,
        font_spacing,
        color
    );
}


static void chip8_draw_display_area(
    const Chip8VM* vm
){
    const Rectangle chip8_pixel = {
        26,
        28,
        14,
        12,
    };

    DrawTextEx(
        font,
        "Display",
        (Vector2){chip8_pixel.width  + 10,
        chip8_pixel.height - 6},
        18,
        2,
        GREEN
    );

    for(int i = 0; i < CHIP8_DISPLAY_HEIGHT; i++)
        for (int j = 0; j < CHIP8_DISPLAY_WIDGHT; j++)
            DrawRectangle( 
                chip8_pixel.x + j * chip8_pixel.width,
                chip8_pixel.y + i * chip8_pixel.height,
                chip8_pixel.width,
                chip8_pixel.height,
                (vm->display[i][j]) ? GREEN : BLACK
            );

    DrawRectangleLinesEx(
        (Rectangle){chip8_pixel.x - 2,
        chip8_pixel.y - 2,
        chip8_pixel.width * CHIP8_DISPLAY_WIDGHT + 4,
        chip8_pixel.height * CHIP8_DISPLAY_HEIGHT + 4},
        2.0,
        GREEN
    );
}

static void chip8_draw_hardware_components_area(
    const Chip8VM* vm
){
    const Rectangle hardware_components_box = {
        946,
        26,
        312,
        364
    };

  
    DrawTextEx(
            font,
            "Registers | Stack",
            (Vector2){hardware_components_box.x,
            hardware_components_box.y - 20},
            18,
            2,
            GREEN
        );


    int stack_offset = (vm->sp >= 8)? 8 : 0;

    for(int i = 0; i < 16; i ++){
        
        chip8_draw_hardware_components(
            (Vector2){hardware_components_box.x + 10,
            hardware_components_box.y + i * 20 + 20},
            TextFormat("V%X", i),
            TextFormat("0x%.2X", vm->V[i]),
            40,
            GREEN,
            16,
            2
        );

        switch (i)
        {
        case 0:
            chip8_draw_hardware_components(
                (Vector2){hardware_components_box.x + 155,
                hardware_components_box.y + i * 20 + 20},
                "I",
                TextFormat("0x%.4X", vm->I),
                40,
                GREEN,
                16,
                2
            );
            break;
        case 1:
            chip8_draw_hardware_components(
                (Vector2){hardware_components_box.x + 155,
                hardware_components_box.y + i * 20 + 20},
                "PC",
                TextFormat("0x%.4X", vm->pc),
                40,
                GREEN,
                16,
                2
            );
            break;
        case 2:
            chip8_draw_hardware_components(
                (Vector2){hardware_components_box.x + 155,
                hardware_components_box.y + i * 20 + 20},
                "SP",
                TextFormat("0x%.2X", vm->sp),
                40,
                GREEN,
                16,
                2
            );
            break;
        case 4:
            chip8_draw_hardware_components(
                (Vector2){hardware_components_box.x + 155,
                hardware_components_box.y + i * 20 + 20},
                "DT",
                TextFormat("0x%.2X", vm->delay_timer),
                40,
                GREEN,
                16,
                2
            );
            break;
        case 5:
            chip8_draw_hardware_components(
                (Vector2){hardware_components_box.x + 155,
                hardware_components_box.y + i * 20 + 20},
                "ST",
                TextFormat("0x%.2X", vm->sound_timer),
                40,
                GREEN,
                16,
                2
            );
            break;
        default:
            break;
        }

        
        if (i >= 8){
            chip8_draw_hardware_components(
                (Vector2){hardware_components_box.x + 155,
                hardware_components_box.y + i * 20 + 18},
                TextFormat("S%.1X", stack_offset),
                TextFormat("0x%.4X", vm->stack[stack_offset]),
                40,
                GREEN,
                16,
                2
            );
            stack_offset += 1;
        }
        
    }

    DrawRectangleLinesEx(
        hardware_components_box,
        2.0,
        GREEN
    );
}

static void chip8_draw_memory_line(
    const Vector2 pos,
    const char* instruction, 
    const char* memory_address, 
    const int spacing,
    const Color color,
    const int font_size,
    const int font_spacing
){
    DrawTextEx(
        font,
        memory_address,
        pos,
        font_size,
        font_spacing,
        color
    );
    DrawTextEx(
        font,
        "-",
        (Vector2){
            pos.x + spacing,
            pos.y
        },
        font_size,
        font_spacing,
        color
    );
    DrawTextEx(
        font,
        instruction,
        (Vector2){
            pos.x + spacing + 33,
            pos.y
        },
        font_size,
        font_spacing,
        color
    );
}

static void chip8_draw_memory_area(
    const Chip8VM* vm
){
    const Rectangle memory_box = {
        946,
        420,
        312,
        280
    };

    DrawTextEx(
        font,
        "Memory",
        (Vector2){memory_box.x,
        memory_box.y - 20},
        18,
        2,
        GREEN
    );
    
    int mem_offset = (vm->pc - PC_INITIAL_OFFSET)/2;
    
    if (mem_offset > vm->memory.rom_size/2 - 14){
        mem_offset = vm->memory.rom_size/2 - 14;
    }

    for (int text_offset = 0; 
        text_offset < 14; 
        mem_offset ++, text_offset++
    ){
        chip8_draw_memory_line(
            (Vector2){
                memory_box.x + 10,
                memory_box.y + 12 +(text_offset) * 19
            },
            vm->dissasembly[mem_offset],
            TextFormat(
                "0x%.4X", (mem_offset + PC_INITIAL_OFFSET)*2
            ),
            75,
            GREEN,
            12,
            2
        );
    }

    DrawRectangleLinesEx(
        memory_box,
        2.0,
        GREEN
    );
            
}

int chip8_press_key(
    Chip8VM* vm
){
    
    
    if (IsKeyPressed(KEY_KP_1)){
        vm->keys[0] = 1;
        return 1;
    }
    else if (IsKeyDown(KEY_KP_2)){
        vm->keys[1] = 1;
        return 1;
    }
    else if (IsKeyDown(KEY_KP_3)){
        vm->keys[2] = 1;
        return 1;
    }
    else if (IsKeyDown(KEY_KP_4)){
        vm->keys[3] = 1;
        return 1;
    }
    else if (IsKeyDown(KEY_Q)){
        vm->keys[4] = 1;
        return 1;
    }
    else if (IsKeyDown(KEY_W)){
        vm->keys[5] = 1;
        return 1;
    }
    else if (IsKeyDown(KEY_E)){
        vm->keys[6] = 1;
        return 1;
    }
    else if (IsKeyDown(KEY_R)){
        vm->keys[7] = 1;
        return 1;
    }
    else if (IsKeyDown(KEY_A)){
        vm->keys[8] = 1;
        return 1;
    }
    else if (IsKeyDown(KEY_S)){
        vm->keys[9] = 1;
        return 1;
    }
    else if (IsKeyDown(KEY_D)){
        vm->keys[10] = 1;
        return 1;
    }
    else if (IsKeyDown(KEY_F)){
        vm->keys[11] = 1;
        return 1;
    }
    else if (IsKeyDown(KEY_Z)){
        vm->keys[12] = 1;
        return 1;
    }
    else if (IsKeyDown(KEY_X)){
        vm->keys[13] = 1;
        return 1;
    }
    else if (IsKeyDown(KEY_C)){
        vm->keys[14] = 1;
        return 1;
    }
    else if (IsKeyDown(KEY_V)){
        vm->keys[15] = 1;
        return 1;
    }
    return 0;
}


void chip8_update_display(
    Chip8VM* vm
){
    assert(vm != NULL);

    BeginDrawing();

        ClearBackground(BLACK);

        chip8_draw_display_area(vm);
        
        chip8_draw_hardware_components_area(vm);

        chip8_draw_memory_area(vm);
        
        
    EndDrawing();
}

void chip8_construct_display(){
    SetTraceLogLevel(LOG_ERROR); 
    InitWindow(DISPLAY_WIDHT, DISPLAY_HEIGHT, "CHIP-8 emulator");
    font = LoadFont("assets/fonts/liner BMP14.TTF");
    SetTargetFPS(60);
}

void chip8_destroy_display(){
    CloseWindow();
}