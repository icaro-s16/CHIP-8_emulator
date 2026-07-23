#include "chip8_decoder.h"



void decode_rts(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == RTS);
    sprintf(decoded_opcode->mnemonic, "RTS");
}

void decode_cls(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == CLS);
    sprintf(decoded_opcode->mnemonic, "CLS");
}

void decode_call(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == CALL);
    decoder_set_address_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "CALL 0x%.3X", decoded_opcode->address);
}

void decode_jmp(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == JMP);
    decoder_set_address_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "JMP 0x%.3X", decoded_opcode->address);
}

void decode_jsr(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == JSR);
    decoder_set_address_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "JSR 0x%.3X", decoded_opcode->address);
}

void decode_skeq_rc(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == SKEQ_RC);
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "SKEQ V%.1X, 0x%.2X", decoded_opcode->vx, decoded_opcode->constant);
}

void decode_skne_rc(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == SKNE_RC);
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "SKNE V%.1X, 0x%.2X", decoded_opcode->vx, decoded_opcode->constant);
}

void decode_skeq_rr(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == SKEQ_RR);
    decoder_set_doubleregister_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "SKEQ V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
}

void decode_mov_rc(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == MOV_RC);
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "MOV V%.1X, 0x%.2X", decoded_opcode->vx, decoded_opcode->constant);
}

void decode_add_rc(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == ADD_RC);
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "ADD V%.1X, 0x%.2X", decoded_opcode->vx, decoded_opcode->constant);
}

void decode_mov_rr(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == MOV_RR);
    decoder_set_doubleregister_op(opcode, decoded_opcode);  
    sprintf(decoded_opcode->mnemonic, "MOV V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
}

void decode_or_rr(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == OR_RR);
    decoder_set_doubleregister_op(opcode, decoded_opcode);  
    sprintf(decoded_opcode->mnemonic, "OR V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
}

void decode_and_rr(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == AND_RR);
    decoder_set_doubleregister_op(opcode, decoded_opcode);  
    sprintf(decoded_opcode->mnemonic, "AND V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
}

void decode_xor_rr(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == XOR_RR);
    decoder_set_doubleregister_op(opcode, decoded_opcode);  
    sprintf(decoded_opcode->mnemonic, "XOR V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
}

void decode_add_rr(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == ADD_RR);
    decoder_set_doubleregister_op(opcode, decoded_opcode);  
    sprintf(decoded_opcode->mnemonic, "ADD V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
}

void decode_sub_rr(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == SUB_RR);
    decoder_set_doubleregister_op(opcode, decoded_opcode);  
    sprintf(decoded_opcode->mnemonic, "SUB V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
}

void decode_shr(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == SHR);
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "SHR V%.1X, 1", decoded_opcode->vx, decoded_opcode->vy);
}

void decode_rsb(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == RSB);
    decoder_set_doubleregister_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "RSB V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
}

void decode_shl(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == SHL);
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "SHL V%.1X, 1", decoded_opcode->vx, decoded_opcode->vy);
}

void decode_skne_rr(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == SKNE_RR);
    decoder_set_doubleregister_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "SKNE V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
}

void decode_mvi(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == MVI);
    decoder_set_address_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "MVI 0x%.3X", decoded_opcode->address);
}

void decode_jmi(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == JMI);
    decoder_set_address_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "JMI 0x%.3X", decoded_opcode->address);
}

void decode_rand(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == RAND);
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "RAND V%.1X, 0x%.3X", decoded_opcode->vx, decoded_opcode->constant);

}

void decode_sprite(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == SPRITE);
    decoder_set_doubleregister_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "SPRITE V%.1X, V%.1X, 0x%.2X", decoded_opcode->vx, decoded_opcode->vy, decoded_opcode->constant);
}

void decode_skpr(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == SKPR);
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "SKPR V%.1X", decoded_opcode->vx);
}

void decode_skup(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == SKUP);
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "SKUP V%.1X", decoded_opcode->vx);
}

void decode_key(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == KEY);
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "KEY V%.1X", decoded_opcode->vx);
}

void decode_sdelay(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == SDELAY);
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "SDELAY V%.1X", decoded_opcode->vx);
}

void decode_ssound(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == SSOUND);
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "SSOUND V%.1X", decoded_opcode->vx);
}

void decode_gdelay(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == GDELAY);
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "GDELAY V%.1X, DT", decoded_opcode->vx);
}

void decode_bcd(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == BCD);
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "BCD V%.1X", decoded_opcode->vx);
}

void decode_addi(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == ADDI);
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "ADDI V%.1X", decoded_opcode->vx);
}

void decode_str(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == STR);
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "STR V0-V%.1X", decoded_opcode->vx);
}

void decode_ldr(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == LDR);
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "LDR V0-V%.1X", decoded_opcode->vx);
}

void decode_font(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == FONT);
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "FONT V%.1X", decoded_opcode->vx);
}

void decode_raw(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);
    assert(decoded_opcode->optype == RAW);
    sprintf(decoded_opcode->mnemonic, "RAW 0x%.4X", opcode);
}

static inline void decoder_set_address_op(const addr opcode, DecodedOpcode* decoded_opcode){
    
    assert(decoded_opcode != NULL);
    decoded_opcode->address = opcode & 0x0FFF;
}

static inline void decoder_set_register_op(const addr opcode, DecodedOpcode* decoded_opcode){
    
    assert(decoded_opcode != NULL);
    decoded_opcode->vx = (opcode & 0x0F00) >> 8;
    decoded_opcode->constant = opcode & 0x00FF;
}

static inline void decoder_set_doubleregister_op(const addr opcode, DecodedOpcode* decoded_opcode){
    
    assert(decoded_opcode != NULL);
    decoded_opcode->vx = (opcode & 0x0F00) >> 8;
    decoded_opcode->vy = (opcode & 0x00F0) >> 4;
    decoded_opcode->constant = opcode & 0x000F;
}
