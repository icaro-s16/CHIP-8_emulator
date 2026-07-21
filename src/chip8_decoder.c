#include "chip8_decoder.h"


void decode_class_0(const addr opcode, DecodedOpcode* decoded_opcode){
    
    assert(decoded_opcode != NULL);
    
    switch(decoded_opcode->optype)
    {
    case RTS:
        sprintf(decoded_opcode->mnemonic, "RTS");
        break;
    case CLS:
        sprintf(decoded_opcode->mnemonic, "CLS");
        break;
    case CALL:
        decoder_set_address_op(opcode, decoded_opcode);
        sprintf(decoded_opcode->mnemonic, "CALL");
        break;
    default:
        decoder_set_raw(opcode, decoded_opcode);
        break;
    }
    
}

void decode_class_1(const addr opcode, DecodedOpcode* decoded_opcode){
    
    assert(decoded_opcode != NULL);
    
    if (decoded_opcode->optype != JMP){
        decoder_set_raw(opcode, decoded_opcode);
        return;
    }

    decoder_set_address_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "JMP 0x%.3X", decoded_opcode->address);
}

void decode_class_2(const addr opcode, DecodedOpcode* decoded_opcode){
    
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype != JSR){
        decoder_set_raw(opcode, decoded_opcode);
        return;
    }

    decoder_set_address_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "JSR 0x%.3X", decoded_opcode->address);
}

void decode_class_3(const addr opcode, DecodedOpcode* decoded_opcode){
    
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype != SKEQ_RC){
        decoder_set_raw(opcode, decoded_opcode);
        return;
    }

    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "SKEQ V%.1X, 0x%.2X", decoded_opcode->vx, decoded_opcode->constant);
}

void decode_class_4(const addr opcode, DecodedOpcode* decoded_opcode){
    
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype != SKNE_RC){
        decoder_set_raw(opcode, decoded_opcode);
        return;
    }

    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "SKNE V%.1X, 0x%.2X", decoded_opcode->vx, decoded_opcode->constant);
}

void decode_class_5(const addr opcode, DecodedOpcode* decoded_opcode){
    
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype != SKEQ_RR){
        decoder_set_raw(opcode, decoded_opcode);
        return;
    }

    decoder_set_doubleregister_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "SKEQ V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
}

void decode_class_6(const addr opcode, DecodedOpcode* decoded_opcode){
    
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype != MOV_RC){
        decoder_set_raw(opcode, decoded_opcode);
        return;
    }

    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "MOV V%.1X, 0x%.2X", decoded_opcode->vx, decoded_opcode->constant);
}

void decode_class_7(const addr opcode, DecodedOpcode* decoded_opcode){
    
    assert(decoded_opcode != NULL);

    if (decoded_opcode->optype != ADD_RC){
        decoder_set_raw(opcode, decoded_opcode);
        return;
    }

    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "ADD V%.1X, 0x%.2X", decoded_opcode->vx, decoded_opcode->constant);
}

void decode_class_8(const addr opcode, DecodedOpcode* decoded_opcode){
    assert(decoded_opcode != NULL);

    decoder_set_doubleregister_op(opcode, decoded_opcode);  

    switch (decoded_opcode->optype)
    {
    case MOV_RR:
        sprintf(decoded_opcode->mnemonic, "MOV V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
        break;
    case OR_RR:
        sprintf(decoded_opcode->mnemonic, "OR V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
        break;
    case AND_RR:
        sprintf(decoded_opcode->mnemonic, "AND V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
        break;
    case XOR_RR:
        sprintf(decoded_opcode->mnemonic, "XOR V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
        break;
    case ADD_RR:
        sprintf(decoded_opcode->mnemonic, "ADD V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
        break;
    case SUB_RR:
        sprintf(decoded_opcode->mnemonic, "SUB V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
        break;
    case SHR:
        sprintf(decoded_opcode->mnemonic, "SHR V%.1X, 1", decoded_opcode->vx);
        break;
    case RSB:
        sprintf(decoded_opcode->mnemonic, "RSB V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
        break;
    case SHL:
        sprintf(decoded_opcode->mnemonic, "SHL V%.1X, 1", decoded_opcode->vx);
        break;
    default:
        decoder_set_raw(opcode, decoded_opcode);
        break;
    }
}

void decode_class_9(const addr opcode, DecodedOpcode* decoded_opcode){
    
    assert(decoded_opcode != NULL);

    if ( decoded_opcode->optype != SKNE_RR ){
        decoder_set_raw(opcode, decoded_opcode);
        return;
    }

    decoder_set_doubleregister_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "SKNE V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
}

void decode_class_A(const addr opcode, DecodedOpcode* decoded_opcode){
    
    assert(decoded_opcode != NULL);

    if ( decoded_opcode->optype != MVI ){
        decoder_set_raw(opcode, decoded_opcode);
        return;
    }

    decoder_set_address_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "MVI 0x%.3X", decoded_opcode->address);
}

void decode_class_B(const addr opcode, DecodedOpcode* decoded_opcode){
    
    assert(decoded_opcode != NULL);

    if ( decoded_opcode->optype != JMI ){
        decoder_set_raw(opcode, decoded_opcode);
        return;
    }

    decoder_set_address_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "JMI 0x%.3X", decoded_opcode->address);
}

void decode_class_C(const addr opcode, DecodedOpcode* decoded_opcode){
    
    assert(decoded_opcode != NULL);

    if ( decoded_opcode->optype != RAND ){
        decoder_set_raw(opcode, decoded_opcode);
        return;
    }

    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "RAND V%.1X, 0x%.3X", decoded_opcode->vx, decoded_opcode->constant);
}

void decode_class_D(const addr opcode, DecodedOpcode* decoded_opcode){
    
    assert(decoded_opcode != NULL);

    if ( decoded_opcode->optype != SPRITE ){
        decoder_set_raw(opcode, decoded_opcode);
        return;
    }

    
    decoder_set_doubleregister_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->mnemonic, "SPRITE V%.1X, V%.1X, 0x%.2X", decoded_opcode->vx, decoded_opcode->vy, decoded_opcode->constant);
}

void decode_class_E(const addr opcode, DecodedOpcode* decoded_opcode){
    
    assert(decoded_opcode != NULL);

    decoder_set_register_op(opcode, decoded_opcode);
    if (decoded_opcode->optype == SKPR)
        sprintf(decoded_opcode->mnemonic, "SKPR V%.1X", decoded_opcode->vx);
    else if ( decoded_opcode->optype == SKUP )
        sprintf(decoded_opcode->mnemonic, "SKUP V%.1X", decoded_opcode->vx);
    else 
        decoder_set_raw(opcode, decoded_opcode);
}

void decode_class_F(const addr opcode, DecodedOpcode* decoded_opcode){
    
    assert(decoded_opcode != NULL);
    decoder_set_register_op(opcode, decoded_opcode);

    switch (decoded_opcode->optype)
    {
    case KEY:
        sprintf(decoded_opcode->mnemonic, "KEY V%.1X", decoded_opcode->vx);
        break;
    case SDELAY:
        sprintf(decoded_opcode->mnemonic, "SDELAY V%.1X", decoded_opcode->vx);
        break;
    case SSOUND:
        sprintf(decoded_opcode->mnemonic, "SSOUND V%.1X", decoded_opcode->vx);
        break;
    case GDELAY:
        sprintf(decoded_opcode->mnemonic, "GDELAY V%.1X, DT", decoded_opcode->vx);
        break;
    case BCD:
        sprintf(decoded_opcode->mnemonic, "BCD V%.1X", decoded_opcode->vx);
        break;
    case ADDI:
        sprintf(decoded_opcode->mnemonic, "ADDI V%.1X", decoded_opcode->vx);
        break;
    case STR:
        sprintf(decoded_opcode->mnemonic, "STR V0-V%.1X", decoded_opcode->vx);
        break;
    case LDR:
        sprintf(decoded_opcode->mnemonic, "LDR V0-V%.1X", decoded_opcode->vx);
        break;
    case FONT:
        sprintf(decoded_opcode->mnemonic, "FONT V%.1X", decoded_opcode->vx);
        break;
    default:
        sprintf(decoded_opcode->mnemonic, "RAW 0x%.4X", opcode);
        break;
    }
    
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

static inline void decoder_set_raw(const addr opcode, DecodedOpcode* decoded_opcode){
    sprintf(decoded_opcode->mnemonic, "RAW 0x%.4X", opcode);
}

void** chip8_decoder_dispatcher(){
    void (**dispatcher)(const addr, DecodedOpcode*) = calloc(16, sizeof(void*));
    dispatcher[0] = decode_class_0;
    dispatcher[1] = decode_class_1;
    dispatcher[2] = decode_class_2;
    dispatcher[3] = decode_class_3;
    dispatcher[4] = decode_class_4;
    dispatcher[5] = decode_class_5;
    dispatcher[6] = decode_class_6;
    dispatcher[7] = decode_class_7;
    dispatcher[8] = decode_class_8;
    dispatcher[9] = decode_class_9;
    dispatcher[10] = decode_class_A;
    dispatcher[11] = decode_class_B;
    dispatcher[12] = decode_class_C;
    dispatcher[13] = decode_class_D;
    dispatcher[14] = decode_class_E;
    dispatcher[15] = decode_class_F;
    return (void**)dispatcher;
}