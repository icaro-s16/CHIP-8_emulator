#include "chip8_core.h"


#define X(name, mask, func)                 \
    if ( !(opcode - ( opcode & mask )))     \
        return name;

OpType chip8_get_optype(const addr opcode){
    INSTRUCTION_TABLE(X)
    return RAW;
}

#undef X

#define X(name, mask, func)             \
    case name:                          \
        decoded_opcode->execute = func; \
        break;

void chip8_set_executer(DecodedOpcode* decoded_opcode){
    switch (decoded_opcode->optype)
    {
    INSTRUCTION_TABLE(X)
    default:
        break;
    }
}

#undef X
