#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "memory.h"

void memory_init(memory *mem){
    memset(mem, 0, CHIP8_RAM_SIZE_BYTES);
}

void memory_set(memory *mem, int address, uint8_t value){
    mem->ram[address] = value;
}

uint8_t memory_get_one_byte(memory *mem, int address){
    return mem->ram[address];
}

uint16_t memory_get_two_bytes(memory *mem, int address){
    uint16_t two_bytes = 0;
    uint8_t byte1 = memory_get_one_byte(mem, address);
    uint8_t byte2 = memory_get_one_byte(mem, address + 1);
    two_bytes = (byte1 << 8) | byte2; 
    return two_bytes;
}