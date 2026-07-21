# CHIP-8_emulator

## About the project

**My first emulator!** I am trying to organize my projects better and use unit tests to feel more confident when adding features to my code, so this is my first project with this kind of organization.

## Usage 

To run it, you have to build it, and you can do this with a bash script that i made, you just have to give a execution permission with `cmod +x build_src.sh`, and run it with, and choose to not build the tests. When its finish enter in the build directory and run the file like that `./chip8Emulator <ROM>`, and if you want to see the assembly of that rom, you can pipe it with `./chip8Emulator <ROM> > assembly.txt`.

## References 

Those are some references that i use to create my project, if you to do a CHIP-8 emulator too, see thoses articles em pages.

- To understand how a CHIP-8 emulator works, see this [guide](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/).
- To get a deeper understanding of the functionality of certain instructions, see the [wiki](https://en.wikipedia.org/wiki/CHIP-8)!
- As a bonus, although it is not specifically about CHIP-8, this [article](https://cliutils.gitlab.io/modern-cmake/) teaches you how to use CMake (it helped me a lot).
- This online [CHIP-8 emulator](https://chipo.ber.gp/) shows the disassembly of a ROM, which helps me debug my code.
