#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "cpu.h"

// initialize the CPU -> set everything to 0
void cpu_init(cpu *cpu_ctx){
    memset(cpu_ctx, 0, sizeof(cpu));
}

// memory space starts at 512 or 0x200 in the memory array 
void load_game(cpu *cpu_ctx, uint8_t *game, size_t gamesize){
    memcpy(&cpu_ctx->memory.ram[512], game, gamesize);
    cpu_ctx->program_counter = 512;
}

void execute_opcode(cpu *cpu_ctx, uint16_t opcode){
    printf("Executing opcode: %04X\n", opcode);
    int first_digit = (opcode >> 12);
    switch(first_digit){
        case 0:
            break;
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
            int x = (opcode & 0x0F00) >> 8; 
            int kk = opcode & 0xFF;
            cpu_ctx->V[x] = kk;
        }
    }
}