#pragma once

#include <stdio.h>
#include <stdint.h>
#include "cpu.h"
#include "disassembler.h"

// dump the content of the memory 
void dump_memory(uint8_t *memory, size_t size_byte);
void dump_register_content(cpu *cpu);
void dump_game_content(char *file_name);
void log_opcode();
decoded_instr disassemble(cpu *cpu_ctx, int address);
void debugger(cpu *cpu_ctx);
void test();