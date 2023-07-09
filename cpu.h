// https://github.com/mattmikolay/chip-8/wiki/Mastering-CHIP%E2%80%908

#pragma once

#include <stdio.h>
#include <stdint.h>
#include "memory.h"
#include "display.h"
#include "input.h"

// this struct emulates the registers -> section 2.2 in the reference
typedef struct cpu{
    // V array represents 16 one byte general purpose registers used by CHIP8
    uint8_t V[16];
    // special 16 bit register in chip-8, used to store memory address
    uint16_t I;
    // see section 2.5 reference
    uint8_t delay_timer;
    // see section 2.5 reference
    uint8_t sound_timer;
    // 16bit, points to the next instruction that will be run after the current one
    uint16_t program_counter;
    // 8 bit, points to the topmost level of the stack
    uint8_t stack_pointer;

    // different components defined in other header files
    input input;
    memory memory;
    display display;

} cpu;

typedef enum Instruction{
    OP_00E0,  // Clear the display
    OP_00EE,  // Return from a subroutine
    OP_1nnn,  // Jump to address nnn
    OP_2nnn,  // Call subroutine at address nnn
    OP_3xkk,  // Skip next instruction if Vx == kk
    OP_4xkk,  // Skip next instruction if Vx != kk
    OP_5xy0,  // Skip next instruction if Vx == Vy
    OP_6xkk,  // Set Vx = kk
    OP_7xkk,  // Set Vx = Vx + kk
    OP_8xy0,  // Set Vx = Vy
    OP_8xy1,  // Set Vx = Vx OR Vy
    OP_8xy2,  // Set Vx = Vx AND Vy
    OP_8xy3,  // Set Vx = Vx XOR Vy
    OP_8xy4,  // Set Vx = Vx + Vy, set VF = carry
    OP_8xy5,  // Set Vx = Vx - Vy, set VF = NOT borrow
    OP_8xy6,  // Set Vx = Vx SHR 1
    OP_8xy7,  // Set Vx = Vy - Vx, set VF = NOT borrow
    OP_8xyE,  // Set Vx = Vx SHL 1
    OP_9xy0,  // Skip next instruction if Vx != Vy
    OP_Annn,  // Set I = nnn
    OP_Bnnn,  // Jump to location nnn + V0
    OP_Cxkk,  // Set Vx = random byte AND kk
    OP_Dxyn,  // Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision
    OP_Ex9E,  // Skip next instruction if key with the value of Vx is pressed
    OP_ExA1,  // Skip next instruction if key with the value of Vx is not pressed
    OP_Fx07,  // Set Vx = delay timer value
    OP_Fx0A,  // Wait for a key press, store the value of the key in Vx
    OP_Fx15,  // Set delay timer = Vx
    OP_Fx18,  // Set sound timer = Vx
    OP_Fx1E,  // Set I = I + Vx
    OP_Fx29,  // Set I = location of sprite for digit Vx
    OP_Fx33,  // Store BCD representation of Vx in memory locations I, I+1, and I+2
    OP_Fx55,  // Store registers V0 through Vx in memory starting at location I
    OP_Fx65,   // Read registers V0 through Vx from memory starting at location I
    UNKNOWN_INSTRUCTION
} Instruction;


// initialize the CPU -> set everything to 0
void cpu_init(cpu *cpu);

// load th game into the memory 
void load_game(cpu *cpu, uint8_t *game, size_t gamesize);

void execute_opcode(cpu *cpu, uint16_t opcode);

void push(cpu *cpu, uint16_t value);

uint16_t pop(cpu *cpu);