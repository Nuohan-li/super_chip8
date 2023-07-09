#pragma once

#include <stdio.h>
#include <stdint.h>
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
    UNKNOWN
} Instruction;

typedef struct decoded_instr{
    Instruction opcode;
    char *chip8_instr;
} decoded_instr;

static const decoded_instr instructions[] ={
    {OP_00E0, "CLS (Clear the display)"},
    {OP_00EE, "RET (Return from a subroutine)"},
    {OP_1nnn, "JP NNN (Jump to address NNN)"},
    {OP_2nnn, "CALL NNN (Call subroutine at address NNN)"},
    {OP_3xkk, "SE VX, NN (Skip next instruction if VX equals NN)"},
    {OP_4xkk, "SNE VX, NN (Skip next instruction if VX does not equal NN)"},
    {OP_5xy0, "SE VX, VY (Skip next instruction if VX equals VY)"},
    {OP_6xkk, "LD VX, NN (Set VX to NN)"},
    {OP_7xkk, "ADD VX, NN (Add NN to VX)"},
    {OP_8xy0, "LD VX, VY (Set VX to the value of VY)"},
    {OP_8xy1, "OR VX, VY (Set VX to VX OR VY)"},
    {OP_8xy2, "AND VX, VY (Set VX to VX AND VY)"},
    {OP_8xy3, "XOR VX, VY (Set VX to VX XOR VY)"},
    {OP_8xy4, "ADD VX, VY (Add VY to VX, set VF if there's a carry)"},
    {OP_8xy5, "SUB VX, VY (Subtract VY from VX, set VF if there's no borrow)"},
    {OP_8xy6, "SHR VX {, VY} (Shift VX right by 1, set VF to the least significant bit)"},
    {OP_8xy7, "SUBN VX, VY (Set VX to VY minus VX, set VF if there's no borrow)"},
    {OP_8xyE, "SHL VX {, VY} (Shift VX left by 1, set VF to the most significant bit)"},
    {OP_9xy0, "SNE VX, VY (Skip next instruction if VX does not equal VY)"},
    {OP_Annn, "LD I, NNN (Set I to the address NNN)"},
    {OP_Bnnn, "JP V0, NNN (Jump to address NNN plus V0)"},
    {OP_Cxkk, "RND VX, NN (Set VX to a random number AND NN)"},
    {OP_Dxyn, "DRW VX, VY, N (Draw sprite at (VX, VY) with width 8 pixels and height N pixels)"},
    {OP_Ex9E, "SKP VX (Skip next instruction if key with the value of VX is pressed)"},
    {OP_ExA1, "SKNP VX (Skip next instruction if key with the value of VX is not pressed)"},
    {OP_Fx07, "LD VX, DT (Set VX to the value of the delay timer)"},
    {OP_Fx0A, "LD VX, K (Wait for a key press and store the value of the key in VX)"},
    {OP_Fx15, "LD DT, VX (Set the delay timer to the value of VX)"},
    {OP_Fx18, "LD ST, VX (Set the sound timer to the value of VX)"},
    {OP_Fx1E, "ADD I, VX (Add the value of VX to I)"},
    {OP_Fx29, "LD F, VX (Set I to the location of the sprite for the character in VX)"},
    {OP_Fx33, "LD B, VX (Store the binary-coded decimal representation of VX in memory)"},
    {OP_Fx55, "LD [I], VX (Store V0 to VX in memory starting at address I)"},
    {OP_Fx65, "LD VX, [I] (Fill V0 to VX with values from memory starting at address I)"},
    {UNKNOWN, "Unknown (likely sprite data)"}
};

Instruction decode(uint16_t opcode);

