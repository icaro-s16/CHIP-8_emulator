#include <CUnit/Basic.h>
#include "../src/chip8_executer.c"


void test_execute_assig_instruction(){
    Chip8VM vm = {0};
    vm.V[1] = 20;

    DecodedOpcode decoded_opcode = {
        .vx = 0,
        .vy = 1
    };

    execute_assig_instruction(&vm, &decoded_opcode);

    CU_ASSERT_EQUAL(
        vm.V[0],
        20
    );
}

void test_execute_bcd_instruction(){
    Chip8VM vm = {0};

    DecodedOpcode decoded_opcode = {
        .vx = 123
    };

    execute_bcd_instruction(&vm, &decoded_opcode);

    CU_ASSERT_EQUAL(
        vm.memory[0],
        1
    );
    CU_ASSERT_EQUAL(
        vm.memory[1],
        2
    );
    CU_ASSERT_EQUAL(
        vm.memory[2],
        3
    );
}


void test_execute_bitop_instruction(){
    Chip8VM vm = {0};
    DecodedOpcode decoded_opcode = {
        .vx = 0,
        .vy = 1,
        .constant = 0x1
    };
    vm.V[decoded_opcode.vy] = 0b1111;

    execute_bitop_instruction(&vm, &decoded_opcode);

    CU_ASSERT_EQUAL(
        vm.V[decoded_opcode.vx],
        0b1111
    );

    decoded_opcode.constant = 0x2;
    vm.V[decoded_opcode.vx] = 0;

    execute_bitop_instruction(&vm, &decoded_opcode);

    CU_ASSERT_EQUAL(
        vm.V[decoded_opcode.vx],
        0
    );

    decoded_opcode.constant = 0x3;
    vm.V[decoded_opcode.vx] = 0;

    execute_bitop_instruction(&vm, &decoded_opcode);

    CU_ASSERT_EQUAL(
        vm.V[decoded_opcode.vx],
        0b1111
    );

    decoded_opcode.constant = 0x6;
    vm.V[decoded_opcode.vx] = 0b10;

    execute_bitop_instruction(&vm, &decoded_opcode);

    CU_ASSERT_EQUAL(
        vm.V[decoded_opcode.vx],
        0b1
    );

    decoded_opcode.constant = 0xE;
    vm.V[decoded_opcode.vx] = 0b01;

    execute_bitop_instruction(&vm, &decoded_opcode);

    CU_ASSERT_EQUAL(
        vm.V[decoded_opcode.vx],
        0b10
    );

}

void test_execute_cond_instruction(){
    Chip8VM vm = {0};
    DecodedOpcode decoded_opcode = {0};
    
    decoded_opcode.vx = 1;
    decoded_opcode.constant = 1;
    decoded_opcode.decoder_class = 0x3;

    execute_cond_instruction(&vm, &decoded_opcode);

    CU_ASSERT_EQUAL(
        vm.pc,
        2
    );

    decoded_opcode.constant = 0;
    vm.pc = 0;
    
    execute_cond_instruction(&vm, &decoded_opcode);

    CU_ASSERT_NOT_EQUAL(
        vm.pc,
        2
    );

    decoded_opcode.vx = 1;
    decoded_opcode.constant = 1;
    decoded_opcode.decoder_class = 0x4;
    vm.pc = 0;

    execute_cond_instruction(&vm, &decoded_opcode);

    CU_ASSERT_NOT_EQUAL(
        vm.pc,
        2
    );

    decoded_opcode.vx = 1;
    decoded_opcode.constant = 0;
    decoded_opcode.decoder_class = 0x4;
    vm.pc = 0;

    execute_cond_instruction(&vm, &decoded_opcode);

    CU_ASSERT_EQUAL(
        vm.pc,
        2
    );
    
    decoded_opcode.vx = 1;
    decoded_opcode.vy = 1;
    decoded_opcode.decoder_class = 0x5;
    vm.pc = 0;

    execute_cond_instruction(&vm, &decoded_opcode);

    CU_ASSERT_EQUAL(
        vm.pc,
        2
    );

    decoded_opcode.vx = 1;
    decoded_opcode.vy = 0;
    decoded_opcode.decoder_class = 0x5;
    vm.pc = 0;

    execute_cond_instruction(&vm, &decoded_opcode);

    CU_ASSERT_NOT_EQUAL(
        vm.pc,
        2
    );
    
    decoded_opcode.vx = 1;
    decoded_opcode.vy = 0;
    decoded_opcode.decoder_class = 0x9;
    vm.pc = 0;

    execute_cond_instruction(&vm, &decoded_opcode);

    CU_ASSERT_EQUAL(
        vm.pc,
        2
    );

    decoded_opcode.vx = 1;
    decoded_opcode.vy = 1;
    decoded_opcode.decoder_class = 0x9;
    vm.pc = 0;

    execute_cond_instruction(&vm, &decoded_opcode);

    CU_ASSERT_NOT_EQUAL(
        vm.pc,
        2
    );
    
}


void test_execute_const_instruction(){
    Chip8VM vm = {0};
    DecodedOpcode decoded_opcode = {0};

    decoded_opcode.vx = 0;
    decoded_opcode.constant = 20;
    decoded_opcode.decoder_class = 0x6;

    execute_const_instruction(&vm, &decoded_opcode);

    CU_ASSERT_EQUAL(
        vm.V[decoded_opcode.vx],
        decoded_opcode.constant
    );

    vm.V[decoded_opcode.vx] = 20;
    decoded_opcode.vx = 0;
    decoded_opcode.constant = 20;
    decoded_opcode.decoder_class = 0x7;

    execute_const_instruction(&vm, &decoded_opcode);

    CU_ASSERT_EQUAL(
        vm.V[decoded_opcode.vx],
        decoded_opcode.constant + 20
    );

    for(int i = 0; i < CHIP8_DISPLAY_HEIGHT * CHIP8_DISPLAY_WIDGHT; i++)
        vm.display[i] = 1;
    
    decoded_opcode.decoder_class = 0x0;
    execute_display_instruction(&vm, &decoded_opcode);

    for(int i = 0; i < CHIP8_DISPLAY_HEIGHT * CHIP8_DISPLAY_WIDGHT; i++)
        CU_ASSERT_EQUAL(
            vm.display[i],
            0
        );

}