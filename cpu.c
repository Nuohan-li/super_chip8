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