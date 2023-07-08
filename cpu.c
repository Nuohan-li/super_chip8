#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "cpu.h"

const uint8_t default_character_set[] = {
    0xf0, 0x90, 0x90, 0x90, 0xf0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xf0, 0x10, 0xf0, 0x80, 0xf0, // 2
    0xf0, 0x10, 0xf0, 0x10, 0xf0, // 3
    0x90, 0x90, 0xf0, 0x10, 0x10, // 4
    0xf0, 0x80, 0xf0, 0x10, 0xf0, // 5
    0xf0, 0x80, 0xf0, 0x90, 0xf0, // 6
    0xf0, 0x10, 0x20, 0x40, 0x40, // 7
    0xf0, 0x90, 0xf0, 0x90, 0xf0, // 8
    0xf0, 0x90, 0xf0, 0x10, 0xf0, // 9
    0xf0, 0x90, 0xf0, 0x90, 0x90, // a
    0xe0, 0x90, 0xe0, 0x90, 0xe0, // b 
    0xf0, 0x80, 0x80, 0x80, 0xf0, // c
    0xe0, 0x90, 0x90, 0x90, 0xe0, // d
    0xf0, 0x80, 0xf0, 0x80, 0xf0, // e
    0xf0, 0x80, 0xf0, 0x80, 0x80  // f
};

// initialize the CPU -> set everything to 0
void cpu_init(cpu *cpu_ctx){
    memset(cpu_ctx, 0, sizeof(cpu));
    memcpy(cpu_ctx->memory.ram, default_character_set, sizeof(default_character_set));
}

// memory space starts at 512 or 0x200 in the memory array 
void load_game(cpu *cpu_ctx, uint8_t *game, size_t gamesize){
    memcpy(&cpu_ctx->memory.ram[512], game, gamesize);
    cpu_ctx->program_counter = 512;
}

void execute_opcode(cpu *cpu_ctx, uint16_t opcode){
    printf("Executing opcode: %04X\n", opcode);
    int first_digit = (opcode >> 12);
    int x = (opcode >> 8) & 0x000F; 
    int kk = opcode & 0xFF;
    switch(first_digit){
        // I think I will remove case 0 since the only intructions that begin with 00E0 and 00EE
        // they are static, and do not contain values that may change
        case 0x00E0:
            break;
        case 0x00EE:
            break;
        // case 0:
        //     break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6: {
            
            cpu_ctx->V[x] = kk;
        }
    }
}