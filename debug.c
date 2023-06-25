#include <stdio.h>
#include <stdint.h>
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
        for(int j = 0; j < num_bytes_to_print; j++){
            printf("%02X ", memory[(i * num_bytes_to_print) + j]);
            if(j == 15){
                printf(" ");
            }
        }
        printf("\n");
        bytes_counter += num_bytes_to_print;
    }
}

void test(){
    // memory test 
    memory mem;
    memory_init(&mem);
    memory_set(&mem, 32, 0x20);
    memory_set(&mem, 13, 0x83);
    memory_set(&mem, 10, 0x10);
    memory_set(&mem, 63, 0xaa);
    memory_set(&mem, 64, 0x64);
    memory_set(&mem, 65, 0x65);

    printf("at address 32 - %04x\n", memory_get_one_byte(&mem, 32));
    printf("at address 13 - %04x\n", memory_get_one_byte(&mem, 13));
    printf("at address 10 - %04x\n", memory_get_one_byte(&mem, 10));
    printf("at address 63 - %04x\n", memory_get_one_byte(&mem, 63));
    printf("at address 64 and 65 - %04x\n", memory_get_two_bytes(&mem, 64));
    dump_memory(mem.ram, 97);
}