#include "chip8_emulator.h"

int main(
    int argc, 
    char** argv
){
    if (argc > 2){
        fprintf(stderr, "ERROR: Incorrect usage. The correct usage is \"./<bin> <rom path>.ch8\"\n");
        exit(1);
    }

    srand(time(NULL));

    printf("INFO: If you are using a relative path, try placing the file in the \"roms/\" directory..\n");
    
    chip8_emulator_run(argv[1]);

    return 0;
}
