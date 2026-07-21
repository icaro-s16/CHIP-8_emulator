#pragma once

#include "chip8_core.h"

void decode_class_0(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_class_1(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_class_2(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_class_3(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_class_4(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_class_5(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_class_6(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_class_7(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_class_8(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_class_9(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_class_A(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_class_B(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_class_C(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_class_D(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_class_E(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_class_F(const addr opcode, DecodedOpcode* decoded_opcode);

static void decoder_set_address_op(const addr opcode, DecodedOpcode* decoded_opcode);

static void decoder_set_register_op(const addr opcode, DecodedOpcode* decoded_opcode);

static void decoder_set_doubleregister_op(const addr opcode, DecodedOpcode* decoded_opcode);

static void decoder_set_raw(const addr opcode, DecodedOpcode* decoded_opcode);

void** chip8_decoder_dispatcher();