#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "cpu.h"
#include "display.h"
#include "disassembler.h"

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

void push(cpu *cpu, uint16_t value){
    cpu->memory.stack[cpu->stack_pointer] = value;
    cpu->stack_pointer++;
}

uint16_t pop(cpu *cpu){
    cpu->stack_pointer--;
    return cpu->memory.stack[cpu->stack_pointer];
}

///////////////////////////////////////////////////////////////////////////////////
//void


//                          INSTRUCTIONS
//
//////////////////////////////////////////////////////////////////////////////////

// 00E0
void cls_display(cpu *cpu_ctx){
    init_display(&cpu_ctx->display);
}

void execute_opcode(cpu *cpu_ctx, uint16_t opcode) {
    printf("Executing opcode: %04X\n", opcode);
    int nnn;
    int x;
    int y;
    int kk;
    int n;
    
    Instruction instr = decode(opcode);
    
    switch (instr) {
        case OP_00E0:
            // Clear the display
            break;

        case OP_00EE:
            // Return from a subroutine
            break;

        case OP_1nnn:
            // Jump to address nnn
            break;

        case OP_2nnn:
            // Call subroutine at address nnn
            break;

        case OP_3xkk:
            // Skip next instruction if Vx == kk
            break;

        case OP_4xkk:
            // Skip next instruction if Vx != kk
            break;

        case OP_5xy0:
            // Skip next instruction if Vx == Vy
            break;
        //my current change.
        case OP_6xkk:
            // Set Vx = kk
            kk = (opcode & 0x00FF);
            x = (opcode & 0x0F00) >> 8;
            cpu_ctx->V[x] = kk;
            break;

        case OP_7xkk:
            // Set Vx = Vx + kk
            kk = (opcode & 0x00FF);
            x = (opcode & 0x0F00) >> 8;
            cpu_ctx->V[x] += kk;
            break;

        case OP_8xy0:
            // Set Vx = Vy
            kk = (opcode & 0x00F0);
            x = (opcode & 0x0F00) >> 8;
            y = (opcode & 0x00F0) >> 4;
            cpu_ctx->V[x] = cpu_ctx->V[y];
            break;

        case OP_8xy1:
            // Set Vx = Vx OR Vy
            x = (opcode & 0x0F00) >> 8;
            y = (opcode & 0x00F0) >> 4;
            cpu_ctx->V[x] = (cpu_ctx->V[x] | cpu_ctx->V[y]);
            break;

        case OP_8xy2:
            // Set Vx = Vx AND Vy
            x = (opcode & 0x0F00) >> 8;
            y = (opcode & 0x00F0) >> 4;
            cpu_ctx->V[x] = (cpu_ctx->V[x] & cpu_ctx->V[y]);
            break;

        case OP_8xy3:
            // Set Vx = Vx XOR Vy
            break;

        case OP_8xy4:
            // Set Vx = Vx + Vy, set VF = carry
            break;

        case OP_8xy5:
            // Set Vx = Vx - Vy, set VF = NOT borrow
            break;

        case OP_8xy6:
            // Set Vx = Vx SHR 1
            break;

        case OP_8xy7:
            // Set Vx = Vy - Vx, set VF = NOT borrow
            break;

        case OP_8xyE:
            // Set Vx = Vx SHL 1
            break;

        case OP_9xy0:
            // Skip next instruction if Vx != Vy
            break;

        case OP_Annn:
            // Set I = nnn
            break;

        case OP_Bnnn:
            // Jump to location nnn + V0
            break;

        case OP_Cxkk:
            // Set Vx = random byte AND kk
            break;

        case OP_Dxyn:
            // Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision
            break;

        case OP_Ex9E:
            // Skip next instruction if key with the value of Vx is pressed
            break;

        case OP_ExA1:
            // Skip next instruction if key with the value of Vx is not pressed
            break;

        case OP_Fx07:
            // Set Vx = delay timer value
            break;

        case OP_Fx0A:
            // Wait for a key press, store the value of the key in Vx
            break;

        case OP_Fx15:
            // Set delay timer = Vx
            break;

        case OP_Fx18:
            // Set sound timer = Vx
            break;

        case OP_Fx1E:
            // Set I = I + Vx
            break;

        case OP_Fx29:
            // Set I = location of sprite for digit Vx
            break;

        case OP_Fx33:
            // Store BCD representation of Vx in memory locations I, I+1, and I+2
            break;

        case OP_Fx55:
            // Store registers V0 through Vx in memory starting at location I
            break;

        case OP_Fx65:
            // Read registers V0 through Vx from memory starting at location I
            break;

        case UNKNOWN:
            // Unknown instruction
            break;
    }    
}
