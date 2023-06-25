#pragma once

#include <stdio.h>
#include <stdint.h>
#include "cpu.h"


// dump the content of the memory 
void dump_memory(uint8_t *memory, size_t size_byte);
void dump_register_content(cpu *cpu);
void log_opcode();
void test();