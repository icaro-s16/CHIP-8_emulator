#include "chip8_core.h"


#define X(optype, opcode, executor, decoder)                 \
    if ( !(_opcode - ( _opcode & opcode )))                  \
        return optype;

OpType chip8_get_optype(const addr _opcode){
    INSTRUCTION_TABLE(X)
    return RAW;
}

#undef X

#define X(optype, opcode, executor, decoder)                \
    case optype:                                            \
        decoded_opcode->execute = executor;                 \
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

#define X(optype, opcode, executor, decoder)          \
    case optype:                                      \
        return decoder;

void* chip8_get_decoder(DecodedOpcode* decoded_opcode){
    switch (decoded_opcode->optype)
    {
        INSTRUCTION_TABLE(X)
        default:
            return decode_raw;
    }
}

#undef X