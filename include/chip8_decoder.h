#pragma once

#include "chip8_structures.h"
#include "chip8_executer.h"

void decoder_class_0(const addr* opcode, DecodedOpcode* decoded_opcode);

void decoder_class_1(const addr* opcode, DecodedOpcode* decoded_opcode);

void decoder_class_2(const addr* opcode, DecodedOpcode* decoded_opcode);

void decoder_class_3(const addr* opcode, DecodedOpcode* decoded_opcode);

void decoder_class_4(const addr* opcode, DecodedOpcode* decoded_opcode);

void decoder_class_5(const addr* opcode, DecodedOpcode* decoded_opcode);

void decoder_class_6(const addr* opcode, DecodedOpcode* decoded_opcode);

void decoder_class_7(const addr* opcode, DecodedOpcode* decoded_opcode);

void decoder_class_8(const addr* opcode, DecodedOpcode* decoded_opcode);

void decoder_class_9(const addr* opcode, DecodedOpcode* decoded_opcode);

void decoder_class_A(const addr* opcode, DecodedOpcode* decoded_opcode);

void decoder_class_B(const addr* opcode, DecodedOpcode* decoded_opcode);

void decoder_class_C(const addr* opcode, DecodedOpcode* decoded_opcode);

void decoder_class_D(const addr* opcode, DecodedOpcode* decoded_opcode);

void decoder_class_E(const addr* opcode, DecodedOpcode* decoded_opcode);

void decoder_class_F(const addr* opcode, DecodedOpcode* decoded_opcode);

static inline void decoder_set_address_op(const addr* opcode, DecodedOpcode* decoded_opcode);

static inline void decoder_set_register_op(const addr* opcode, DecodedOpcode* decoded_opcode);

static inline void decoder_set_doubleregister_op(const addr* opcode, DecodedOpcode* decoded_opcode);

const void** chip8_decoder_dispatcher();