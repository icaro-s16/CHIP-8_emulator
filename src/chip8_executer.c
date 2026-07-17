#include "chip8_executer.h"


inline void execute_assig_instruction(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    vm->V[decoded_opcode->vx] = vm->V[decoded_opcode->vy];
}

inline void execute_bcd_instruction(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);
    
    vm->memory[vm->I] = decoded_opcode->vx / 100;
    vm->memory[vm->I + 1] = (decoded_opcode->vx / 10) % 10;
    vm->memory[vm->I + 2] = decoded_opcode->vx % 10;
}

void execute_bitop_instruction(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    switch(decoded_opcode->constant){
    case 0x1:
        vm->V[decoded_opcode->vx] |= vm->V[decoded_opcode->vy];
        break;
    case 0x2:
        vm->V[decoded_opcode->vx] &= vm->V[decoded_opcode->vy];
        break;
    case 0x3:
        vm->V[decoded_opcode->vx] ^= vm->V[decoded_opcode->vy];
        break;
    case 0x6:
        vm->V[decoded_opcode->vx] >>= 1;
        break;
    case 0xE:
        vm->V[decoded_opcode->vx] <<= 1;
        break;
    default:
        break;
    }
    
}

void execute_call_instruction(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    // TODO: Calls machine code routine for the COSMAC VIP
    return;
}

void execute_cond_instruction(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);
    
    switch (decoded_opcode->decoder_class)
    {
    case 0x3:
        if (decoded_opcode->vx == decoded_opcode->constant)
            vm->pc += 2;
        break;
    case 0x4:
        if (decoded_opcode->vx != decoded_opcode->constant)
            vm->pc += 2;
        break;
    case 0x5:
        if (decoded_opcode->vx == decoded_opcode->vy)
            vm->pc += 2;
        break;
    case 0x9:
        if (decoded_opcode->vx != decoded_opcode->vy)
            vm->pc += 2;
        break;
    default:
        break;
    }
}

void execute_const_instruction(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);
    
    switch (decoded_opcode->decoder_class)
    {
    case 0x6:
        vm->V[decoded_opcode->vx] = decoded_opcode->constant;
        break;
    case 0x7:
        vm->V[decoded_opcode->vx] += decoded_opcode->constant;
        break;
    default:
        break;
    }
}

void execute_display_instruction(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);
    
    switch (decoded_opcode->decoder_class)
    {
    case 0x0:
        for (int i = 0; i < (CHIP8_DISPLAY_HEIGHT * CHIP8_DISPLAY_WIDGHT); i++)
            vm->display[i] = 0;
        break;
    
    case 0xD:{
        int x = decoded_opcode->vx % CHIP8_DISPLAY_WIDGHT;
        int y = decoded_opcode->vy % CHIP8_DISPLAY_HEIGHT;
        vm->V[0xF] = 0;
        for(int row = 0; row < decoded_opcode->constant; row++){
            byte sprite_byte = vm->memory[vm->I + row];
            for(int col = 0; col < 8; col++){
                byte *screen_pixel = &vm->display[(y + row) * CHIP8_DISPLAY_WIDGHT + (x + row)];
                if ((sprite_byte & (1 << col)) ){
                    if (*screen_pixel > 0)
                        vm->V[0xF] = 1;
                    *screen_pixel ^= 1;
                }
            }
        }
        break;
    }

    default:
        break;
    }
}

void execute_flow_instruction(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);
    
    switch (decoded_opcode->decoder_class)
    {
    case 0x0:
        if (vm->sp <= 0){
            return;
        }
        vm->pc = vm->stack[vm->sp--];
        break;

    case 0x1:
        vm->pc = decoded_opcode->address;
        break;

    case 0x2:
        if (vm->sp >= 16){
            return;
        } 
        vm->stack[vm->sp ++] = vm->pc;
        vm->pc = decoded_opcode->address;
        break;
        
    case 0xB:
        vm->pc = vm->V[0] + decoded_opcode->address;
        break;
    default:
        break;
    }
}

void execute_keyop_instruction(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);
    
    switch (decoded_opcode->constant)
    {
    case 0x9E:
        if (vm->keys[vm->V[decoded_opcode->vx]])
            vm->pc += 2;
        break;

    case 0xA1:
        if (!vm->keys[vm->V[decoded_opcode->vx]])
            vm->pc += 2;
        break;

    case 0x0A:
        if (!chip8_press_key(vm))
            vm->pc -= 2;
        break;

    default:
        break;
    }
}

void execute_mem_instruction(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);
    
    if (decoded_opcode->decoder_class == 0xA){
        vm->I = decoded_opcode->address;
        return;
    }
    
    switch (decoded_opcode->constant)
    {
    case 0x1E:
        vm->I += decoded_opcode->vx;
        break;

    case 0x29:
        vm->I = &(vm->memory[FONTSET_INITIAL_OFFSET + (decoded_opcode->vx * 5)]) - vm->memory;
        break;

    case 0x55:
        for (int i = 0; i <= decoded_opcode->vx; i++)
            vm->memory[vm->I + i] = vm->V[i];
        break;
        
    case 0x65:
        for(int i = 0; i <= decoded_opcode->vx; i++)
            vm->V[i] = vm->memory[vm->I + i];
        break;
    
    default:
        break;
    }
}

void execute_math_instruction(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);
    
    switch (decoded_opcode->constant)
    {
    case 0x4:
        vm->V[decoded_opcode->vx] += vm->V[decoded_opcode->vy];
        break;
    
    case 0x5:
        vm->V[decoded_opcode->vx] -= vm->V[decoded_opcode->vy];
        break;
    
    case 0x7:
        vm->V[decoded_opcode->vx] = vm->V[decoded_opcode->vy] - vm->V[decoded_opcode->vx];
        break;
    
    default:
        break;
    }
}

inline void execute_rand_instruction(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);
    
    vm->V[decoded_opcode->vx] = rand() & decoded_opcode->constant;
}

inline void execute_sound_instruction(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);
    
    vm->sound_timer = decoded_opcode->vx;
}

void execute_timer_instruction(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);
    
    switch (decoded_opcode->constant)
    {
    case 0x07:
        vm->V[decoded_opcode->vx] = vm->delay_timer;
        break;

    case 0x15:
        vm->delay_timer = vm->V[decoded_opcode->vx];
        break;

    default:
        break;
    }
}
