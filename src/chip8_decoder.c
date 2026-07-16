#include "chip8_decoder.h"


static inline void decoder_set_address_op(const addr* opcode, DecodedOpcode* decoded_opcode){
    decoded_opcode->address = *opcode & 0x0FFF;
}

static inline void decoder_set_register_op(const addr* opcode, DecodedOpcode* decoded_opcode){
    decoded_opcode->vx = (*opcode & 0x0F00) >> 8;
    decoded_opcode->constant = *opcode & 0x00FF;
}

static inline void decoder_set_doubleregister_op(const addr* opcode, DecodedOpcode* decoded_opcode){
    decoded_opcode->vx = (*opcode & 0x0F00) >> 8;
    decoded_opcode->vy = (*opcode & 0x00F0) >> 4;
    decoded_opcode->constant = *opcode & 0x000F;
}


void decoder_class_0(const addr* opcode, DecodedOpcode* decoded_opcode){
    byte instruction_id = *opcode & 0x00FF;

    switch(instruction_id)
    {
    case 0xEE:
        decoded_opcode->execute = execute_flow_instruction;
        sprintf(decoded_opcode->instruction_alias, "RET");
        break;
    case 0xE0:
        decoded_opcode->execute = execute_display_instruction;
        sprintf(decoded_opcode->instruction_alias, "CLR");
        break;
    default:
        decoded_opcode->execute = execute_call_instruction;
        decoder_set_address_op(opcode, decoded_opcode);
        sprintf(decoded_opcode->instruction_alias, "CALL");
        break;
    }
    
}

void decoder_class_1(const addr* opcode, DecodedOpcode* decoded_opcode){
    decoded_opcode->execute = execute_flow_instruction;
    decoder_set_address_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->instruction_alias, "GOTO 0x%.4X", decoded_opcode->address);
}

void decoder_class_2(const addr* opcode, DecodedOpcode* decoded_opcode){
    decoded_opcode->execute = execute_flow_instruction;
    decoder_set_address_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->instruction_alias, "CALL 0x%.4X", decoded_opcode->address);
}

void decoder_class_3(const addr* opcode, DecodedOpcode* decoded_opcode){
    decoded_opcode->execute = execute_cond_instruction;
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->instruction_alias, "JE V%.1X, 0x%.2X", decoded_opcode->vx, decoded_opcode->constant);
}

void decoder_class_4(const addr* opcode, DecodedOpcode* decoded_opcode){
    decoded_opcode->execute = execute_cond_instruction;
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->instruction_alias, "JNE V%.1X, 0x%.2X", decoded_opcode->vx, decoded_opcode->constant);
}

void decoder_class_5(const addr* opcode, DecodedOpcode* decoded_opcode){
    decoded_opcode->execute = execute_cond_instruction;
    decoder_set_doubleregister_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->instruction_alias, "JE V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
}

void decoder_class_6(const addr* opcode, DecodedOpcode* decoded_opcode){
    decoded_opcode->execute = execute_const_instruction;
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->instruction_alias, "MOV V%.1X, 0x%.2X", decoded_opcode->vx, decoded_opcode->constant);
}

void decoder_class_7(const addr* opcode, DecodedOpcode* decoded_opcode){
    decoded_opcode->execute = execute_const_instruction;
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->instruction_alias, "ADD V%.1X, 0x%.2X", decoded_opcode->vx, decoded_opcode->constant);
}

void decoder_class_8(const addr* opcode, DecodedOpcode* decoded_opcode){
    decoder_set_doubleregister_op(opcode, decoded_opcode);  
    byte instruction_identifier = *opcode & 0x000F; 
    
    if (instruction_identifier == 0x0 ){
        decoded_opcode->execute = execute_assig_instruction;
        sprintf(decoded_opcode->instruction_alias, "MOV V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);

    }
    else if (
        instruction_identifier <= 0x3 || 
        instruction_identifier == 0x6 ||
        instruction_identifier == 0xE 
    ){
        decoded_opcode->execute = execute_bitop_instruction;
        if (instruction_identifier  == 0x1) 
            sprintf(decoded_opcode->instruction_alias, "OR V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
        if (instruction_identifier  == 0x2)
            sprintf(decoded_opcode->instruction_alias, "AND V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
        if (instruction_identifier  == 0x3)
            sprintf(decoded_opcode->instruction_alias, "XOR V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
        if (instruction_identifier == 0x6)
            sprintf(decoded_opcode->instruction_alias, "SHR V%.1X, 1", decoded_opcode->vx);    
        if (instruction_identifier == 0xE)
            sprintf(decoded_opcode->instruction_alias, "SHE V%.1X, 1", decoded_opcode->vx);

    }
    else{
        decoded_opcode->execute = execute_math_instruction;
        if (instruction_identifier  == 0x4) 
            sprintf(decoded_opcode->instruction_alias, "ADD V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
        if (instruction_identifier  == 0x5) 
            sprintf(decoded_opcode->instruction_alias, "SUB V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
        else
            sprintf(decoded_opcode->instruction_alias, "RSUB V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);

    }
}

void decoder_class_9(const addr* opcode, DecodedOpcode* decoded_opcode){
    decoded_opcode->execute = execute_cond_instruction;
    decoder_set_doubleregister_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->instruction_alias, "JNE V%.1X, V%.1X", decoded_opcode->vx, decoded_opcode->vy);
}

void decoder_class_A(const addr* opcode, DecodedOpcode* decoded_opcode){
    decoded_opcode->execute = execute_mem_instruction;
    decoder_set_address_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->instruction_alias, "MOV I, 0x%.4X", decoded_opcode->address);
}

void decoder_class_B(const addr* opcode, DecodedOpcode* decoded_opcode){
    decoded_opcode->execute = execute_flow_instruction;
    decoder_set_address_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->instruction_alias, "MOV PC, V0 + 0x%.4X", decoded_opcode->address);
}

void decoder_class_C(const addr* opcode, DecodedOpcode* decoded_opcode){
    decoded_opcode->execute = execute_rand_instruction;
    decoder_set_register_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->instruction_alias, "RAND V%.1X, 0x%.2X", decoded_opcode->vx, decoded_opcode->constant);
}

void decoder_class_D(const addr* opcode, DecodedOpcode* decoded_opcode){
    decoded_opcode->execute = execute_display_instruction;
    decoder_set_doubleregister_op(opcode, decoded_opcode);
    sprintf(decoded_opcode->instruction_alias, "DRW V%.1X, V%.1X, 0x%.1X", decoded_opcode->vx, decoded_opcode->vy, decoded_opcode->constant);
}

void decoder_class_E(const addr* opcode, DecodedOpcode* decoded_opcode){
    decoded_opcode->execute = execute_keyop_instruction;
    decoder_set_register_op(opcode, decoded_opcode);
    if (decoded_opcode->constant == 0x9E)
        sprintf(decoded_opcode->instruction_alias, "JE V%.1X, KEY", decoded_opcode->vx);
    else
        sprintf(decoded_opcode->instruction_alias, "JNE V%.1X, KEY", decoded_opcode->vx);
}

void decoder_class_F(const addr* opcode, DecodedOpcode* decoded_opcode){
    decoder_set_register_op(opcode, decoded_opcode);
    byte instruction_identifier = *opcode & 0x00FF; 

    switch (instruction_identifier)
    {
    case 0x0A:
        sprintf(decoded_opcode->instruction_alias, "MOV V%.1X, KEY", decoded_opcode->vx);
        decoded_opcode->execute = execute_timer_instruction;
        break;
    
    case 0x18:
        sprintf(decoded_opcode->instruction_alias, "MOV ST, V%.1X", decoded_opcode->vx);
        decoded_opcode->execute = execute_sound_instruction;
        break;
    case 0x07:
        sprintf(decoded_opcode->instruction_alias, "MOV V%.1X, DT", decoded_opcode->vx);
        decoded_opcode->execute = execute_timer_instruction;
        break;
    case 0x33:
        sprintf(decoded_opcode->instruction_alias, "BCD V%.1X", decoded_opcode->vx);
        decoded_opcode->execute = execute_bcd_instruction;
        break;
    
    default:
        if (instruction_identifier == 0x1E)
            sprintf(decoded_opcode->instruction_alias, "ADD I, V%.1X", decoded_opcode->vx);
        if (instruction_identifier == 0x1E)
            sprintf(decoded_opcode->instruction_alias, "MEMDUMP V%.1X", decoded_opcode->vx);
        if (instruction_identifier == 0x1E)
            sprintf(decoded_opcode->instruction_alias, "MEMLOAD V%.1X", decoded_opcode->vx);
        else
            sprintf(decoded_opcode->instruction_alias, "MOV I, V%.1X", decoded_opcode->vx);
        decoded_opcode->execute = execute_mem_instruction;
        break;
    }
}

const void** chip8_decoder_dispatcher(){
    void (**dispatcher)(const addr*, DecodedOpcode*) = calloc(16, sizeof(void*));
    dispatcher[0] = decoder_class_0;
    dispatcher[1] = decoder_class_1;
    dispatcher[2] = decoder_class_2;
    dispatcher[3] = decoder_class_3;
    dispatcher[4] = decoder_class_4;
    dispatcher[5] = decoder_class_5;
    dispatcher[6] = decoder_class_6;
    dispatcher[7] = decoder_class_7;
    dispatcher[8] = decoder_class_8;
    dispatcher[9] = decoder_class_9;
    dispatcher[10] = decoder_class_A;
    dispatcher[11] = decoder_class_B;
    dispatcher[12] = decoder_class_C;
    dispatcher[13] = decoder_class_D;
    dispatcher[14] = decoder_class_E;
    dispatcher[15] = decoder_class_F;
    return (const void**)dispatcher;
}