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

void push(cpu *cpu, uint16_t value){
    cpu->memory.stack[cpu->stack_pointer] = value;
    cpu->stack_pointer++;
}

uint16_t pop(cpu *cpu){
    uint16_t value = cpu->memory.stack[cpu->stack_pointer];
    cpu->stack_pointer--;
    return value;
}

///////////////////////////////////////////////////////////////////////////////////
// 
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

    if (opcode == 0x00E0) {
        cls_display(cpu_ctx);
    } 
    else if (opcode == 0x00EE) {
        return ;
    }
    else if ((opcode & 0xF000) == 0x1000) { // 1nnn
        return ;
    }
    else if ((opcode & 0xF000) == 0x2000) { // 2nnn 
        return ;
    }
    else if ((opcode & 0xF000) == 0x3000) { // 3xkk
        return ;
    }
    else if ((opcode & 0xF000) == 0x4000) { // 4xkk
        return ;
    }
    else if ((opcode & 0xF000) == 0x5000) { // 5xy0
        return ;
    }
    else if ((opcode & 0xF000) == 0x6000) { // 6xkk
        return ;
    }
    else if ((opcode & 0xF000) == 0x7000) { // 7xkk
        return ;
    }
    else if ((opcode & 0xF000) == 0x8000) { // 
        uint16_t code = opcode & 0xF00F;
        switch(code) {
            case 0x8000: // 8xy0
                return ;  
            case 0x8001: // 8xy1
                return ;  
            case 0x8002: // 8xy2
                return ;
            case 0x8003: // 8xy3
                return ;
            case 0x8004: // 8xy4
                return ;
            case 0x8005: // 8xy5
                return ;
            case 0x8006: // 8xy6
                return ;
            case 0x8007: // 8xy7
                return ;
            case 0x800E: // 8xyE
                return ;
            default:
                return ;
        }
    }
    else if ((opcode & 0xF000) == 0x9000) { // 9xy0
        return ;
    }
    else if ((opcode & 0xF000) == 0xA000) { // Annn
        return ;
    }
    else if ((opcode & 0xF000) == 0xB000) { // Bnnn
        return ;
    }
    else if ((opcode & 0xF000) == 0xC000) { // Cxkk
        return ;
    }
    else if ((opcode & 0xF000) == 0xD000) { // Dxyn
        return ;
    }
    else if ((opcode & 0xF0FF) == 0xE09E) { // Ex9E
        return ;
    }
    else if ((opcode & 0xF0FF) == 0xE0A1) { // ExA1
        return ;
    }
    else if ((opcode & 0xF0FF) == 0xF007) { // Fx07
        return ;
    }
    else if ((opcode & 0xF0FF) == 0xF00A) { // Fx0A
        return ;
    }
    else if ((opcode & 0xF0FF) == 0xF015) { // Fx15
        return ;
    }
    else if ((opcode & 0xF0FF) == 0xF018) { // Fx18
        return ;
    }
    else if ((opcode & 0xF0FF) == 0xF01E) { // Fx1E
        return ;
    }
    else if ((opcode & 0xF0FF) == 0xF029) { // Fx29
        return ;
    }
    else if ((opcode & 0xF0FF) == 0xF033) { // Fx33
        return ;
    }
    else if ((opcode & 0xF0FF) == 0xF055) { // Fx55
        return ;
    }
    else if ((opcode & 0xF0FF) == 0xF065) { // Fx65
        return ;
    }
  
    return ;
}
