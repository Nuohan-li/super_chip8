#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "cpu.h"
#include "display.h"

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

///////////////////////////////////////////////////////////////////////////////////
// 
//                          INSTRUCTIONS
//
//////////////////////////////////////////////////////////////////////////////////

// 00E0
void cls_display(cpu *cpu){
    init_display(&cpu->display);
}

Instruction decode_opcode(uint16_t opcode) {
    if (opcode == 0x00E0) {
        return OP_00E0;
    } 
    else if (opcode == 0x00EE) {
        return OP_00EE;
    }
    else if ((opcode & 0xF000) == 0x1000) {
        return OP_1nnn;
    }
    else if ((opcode & 0xF000) == 0x2000) {
        return OP_2nnn;
    }
    else if ((opcode & 0xF000) == 0x3000) {
        return OP_3xkk;
    }
    else if ((opcode & 0xF000) == 0x4000) {
        return OP_4xkk;
    }
    else if ((opcode & 0xF000) == 0x5000) {
        return OP_5xy0;
    }
    else if ((opcode & 0xF000) == 0x6000) {
        return OP_6xkk;
    }
    else if ((opcode & 0xF000) == 0x7000) {
        return OP_7xkk;
    }
    else if ((opcode & 0xF000) == 0x8000) {
        uint16_t code = opcode & 0xF00F;
        switch(code) {
            case 0x8000:
                return OP_8xy0;
            case 0x8001:
                return OP_8xy1;
            case 0x8002:
                return OP_8xy2;
            case 0x8003:
                return OP_8xy3;
            case 0x8004:
                return OP_8xy4;
            case 0x8005:
                return OP_8xy5;
            case 0x8006:
                return OP_8xy6;
            case 0x8007:
                return OP_8xy7;
            case 0x800E:
                return OP_8xyE;
            default:
                return UNKNOWN_INSTRUCTION;
        }
    }
    else if ((opcode & 0xF000) == 0x9000) {
        return OP_9xy0;
    }
    else if ((opcode & 0xF000) == 0xA000) {
        return OP_Annn;
    }
    else if ((opcode & 0xF000) == 0xB000) {
        return OP_Bnnn;
    }
    else if ((opcode & 0xF000) == 0xC000) {
        return OP_Cxkk;
    }
    else if ((opcode & 0xF000) == 0xD000) {
        return OP_Dxyn;
    }
    else if ((opcode & 0xF0FF) == 0xE09E) {
        return OP_Ex9E;
    }
    else if ((opcode & 0xF0FF) == 0xE0A1) {
        return OP_ExA1;
    }
    else if ((opcode & 0xF0FF) == 0xF007) {
        return OP_Fx07;
    }
    else if ((opcode & 0xF0FF) == 0xF00A) {
        return OP_Fx0A;
    }
    else if ((opcode & 0xF0FF) == 0xF015) {
        return OP_Fx15;
    }
    else if ((opcode & 0xF0FF) == 0xF018) {
        return OP_Fx18;
    }
    else if ((opcode & 0xF0FF) == 0xF01E) {
        return OP_Fx1E;
    }
    else if ((opcode & 0xF0FF) == 0xF029) {
        return OP_Fx29;
    }
    else if ((opcode & 0xF0FF) == 0xF033) {
        return OP_Fx33;
    }
    else if ((opcode & 0xF0FF) == 0xF055) {
        return OP_Fx55;
    }
    else if ((opcode & 0xF0FF) == 0xF065) {
        return OP_Fx65;
    }
  
    return UNKNOWN_INSTRUCTION;
}


void execute_opcode(cpu *cpu_ctx, uint16_t opcode){
    printf("Executing opcode: %04X\n", opcode);
    Instruction decoded_opcode = decode_opcode(opcode);
    switch (decoded_opcode){
    case OP_00E0:
        cls_display(&cpu_ctx->display);
        break;
    
    default:
        break;
    }
}

void push(cpu *cpu, uint16_t value){
    cpu->memory.stack[cpu->stack_pointer] = value;
    cpu->stack_pointer++;
}

uint16_t pop(cpu *cpu){
    uint16_t value = cpu->memory.stack[cpu->stack_pointer];
    cpu->stack_pointer--;
    return value;
}