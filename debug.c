#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "debug.h"
#include "memory.h"

// dump the content of the memory 
void dump_memory(uint8_t *memory, size_t size_byte){
    uint16_t bytes_counter = 0;
    int num_of_lines = 0;
    int num_bytes_to_print = 0;
    int remainder = size_byte % 32;
    if(remainder == 0){
        num_of_lines = size_byte / 32;
    } else{
        num_of_lines = size_byte / 32 + 1;
    }
    for(int i = 0; i < num_of_lines; i++){
        printf("%04u     ", bytes_counter);
        if(i == num_of_lines - 1 && remainder != 0){ 
            num_bytes_to_print = remainder;
        } else{
            num_bytes_to_print = 32;
        }
        // printing the hex value 
        for(int j = 0; j < num_bytes_to_print; j++){
            printf("%02X ", memory[(i * num_bytes_to_print) + j]);
            if(j == 15){
                printf(" ");
            }
        }
        printf(" ");
        // upon reaching last line, add padding to hex values so that all characters will align
        if(i == num_of_lines - 1){
            int padding = 32 - num_bytes_to_print;
            for (int j = 0; j < padding; j++) {
                printf("   ");
            }
        }
        // printing characters
        for (int j = 0; j < num_bytes_to_print; j++) {
            uint8_t value = memory[i * 32 + j];
            if (isprint(value)) {
                printf("%c", value);
            } else {
                printf(".");
            }
        }
        printf("\n");
        bytes_counter += num_bytes_to_print;
    }
}

void dump_register_content(cpu *cpu_ctx){
    for(int i = 0; i < 16; i++){
        printf("Register V%d - %02X\n", i, cpu_ctx->V[i]);
    }
    printf("Register I   - %04X\n", cpu_ctx->I);
    printf("Delay timer  - %02X\n", cpu_ctx->delay_timer);
    printf("Sound timer  - %02X\n", cpu_ctx->sound_timer);
    printf("PC           - %04X\n", cpu_ctx->program_counter);
    printf("SP           - %02X\n", cpu_ctx->stack_pointer);
}

void dump_game_content(uint8_t *file_name){
    // loading game into memory space
    printf("file name is: %s\n", file_name);
    // open the file in "rb" mode -> rb = read binary 
    FILE* f = fopen(file_name, "rb");  
    // fseek sets the file pointer to the position "SEEK_END", which is the end of the file
    fseek(f, 0, SEEK_END);
    // ftell returns the current position of the file pointer. It corresponds to the size of the file in bytes because 
    // the file pointer is currently pointing at the end of the file
    long size = ftell(f);
    // SEEK_SET returns the file pointer back to the beginning
    fseek(f, 0, SEEK_SET);

    uint8_t game[size];
    int result = fread(game, size, 1, f);
    dump_memory(game, size);
}

void test(){
    // memory test 
    printf("\n");
    memory mem;
    memory_set(&mem, 32, 0x20);
    memory_set(&mem, 13, 0x83);
    memory_set(&mem, 10, 0x10);
    memory_set(&mem, 63, 0xaa);
    memory_set(&mem, 64, 0x64);
    memory_set(&mem, 65, 0x65);

    printf("at address 32        - %04x\n", memory_get_one_byte(&mem, 32));
    printf("at address 13        - %04x\n", memory_get_one_byte(&mem, 13));
    printf("at address 10        - %04x\n", memory_get_one_byte(&mem, 10));
    printf("at address 63        - %04x\n", memory_get_one_byte(&mem, 63));
    printf("at address 64 and 65 - %04x\n", memory_get_two_bytes(&mem, 64));
    dump_memory(mem.ram, 97);
    printf("printing the entire memory content\n");
    dump_memory(mem.ram, CHIP8_RAM_SIZE_BYTES);
    printf("initializing memory\n");
    memory_init(&mem);
    dump_memory(mem.ram, CHIP8_RAM_SIZE_BYTES);
    printf("\n\n");

    // CPU registers 
    cpu cpu_ctx;
    cpu_init(&cpu_ctx);
    dump_register_content(&cpu_ctx);
    printf("\n");
    uint64_t val = 0x1122334455667788; // my linux is little endian
    memcpy(cpu_ctx.V, &val, sizeof(uint64_t));
    cpu_ctx.I = 0x9870;
    cpu_ctx.stack_pointer = 0x12;
    dump_register_content(&cpu_ctx);
    printf("\n\n");
}