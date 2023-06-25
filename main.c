#include <stdio.h>
#include <stdint.h>
#include "cpu.h"
#include "debug.h"

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

int main(){
    test();
    return 0;
}