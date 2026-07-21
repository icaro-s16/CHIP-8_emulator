#include "chip8_emulator.h"

int main(
    int argc, 
    char** argv
){
    ulong op_per_sec = 700;

    if (argc > 3){
        fprintf(
            stderr, 
            "ERROR: Incorrect usage. The correct usage is \"./<bin> <rom path> <operation per sec>\"..\n"
        );
        exit(1);
    }

    if (argc < 3)
        printf("INFO: The emulator will use 700 operation per sec, you can change it passing the desired value after \"./<bin> <rom path> <operation per sec>\"..\n");
    else if (
        sscanf(argv[2], "%lu", &op_per_sec) != 1
    ){
        fprintf(
            stderr, 
            "ERROR: Invalid command, expected to find a ulong and found \"%s\"..\"\n", 
            argv[2]
        );
        exit(1);
    }

    chip8_emulator_run(
        "/home/icaro_s/projects/C_family/CHIP-8_emulator/assets/roms/2-ibm-logo.ch8", 
        op_per_sec
    );

    return 0;
}
