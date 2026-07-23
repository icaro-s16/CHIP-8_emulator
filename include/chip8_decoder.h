#pragma once

#include "chip8_core.h"

void decode_rts(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_cls(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_call(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_jmp(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_jsr(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_skeq_rc(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_skne_rc(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_skeq_rr(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_mov_rc(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_add_rc(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_mov_rr(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_or_rr(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_and_rr(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_xor_rr(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_add_rr(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_sub_rr(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_shr(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_rsb(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_shl(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_skne_rr(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_mvi(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_jmi(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_rand(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_sprite(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_skpr(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_skup(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_key(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_sdelay(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_ssound(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_gdelay(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_bcd(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_addi(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_str(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_ldr(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_font(const addr opcode, DecodedOpcode* decoded_opcode);

void decode_raw(const addr opcode, DecodedOpcode* decoded_opcode);

static void decoder_set_address_op(const addr opcode, DecodedOpcode* decoded_opcode);

static void decoder_set_register_op(const addr opcode, DecodedOpcode* decoded_opcode);

static void decoder_set_doubleregister_op(const addr opcode, DecodedOpcode* decoded_opcode);
