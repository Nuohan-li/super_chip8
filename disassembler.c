#include <stdio.h>
#include <stdint.h>
#include "disassembler.h"

Instruction decode(uint16_t opcode) {
   
    if (opcode == 0x00E0) {
        return OP_00E0;
    } 
    else if (opcode == 0x00EE) {
        return OP_00EE;
    }
    else if ((opcode & 0xF000) == 0x1000) { // 1nnn
        return OP_1nnn;
    }
    else if ((opcode & 0xF000) == 0x2000) { // 2nnn 
        return OP_2nnn;
    }
    else if ((opcode & 0xF000) == 0x3000) { // 3xkk
        return OP_3xkk;
    }
    else if ((opcode & 0xF000) == 0x4000) { // 4xkk
        return OP_4xkk;
    }
    else if ((opcode & 0xF000) == 0x5000) { // 5xy0
        return OP_5xy0;
    }
    else if ((opcode & 0xF000) == 0x6000) { // 6xkk
        return OP_6xkk;
    }
    else if ((opcode & 0xF000) == 0x7000) { // 7xkk
        return OP_7xkk;
    }
    else if ((opcode & 0xF000) == 0x8000) { // 
        uint16_t code = opcode & 0xF00F;
        switch(code) {
            case 0x8000: // 8xy0
                return OP_8xy0;  
            case 0x8001: // 8xy1
                return OP_8xy1;  
            case 0x8002: // 8xy2
                return OP_8xy2;
            case 0x8003: // 8xy3
                return OP_8xy3;
            case 0x8004: // 8xy4
                return OP_8xy4;
            case 0x8005: // 8xy5
                return OP_8xy5;
            case 0x8006: // 8xy6
                return OP_8xy6;
            case 0x8007: // 8xy7
                return OP_8xy7;
            case 0x800E: // 8xyE
                return OP_8xyE;
            default:
                return UNKNOWN;
        }
    }
    else if ((opcode & 0xF000) == 0x9000) { // 9xy0
        return OP_9xy0;
    }
    else if ((opcode & 0xF000) == 0xA000) { // Annn
        return OP_Annn;
    }
    else if ((opcode & 0xF000) == 0xB000) { // Bnnn
        return OP_Bnnn;
    }
    else if ((opcode & 0xF000) == 0xC000) { // Cxkk
        // if(opcode == 0xC0C0){

        // }
        return OP_Cxkk;
    }
    else if ((opcode & 0xF000) == 0xD000) { // Dxyn
        return OP_Dxyn;
    }
    else if ((opcode & 0xF0FF) == 0xE09E) { // Ex9E
        return OP_Ex9E;
    }
    else if ((opcode & 0xF0FF) == 0xE0A1) { // ExA1
        return OP_ExA1;
    }
    else if ((opcode & 0xF0FF) == 0xF007) { // Fx07
        return OP_Fx07;
    }
    else if ((opcode & 0xF0FF) == 0xF00A) { // Fx0A
        return OP_Fx0A;
    }
    else if ((opcode & 0xF0FF) == 0xF015) { // Fx15
        return OP_Fx15;
    }
    else if ((opcode & 0xF0FF) == 0xF018) { // Fx18
        return OP_Fx18;
    }
    else if ((opcode & 0xF0FF) == 0xF01E) { // Fx1E
        return OP_Fx1E;
    }
    else if ((opcode & 0xF0FF) == 0xF029) { // Fx29
        return OP_Fx29;
    }
    else if ((opcode & 0xF0FF) == 0xF033) { // Fx33
        return OP_Fx33;
    }
    else if ((opcode & 0xF0FF) == 0xF055) { // Fx55
        return OP_Fx55;
    }
    else if ((opcode & 0xF0FF) == 0xF065) { // Fx65
        return OP_Fx65;
    }
  
    return UNKNOWN;
}