#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
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
    cpu_ctx->stack_pointer = 16;
}

// memory space starts at 512 or 0x200 in the memory array 
void load_game(cpu *cpu_ctx, uint8_t *game, size_t gamesize){
    memcpy(&cpu_ctx->memory.ram[512], game, gamesize);
    cpu_ctx->program_counter = 512;
}

void push(cpu *cpu_ctx, uint16_t value){
    if(cpu_ctx->stack_pointer <= 0){
        printf("SP <= 0 -- SP = %u\n", cpu_ctx->stack_pointer);
        return;
    }
    cpu_ctx->stack_pointer--;
    cpu_ctx->memory.stack[cpu_ctx->stack_pointer] = value;
}

uint16_t pop(cpu *cpu_ctx){
    if(cpu_ctx->stack_pointer >= 16){
        printf("SP >= 16 -- SP = %u\n", cpu_ctx->stack_pointer);
        return 0;
    }
    uint16_t item = cpu_ctx->memory.stack[cpu_ctx->stack_pointer];
    // propbably not necessary as this will simply be over written when stack pointer moves here again 
    // but it makes printing stack better
    cpu_ctx->memory.stack[cpu_ctx->stack_pointer] = 0; 
    cpu_ctx->stack_pointer++;
    return item;
}

void print_stack(cpu *cpu_ctx){
    for(int i = 15; i >= 0; i--){
        printf("0x%04X: %04X\n", i, cpu_ctx->memory.stack[i]);
    }
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
    int nnn = (opcode & 0xFFF);
    int x = (opcode & 0x0F00) >> 8;
    int y = (opcode & 0x00F0) >> 4;
    int kk = (opcode & 0x00FF);
    int n = (opcode & 0x000F);
    int sig_bit = 0;
    
    Instruction instr = decode(opcode);
    cpu_ctx->program_counter += 2;
    
    switch (instr) {
        case OP_00E0:
            // Clear the display
            init_display(&cpu_ctx->display);
            break;

        case OP_00EE:
            // Return from a subroutine
            cpu_ctx->program_counter = pop(cpu_ctx);
            break;

        case OP_1nnn:
            // Jump to address nnn
            cpu_ctx->program_counter = nnn;
            break;

        case OP_2nnn:
            // Call subroutine at address nnn
            push(cpu_ctx, cpu_ctx->program_counter);
            cpu_ctx->program_counter = nnn;
            break;

        case OP_3xkk:
            // Skip next instruction if Vx == kk
            if(cpu_ctx->V[x] == kk){
                cpu_ctx->program_counter += 2;
            }
            break;

        case OP_4xkk:
            // Skip next instruction if Vx != kk
            if(cpu_ctx->V[x] != kk){
                cpu_ctx->program_counter +=2;
            }
            break;

        case OP_5xy0:
            // Skip next instruction if Vx == Vy
            if(cpu_ctx->V[x] == cpu_ctx->V[y]){
                cpu_ctx->program_counter +=2;
            }
            break;
        //my current change.
        case OP_6xkk:
            // Set Vx = kk
            cpu_ctx->V[x] = kk;
            break;

        case OP_7xkk:
            // Set Vx = Vx + kk
            cpu_ctx->V[x] += kk;
            break;

        case OP_8xy0:
            // Set Vx = Vy
            cpu_ctx->V[x] = cpu_ctx->V[y];
            break;

        case OP_8xy1:
            // Set Vx = Vx OR Vy
            cpu_ctx->V[x] = (cpu_ctx->V[x] | cpu_ctx->V[y]);
            break;

        case OP_8xy2:
            // Set Vx = Vx AND Vy
            cpu_ctx->V[x] = (cpu_ctx->V[x] & cpu_ctx->V[y]);
            break;

        case OP_8xy3:
            // Set Vx = Vx XOR Vy
            cpu_ctx->V[x]= (cpu_ctx->V[x] ^ cpu_ctx->V[y]);
            break;

        case OP_8xy4:
            // Set Vx = Vx + Vy, set VF = carry
            if ((cpu_ctx->V[x] + cpu_ctx->V[y])>0xFF){
                cpu_ctx->V[0xF] = 1;
            }else{
                cpu_ctx->V[0xF] = 0;
            }
            cpu_ctx->V[x] = 0xFF & (cpu_ctx->V[x] + cpu_ctx->V[y]);
            break;

        case OP_8xy5:
            // Set Vx = Vx - Vy, set VF = NOT borrow
            //If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.
            if(cpu_ctx->V[x] > cpu_ctx->V[y]) {
                cpu_ctx->V[0xF] = 1;
            }
            else {
                cpu_ctx->V[0xF] = 0;
            }

            cpu_ctx->V[x] = cpu_ctx->V[x] - cpu_ctx->V[y];
            break;

        case OP_8xy6:
            // Set Vx = Vx SHR 1
            //If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2.
            // 11010001
            // 00000001
            // ---------
            // 00000001

            sig_bit = cpu_ctx->V[x] & 0x1;
            if(sig_bit) {
                cpu_ctx->V[0xF] = 1;
            }
            else {
                cpu_ctx->V[0xF] = 0;
            }

            cpu_ctx->V[x] = cpu_ctx->V[x] / 2;

            break;

        case OP_8xy7:
            // Set Vx = Vy - Vx, set VF = NOT borrow
            //If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
            if(cpu_ctx->V[y] > cpu_ctx->V[x]) {
                cpu_ctx->V[0xF] = 1;
            }
            else {
                cpu_ctx->V[0xF] = 0;
            }

            cpu_ctx->V[x] = cpu_ctx->V[y] - cpu_ctx->V[x];
            break;

        case OP_8xyE:
            // Set Vx = Vx SHL 1
            //If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.
            sig_bit = cpu_ctx->V[x] & 0x80;  //0x80 b/c 10000000 is 0x80 (in hex)
            if(sig_bit) {
                cpu_ctx->V[0xF] = 1;
            }
            else {
                cpu_ctx->V[0xF] = 0;
            }

            cpu_ctx->V[x] = cpu_ctx->V[x] * 2;
            break;

        case OP_9xy0:
            // Skip next instruction if Vx != Vy
            if(cpu_ctx->V[x] != cpu_ctx->V[y]) {
                cpu_ctx->program_counter += 2;
            }
            break;

        case OP_Annn:
            // Set I = nnn
            //The value of register I is set to nnn.
            cpu_ctx->I = nnn;
            break;

        case OP_Bnnn:
            // Jump to location nnn + V0
            nnn = opcode & 0x0FFF;
            cpu_ctx->program_counter= cpu_ctx->V[0x0]+nnn;
            break;

        case OP_Cxkk:
            // Set Vx = random byte AND kk
            srand(time(NULL));
            cpu_ctx->V[x] = (rand() % 256) & kk;
            break;

        case OP_Dxyn:
            // Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision
            cpu_ctx->V[0xF] = draw_sprite(&cpu_ctx->display, cpu_ctx->V[x], cpu_ctx->V[y], &cpu_ctx->memory.ram[cpu_ctx->I], n);
            break;

        case OP_Ex9E:
            // Skip next instruction if key with the value of Vx is pressed
            if(key_current_state(&cpu_ctx->input, cpu_ctx->V[x])){ // how is key stored in register?
                cpu_ctx->program_counter += 2;
            }
            break;

        case OP_ExA1:
            // Skip next instruction if key with the value of Vx is not pressed
            if(!key_current_state(&cpu_ctx->input, cpu_ctx->V[x])){ // how is key stored in register?
                cpu_ctx->program_counter += 2;
            }
            break;

        case OP_Fx07:
            // Set Vx = delay timer value
            //The value of DT is placed into Vx.
            cpu_ctx->V[x] = cpu_ctx->delay_timer;
            break;

        case OP_Fx0A:
            // Wait for a key press, store the value of the key in Vx
            break;

        case OP_Fx15:
            // Set delay timer = Vx
            //DT is set equal to the value of Vx.
            cpu_ctx->delay_timer = cpu_ctx->V[x];
            break;

        case OP_Fx18:
            // Set sound timer = Vx
            //ST is set equal to the value of Vx.
            cpu_ctx->sound_timer = cpu_ctx->V[x];
            break;

        case OP_Fx1E:
            // Set I = I + Vx
            //The values of I and Vx are added, and the results are stored in I.
            cpu_ctx->I = cpu_ctx->I + cpu_ctx->V[x];
            break;

        case OP_Fx29:
            // Set I = location of sprite for digit Vx
            cpu_ctx->I = cpu_ctx->V[x];
            break;

        case OP_Fx33:
            // Store BCD representation of Vx in memory locations I, I+1, and I+2
            // The interpreter takes the decimal value of Vx, and places the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.
            memset(&cpu_ctx->memory.ram[cpu_ctx->I], cpu_ctx->V[x]/100, 1);
            memset(&cpu_ctx->memory.ram[cpu_ctx->I + 1], ((cpu_ctx->V[x] / 10) % 10), 1);
            memset(&cpu_ctx->memory.ram[cpu_ctx->I + 2], ( cpu_ctx->V[x]% 10), 1);
            // memory_set(&cpu_ctx->memory, cpu_ctx->I, cpu_ctx->V[x] / 100);
            // memory_set(&cpu_ctx->memory, cpu_ctx->I + 1, ( (cpu_ctx->V[x] / 10) % 10));
            // memory_set(&cpu_ctx->memory, cpu_ctx->I + 2, ( cpu_ctx->V[x]% 10));
            break;

        case OP_Fx55:
            // Store registers V0 through Vx in memory starting at location I
            //The interpreter copies the values of registers V0 through Vx into memory, starting at the address in I.

            memcpy(&cpu_ctx->memory.ram[cpu_ctx->I], cpu_ctx->V, x);
            break;

        case OP_Fx65:
            // Read registers V0 through Vx from memory starting at location I
            //The interpreter reads values from memory starting at location I into registers V0 through Vx.

            memcpy(cpu_ctx->V, &cpu_ctx->memory.ram[cpu_ctx->I], x);
            break;

        case UNKNOWN:
            // Unknown instruction
            printf("ERROR: unknown opcode - %u\n", opcode);
            break;
    }   
}
