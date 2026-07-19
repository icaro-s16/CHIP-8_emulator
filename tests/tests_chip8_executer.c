#include <CUnit/Basic.h>
#include "../src/chip8_executer.c"


static Memory tests_memory_construct(){
    Memory mem = {0};
    mem.rom = calloc(MEM_MAX_SIZE - PC_INITIAL_OFFSET, sizeof(byte));
    mem.rom_size = MEM_MAX_SIZE - PC_INITIAL_OFFSET;
    mem.read = chip8_memory_read;
    mem.write = chip8_memory_write;
    return mem;
}

static void tests_memory_destroy(Memory* mem){
    free(mem->rom);
}

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

    vm.memory = tests_memory_construct();

    DecodedOpcode decoded_opcode = {
        .vx = 123
    };

    vm.I = PC_INITIAL_OFFSET;

    execute_bcd_instruction(&vm, &decoded_opcode);

    CU_ASSERT_EQUAL(
        vm.memory.read(&vm.memory, PC_INITIAL_OFFSET),
        1
    );
    CU_ASSERT_EQUAL(
        vm.memory.read(&vm.memory, 1 + PC_INITIAL_OFFSET),
        2
    );
    CU_ASSERT_EQUAL(
        vm.memory.read(&vm.memory, 2 + PC_INITIAL_OFFSET),
        3
    );

    tests_memory_destroy(&vm.memory);
}


void test_execute_display_instruction(){
    Chip8VM vm = {0};
    DecodedOpcode decoded_opcode = {0};
    vm.memory = tests_memory_construct();

    vm.memory.write(&vm.memory, PC_INITIAL_OFFSET, 0xF0);
    
    /*
    Draw:

    | ****---- |
    
    */

    vm.I = PC_INITIAL_OFFSET;
    decoded_opcode.decode_class = 0xD;
    decoded_opcode.vx = 0;
    decoded_opcode.vy = 0;
    decoded_opcode.constant = 1;
    
    execute_display_instruction(&vm, &decoded_opcode); 
    for(int i = 0; i < 8; i++){
        if(i < 4){
            CU_ASSERT_EQUAL(
                vm.display[i],
                1
            );
        }
        else{ 
            CU_ASSERT_EQUAL(
                vm.display[i], 
                0
            );
        }
    }

    tests_memory_destroy(&vm.memory);
}

