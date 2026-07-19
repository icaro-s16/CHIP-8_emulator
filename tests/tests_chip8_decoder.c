#include <CUnit/Basic.h>
#include "../src/chip8_decoder.c"

void test_decoder_set_address_op(){
    DecodedOpcode opcode;
    addr instruction_addr = 0x0FFF;
    decoder_set_address_op(&instruction_addr, &opcode);

    CU_ASSERT_EQUAL(
        opcode.address,
        0x0FFF
    );
}


void test_decoder_set_register_op(){
    DecodedOpcode opcode;
    addr instruction_addr = 0x0ABB;
    decoder_set_register_op(&instruction_addr, &opcode);

    CU_ASSERT_EQUAL(
        opcode.vx,
        0X000A
    );
    CU_ASSERT_EQUAL(
        opcode.constant,
        0x00BB
    );
}

void test_decoder_set_doubleregister_op(){
    DecodedOpcode opcode;
    addr instruction_addr = 0x0ABC;
    decoder_set_doubleregister_op(&instruction_addr, &opcode);

    CU_ASSERT_EQUAL(
        opcode.vx,
        0x000A
    );
    CU_ASSERT_EQUAL(
        opcode.vy,
        0x000B
    );
    CU_ASSERT_EQUAL(
        opcode.constant,
        0x000C
    );
}

void test_decoder_function(){
    DecodedOpcode opcode;
    addr instruction_addr = 0x0FFF;
    decode_class_1(&instruction_addr, &opcode);

    CU_ASSERT_EQUAL(
        opcode.address,
        0x0FFF
    );
    CU_ASSERT_STRING_EQUAL(
        opcode.mnemonic,
        "GOTO 0x0FFF"
    );
}

