#include "chip8_executer.h"


void execute_mov_rr(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  MOV_RR)
        execute_err(decoded_opcode);

    vm->V[decoded_opcode->vx] = vm->V[decoded_opcode->vy];
}

void execute_bcd(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);    

    if (decoded_opcode->optype != BCD)
        execute_err(decoded_opcode);

    vm->memory.write(&vm->memory, vm->I, decoded_opcode->vx / 100);
    vm->memory.write(&vm->memory, vm->I + 1, (decoded_opcode->vx / 10) % 10);
    vm->memory.write(&vm->memory, vm->I + 2, decoded_opcode->vx % 10);
}

void execute_or_rr(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  OR_RR)
        execute_err(decoded_opcode);

    vm->V[decoded_opcode->vx] |= vm->V[decoded_opcode->vy];
}

void execute_and_rr(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  AND_RR)
        execute_err(decoded_opcode);

    vm->V[decoded_opcode->vx] &= vm->V[decoded_opcode->vy];
}

void execute_xor_rr(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  XOR_RR)
        execute_err(decoded_opcode);

    vm->V[decoded_opcode->vx] ^= vm->V[decoded_opcode->vy];
}

void execute_shr(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  SHR)
        execute_err(decoded_opcode);

    vm->V[0xF] = vm->V[decoded_opcode->vx] & 0x1u;
    vm->V[decoded_opcode->vx] >>= 1;
}

void execute_shl(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  SHR)
        execute_err(decoded_opcode);

    vm->V[0xF] = vm->V[decoded_opcode->vx] & 0x80u;
    vm->V[decoded_opcode->vx] <<= 1;
}

void execute_call(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);
    // TODO: Calls machine code routine for the COSMAC VIP
    return;
}

void execute_skeq_rc(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  SKEQ_RC)
        execute_err(decoded_opcode);

    if (decoded_opcode->vx == decoded_opcode->constant)
        vm->pc += 2;
}

void execute_skne_rc(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  SKNE_RC)
        execute_err(decoded_opcode);

    if (decoded_opcode->vx != decoded_opcode->constant)
        vm->pc += 2;
}

void execute_skeq_rr(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  SKEQ_RR)
        execute_err(decoded_opcode);

    if (decoded_opcode->vx == decoded_opcode->vy)
        vm->pc += 2;
}

void execute_skne_rr(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  SKNE_RR)
        execute_err(decoded_opcode);

    if (decoded_opcode->vx != decoded_opcode->vy)
        vm->pc += 2;
}

void execute_mov_rc(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  MOV_RC)
        execute_err(decoded_opcode);

    vm->V[decoded_opcode->vx] = decoded_opcode->constant;
}

void execute_add_rc(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  ADD_RC)
        execute_err(decoded_opcode);

    vm->V[decoded_opcode->vx] += decoded_opcode->constant;
}


void execute_sprite(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  SPRITE)
        execute_err(decoded_opcode);

    int x = vm->V[decoded_opcode->vx] % CHIP8_DISPLAY_WIDGHT;
    int y = vm->V[decoded_opcode->vy] % CHIP8_DISPLAY_HEIGHT;
    vm->V[0xF] = 0;
    for(int row = 0; row < decoded_opcode->constant; row++){
        byte sprite_byte = vm->memory.read(&vm->memory, vm->I + row);
        for(int col = 0; col < 8; col++){
            byte *screen_pixel = &(vm->display[(y + row) % CHIP8_DISPLAY_HEIGHT][(x + col) % CHIP8_DISPLAY_WIDGHT]);
            if (!(sprite_byte & (0x80u >> col)))
                continue;

            if (*screen_pixel > 0)
                vm->V[0xF] = 1;
                
            *screen_pixel ^= 1;
        }
    }
}

void execute_cls(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  CLS)
        execute_err(decoded_opcode);

    memset(
        vm->display, 
        0, 
        sizeof(vm->display)
    );
}

void execute_rts(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  RTS)
        execute_err(decoded_opcode);

    if (vm->sp <= 0){
        fprintf(stderr, "ERROR: Stack pointer underflow..\n");
        exit(1);
    }
    vm->pc = vm->stack[--vm->sp];
}

void execute_jmp(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  JMP)
        execute_err(decoded_opcode);

    vm->pc = decoded_opcode->address;
}

void execute_jsr(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  JSR)
        execute_err(decoded_opcode);

    if (vm->sp > 16){
        fprintf(stderr, "ERROR: Stack pointer overflow..\n");
        exit(1);
    } 
    vm->stack[vm->sp++] = vm->pc;
    vm->pc = decoded_opcode->address;
}

void execute_jmi(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  JMI)
        execute_err(decoded_opcode);

    vm->pc = vm->V[0] + decoded_opcode->address;
}

void execute_skpr(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  SKPR)
        execute_err(decoded_opcode);

    if (vm->keys[vm->V[decoded_opcode->vx]])
        vm->pc += 2;
}

void execute_skup(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  SKUP)
        execute_err(decoded_opcode);

    if (!vm->keys[vm->V[decoded_opcode->vx]])
        vm->pc += 2;
}

void execute_key(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  KEY)
        execute_err(decoded_opcode);

    if (!chip8_press_key(vm))
        vm->pc -= 2;
}

void execute_addi(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  ADDI)
        execute_err(decoded_opcode);

    vm->I += decoded_opcode->vx;
}

void execute_font(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  FONT)
        execute_err(decoded_opcode);

    vm->I = FONTSET_INITIAL_OFFSET + (vm->V[decoded_opcode->vx] * 5);
}

void execute_str(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  STR)
        execute_err(decoded_opcode);

    for (int i = 0; i <= decoded_opcode->vx; i++)
        vm->memory.write(&vm->memory, vm->I + i, vm->V[i]);
}

void execute_ldr(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  LDR)
        execute_err(decoded_opcode);

    for(int i = 0; i <= decoded_opcode->vx; i++)
        vm->V[i] = vm->memory.read(&vm->memory, vm->I + i);
}

void execute_mvi(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  MVI)
        execute_err(decoded_opcode);

    vm->I = decoded_opcode->address;
}

void execute_add_rr(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  ADD_RR)
        execute_err(decoded_opcode);

    uint16_t sum = vm->V[decoded_opcode->vx] + vm->V[decoded_opcode->vy];
    vm->V[0xF] = (sum > 255u);
    vm->V[decoded_opcode->vx] = sum & 0xFFu;
}

void execute_sub_rr(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  SUB_RR)
        execute_err(decoded_opcode);

    vm->V[0xF] = (
        vm->V[decoded_opcode->vx] < 
        vm->V[decoded_opcode->vy]
    );
    vm->V[decoded_opcode->vx] -= vm->V[decoded_opcode->vy];
}

void execute_rsb(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype !=  RSB)
        execute_err(decoded_opcode);

    vm->V[0xF] = (
        vm->V[decoded_opcode->vx] > 
        vm->V[decoded_opcode->vy]
    ) ? 1 : 0;
    vm->V[decoded_opcode->vx] = vm->V[decoded_opcode->vy] - vm->V[decoded_opcode->vx];
}

void execute_rand(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);    

    if (decoded_opcode->optype != RAND)
        execute_err(decoded_opcode);

    vm->V[decoded_opcode->vx] = (rand() % 256) & decoded_opcode->constant;
}

void execute_ssound(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);    

    if (decoded_opcode->optype != SSOUND)
        execute_err(decoded_opcode);

    vm->sound_timer = decoded_opcode->vx;
}

void execute_gdelay(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);    

    if (decoded_opcode->optype != GDELAY)
        execute_err(decoded_opcode);

    vm->V[decoded_opcode->vx] = vm->delay_timer;
}

void execute_sdelay(
    Chip8VM* vm, 
    const DecodedOpcode* decoded_opcode
){
    assert(vm != NULL);
    assert(decoded_opcode != NULL);    

    if (decoded_opcode->optype != SDELAY)
        execute_err(decoded_opcode);

    vm->delay_timer = vm->V[decoded_opcode->vx];
}

static void execute_err(const DecodedOpcode* decoded_opcode){
    fprintf(stderr, "ERROR: Unknown instruction \"%s\" ..\n", decoded_opcode->mnemonic);
    exit(1);
}