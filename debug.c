#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "debug.h"
#include "memory.h"
#include "disassembler.h"


#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define LE16TOBE16(value) ((value) >> 8) | ((value) << 8)
#else 
    #define LE16TOBE16(value) value
#endif

// dump the content of the memory 
void dump_memory(uint8_t *memory, size_t size_byte){
    uint16_t bytes_counter = 0;
    int num_of_lines = 0;
    int num_bytes_to_print = 0;
    int remainder = size_byte % 32;
    if(remainder == 0){
        num_of_lines = size_byte / 32;
    } else{
        num_of_lines = size_byte / 32 + 1;
    }
    for(int i = 0; i < num_of_lines; i++){
        printf("%04u     ", bytes_counter);
        if(i == num_of_lines - 1 && remainder != 0){ 
            num_bytes_to_print = remainder;
        } else{
            num_bytes_to_print = 32;
        }
        // printing the hex value 
        for(int j = 0; j < num_bytes_to_print; j++){
            printf("%02X ", memory[(i * num_bytes_to_print) + j]);
            if(j == 15){
                printf(" ");
            }
        }
        printf(" ");
        // upon reaching last line, add padding to hex values so that all characters will align
        if(i == num_of_lines - 1){
            int padding = 32 - num_bytes_to_print;
            for (int j = 0; j < padding; j++) {
                printf("   ");
            }
        }
        // printing characters
        for (int j = 0; j < num_bytes_to_print; j++) {
            uint8_t value = memory[i * 32 + j];
            if (isprint(value)) {
                printf("%c", value);
            } else {
                printf(".");
            }
        }
        printf("\n");
        bytes_counter += num_bytes_to_print;
    }
}

void dump_register_content(cpu *cpu_ctx){
    printf("REGISTERS\n");
    printf("Reg   value\n");
    printf("--------------\n");
    printf("V0     %02X\n", cpu_ctx->V[0]);
    printf("V1     %02X\n", cpu_ctx->V[1]);
    printf("V2     %02X\n", cpu_ctx->V[2]);
    printf("V3     %02X\n", cpu_ctx->V[3]);
    printf("V4     %02X\n", cpu_ctx->V[4]);
    printf("V5     %02X\n", cpu_ctx->V[5]);
    printf("V6     %02X\n", cpu_ctx->V[6]);
    printf("V7     %02X\n", cpu_ctx->V[7]);
    printf("V8     %02X\n", cpu_ctx->V[8]);
    printf("V9     %02X\n", cpu_ctx->V[9]);
    printf("V10    %02X\n", cpu_ctx->V[10]);
    printf("V11    %02X\n", cpu_ctx->V[11]);
    printf("V12    %02X\n", cpu_ctx->V[12]);
    printf("V13    %02X\n", cpu_ctx->V[13]);
    printf("V14    %02X\n", cpu_ctx->V[14]);
    printf("V15    %02X\n", cpu_ctx->V[15]);
    printf("I      %04X\n", cpu_ctx->I);
    printf("DT     %02X\n", cpu_ctx->delay_timer);
    printf("ST     %02X\n", cpu_ctx->sound_timer);
    printf("PC     %04X\n", cpu_ctx->program_counter);
    printf("SP     %02X\n", cpu_ctx->stack_pointer);
}

decoded_instr disassemble(cpu *cpu_ctx, int address){
    // loop through all 35 instructions including UNKNOWN
    uint16_t opcode = memory_get_two_bytes(&cpu_ctx->memory, address);
    for(int i = 0; i < 35; i++){
        if(instructions[i].opcode == decode(opcode)){
            return instructions[i];
        }
    }
    return instructions[34];
}

void dump_registers_and_memory(cpu *cpu_ctx, int address){
    printf("REGISTERS        MEMORY\n");
    printf("Reg   value      loc       value      disassembled opcode\n");
    printf("------------     -------------------------------------------------\n");
    printf("V0:     %02X       %u:      %02X%02X      %s\n", 
        cpu_ctx->V[0], address, cpu_ctx->memory.ram[address], cpu_ctx->memory.ram[address+1], disassemble(cpu_ctx, address).chip8_instr);
    printf("V1:     %02X       %u:      %02X%02X      %s\n", 
        cpu_ctx->V[1], address+2, cpu_ctx->memory.ram[address+2], cpu_ctx->memory.ram[address+3], disassemble(cpu_ctx, address+2).chip8_instr);
    printf("V2:     %02X       %u:      %02X%02X      %s\n", 
        cpu_ctx->V[2], address+4, cpu_ctx->memory.ram[address+4], cpu_ctx->memory.ram[address+5], disassemble(cpu_ctx, address+4).chip8_instr);
    printf("V3:     %02X       %u:      %02X%02X      %s\n", 
        cpu_ctx->V[3], address+6, cpu_ctx->memory.ram[address+6], cpu_ctx->memory.ram[address+7], disassemble(cpu_ctx, address+6).chip8_instr);
    printf("V4:     %02X       %u:      %02X%02X      %s\n", 
        cpu_ctx->V[4], address+8, cpu_ctx->memory.ram[address+8], cpu_ctx->memory.ram[address+9], disassemble(cpu_ctx, address+8).chip8_instr);
    printf("V5:     %02X       %u:      %02X%02X      %s\n", 
        cpu_ctx->V[5], address+10, cpu_ctx->memory.ram[address+10], cpu_ctx->memory.ram[address+11], disassemble(cpu_ctx, address+10).chip8_instr);
    printf("V6:     %02X       %u:      %02X%02X      %s\n", 
        cpu_ctx->V[6], address+12, cpu_ctx->memory.ram[address+12], cpu_ctx->memory.ram[address+13], disassemble(cpu_ctx, address+12).chip8_instr);
    printf("V7:     %02X       %u:      %02X%02X      %s\n", 
        cpu_ctx->V[7], address+14, cpu_ctx->memory.ram[address+14], cpu_ctx->memory.ram[address+15], disassemble(cpu_ctx, address+14).chip8_instr);
    printf("V8:     %02X       %u:      %02X%02X      %s\n", 
        cpu_ctx->V[8], address+16, cpu_ctx->memory.ram[address+16], cpu_ctx->memory.ram[address+17], disassemble(cpu_ctx, address+16).chip8_instr);
    printf("V9:     %02X       %u:      %02X%02X      %s\n", 
        cpu_ctx->V[9], address+18, cpu_ctx->memory.ram[address+18], cpu_ctx->memory.ram[address+19], disassemble(cpu_ctx, address+18).chip8_instr);
    printf("V10:    %02X       %u:      %02X%02X      %s\n", 
        cpu_ctx->V[10], address+20, cpu_ctx->memory.ram[address+20], cpu_ctx->memory.ram[address+21], disassemble(cpu_ctx, address+20).chip8_instr);
    printf("V11:    %02X       %u:      %02X%02X      %s\n", 
        cpu_ctx->V[11], address+22, cpu_ctx->memory.ram[address+22], cpu_ctx->memory.ram[address+23], disassemble(cpu_ctx, address+22).chip8_instr);
    printf("V12:    %02X       %u:      %02X%02X      %s\n", 
        cpu_ctx->V[12], address+24, cpu_ctx->memory.ram[address+24], cpu_ctx->memory.ram[address+25], disassemble(cpu_ctx, address+24).chip8_instr);
    printf("V13:    %02X       %u:      %02X%02X      %s\n", 
        cpu_ctx->V[13], address+26, cpu_ctx->memory.ram[address+26], cpu_ctx->memory.ram[address+27], disassemble(cpu_ctx, address+26).chip8_instr);
    printf("V14:    %02X       %u:      %02X%02X      %s\n", 
        cpu_ctx->V[14], address+28, cpu_ctx->memory.ram[address+28], cpu_ctx->memory.ram[address+29], disassemble(cpu_ctx, address+28).chip8_instr);
    printf("V15:    %02X       %u:      %02X%02X      %s\n", 
        cpu_ctx->V[15], address+30, cpu_ctx->memory.ram[address+30], cpu_ctx->memory.ram[address+31], disassemble(cpu_ctx, address+30).chip8_instr);
    printf("I:      %04X     %u:      %02X%02X      %s\n", 
        cpu_ctx->I, address+32, cpu_ctx->memory.ram[address+32], cpu_ctx->memory.ram[address+33], disassemble(cpu_ctx, address+32).chip8_instr);
    printf("DT:     %02X       %u:      %02X%02X      %s\n", 
        cpu_ctx->delay_timer, address+34, cpu_ctx->memory.ram[address+34], cpu_ctx->memory.ram[address+35], disassemble(cpu_ctx, address+34).chip8_instr);
    printf("ST:     %02X       %u:      %02X%02X      %s\n", 
        cpu_ctx->sound_timer, address+36, cpu_ctx->memory.ram[address+36], cpu_ctx->memory.ram[address+37], disassemble(cpu_ctx, address+36).chip8_instr);
    printf("PC:     %04X     %u:      %02X%02X      %s\n", 
        cpu_ctx->program_counter, address+38, cpu_ctx->memory.ram[address+38], cpu_ctx->memory.ram[address+39], disassemble(cpu_ctx, address+38).chip8_instr);
    printf("SP:     %02X       %u:      %02X%02X      %s\n", 
        cpu_ctx->stack_pointer, address+40, cpu_ctx->memory.ram[address+40], cpu_ctx->memory.ram[address+41], disassemble(cpu_ctx, address+40).chip8_instr);
}

void dump_game_content(char *file_name){
    // loading game into memory space
    printf("file name is: %s\n", file_name);
    // open the file in "rb" mode -> rb = read binary 
    FILE* f = fopen(file_name, "rb");  
    // fseek sets the file pointer to the position "SEEK_END", which is the end of the file
    fseek(f, 0, SEEK_END);
    // ftell returns the current position of the file pointer. It corresponds to the size of the file in bytes because 
    // the file pointer is currently pointing at the end of the file
    long size = ftell(f);
    // SEEK_SET returns the file pointer back to the beginning
    fseek(f, 0, SEEK_SET);

    uint8_t game[size];
    fread(game, size, 1, f);
    dump_memory(game, size);
}

void load_temp_opcode(cpu *cpu_ctx){

    uint16_t test_instr[5] = { LE16TOBE16(0x6102), LE16TOBE16(0x75F1),  LE16TOBE16(0x8A10), LE16TOBE16(0x8121), LE16TOBE16(0x8232)};
    memory_init(&cpu_ctx->memory);
    load_game(cpu_ctx, (uint8_t *)test_instr, sizeof(test_instr));
}

// void exec_instr(int address){
//     if(address < 512 || address > size + GAME_MEM_SPACE_BEGINNING){
//         printf("You have stepped out of memory space allocated for game instructions\n");
//         break;
//     }
//     if(address % 2 != 0){
//         printf("Every instruction starts at even address\n");
//         break;        
//     }
//     opcode = memory_get_two_bytes(&cpu_ctx->memory, address);
//     execute_opcode(cpu_ctx, opcode);
//     address += 2;
// }


void debugger(cpu *cpu_ctx){
    char *file_name = "GAMES/GAMES/15PUZZLE.ch8";
    FILE* f = fopen(file_name, "rb");  
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t game[size];
    fread(game, size, 1, f);
    memory_init(&cpu_ctx->memory);
    load_game(cpu_ctx, game, size);
    // dump_memory(cpu_ctx->memory.ram, 4096);

    uint8_t break_points[100] = { -1 };
    int break_point_index = 0;

    uint16_t opcode = 0;
    char input[20];
    int address = 512;
    int size_to_dump = 0;
    // char game_name[50];
    printf("Debugging mode\n");
    while(1){
        printf(">>> ");
        fgets(input, sizeof(input), stdin);
        switch (tolower(input[0]))
        {
        // execute a game instruction
        case 'e':
            sscanf(input, "%*s %d", &address);
            if(address < 512 || address > size + GAME_MEM_SPACE_BEGINNING){
                printf("You have stepped out of memory space allocated for game instructions\n");
                break;
            }
            if(address % 2 != 0){
                printf("Every instruction starts at even address\n");
                break;        
            }
            opcode = memory_get_two_bytes(&cpu_ctx->memory, address);
            execute_opcode(cpu_ctx, opcode);
            address += 2;
            break;
        // dump memory segments 
        case 'd':
            sscanf(input, "%*s %d %d", &address, &size_to_dump);
            dump_memory(&cpu_ctx->memory.ram[address], size_to_dump);
            break;
        
        // dump game
        case 'g':
            dump_memory(&cpu_ctx->memory.ram[GAME_MEM_SPACE_BEGINNING], size);
            break;
        
        // execute next instruction
        case 'n':
            break;
        
        // set break point
        case 'b':
            sscanf(input, "%*s %d", &address);
            if(address < 512 || address > size + GAME_MEM_SPACE_BEGINNING){
                printf("You have stepped out of memory space allocated for game instructions\n");
                break;
            }
            if(address % 2 != 0){
                printf("Every instruction starts at even address\n");
                break;        
            }
            break_points[break_point_index] = address;
            break_point_index++;
            break;

        // print break points
        
        // step into  ---- done e

        // step through  --- need to google

        // run until next break point 
        case 's': // stands for start
            break;

        // print register
        case 'r':
            dump_register_content(cpu_ctx);
            break;
        // prints registers and memory contents around instruction
        case 'm':
            sscanf(input, "%*s %d", &address);
            dump_registers_and_memory(cpu_ctx, address);
            break;
        // run test cases
        case 't':
            load_temp_opcode(cpu_ctx);
            break;
        default:
            printf("Invalid command\n");
            break;
        }
    }
}

void test(){
    // memory test 
    printf("\n");
    memory mem;
    memory_set(&mem, 32, 0x20);
    memory_set(&mem, 13, 0x83);
    memory_set(&mem, 10, 0x10);
    memory_set(&mem, 63, 0xaa);
    memory_set(&mem, 64, 0x64);
    memory_set(&mem, 65, 0x65);

    printf("at address 32        - %04x\n", memory_get_one_byte(&mem, 32));
    printf("at address 13        - %04x\n", memory_get_one_byte(&mem, 13));
    printf("at address 10        - %04x\n", memory_get_one_byte(&mem, 10));
    printf("at address 63        - %04x\n", memory_get_one_byte(&mem, 63));
    printf("at address 64 and 65 - %04x\n", memory_get_two_bytes(&mem, 64));
    dump_memory(mem.ram, 97);
    printf("printing the entire memory content\n");
    dump_memory(mem.ram, CHIP8_RAM_SIZE_BYTES);
    printf("initializing memory\n");
    memory_init(&mem);
    dump_memory(mem.ram, CHIP8_RAM_SIZE_BYTES);
    printf("\n\n");

    // CPU registers 
    cpu cpu_ctx;
    cpu_init(&cpu_ctx);
    dump_register_content(&cpu_ctx);
    printf("\n");
    uint64_t val = 0x1122334455667788; // my linux is little endian
    memcpy(cpu_ctx.V, &val, sizeof(uint64_t));
    cpu_ctx.I = 0x9870;
    cpu_ctx.stack_pointer = 0x12;
    dump_register_content(&cpu_ctx);

    // CPU execute opcode
    execute_opcode(&cpu_ctx, 0x00E0);
    printf("\n\n");

    // Stack test 
    push(&cpu_ctx, 0x12);
    push(&cpu_ctx, 0x34);
    push(&cpu_ctx, 0x56);

    // Pop values from the stack
    uint8_t value1 = pop(&cpu_ctx);
    uint8_t value2 = pop(&cpu_ctx);
    uint8_t value5 = pop(&cpu_ctx);
    
    // Print the popped values
    printf("Popped Values: 0x%02X, 0x%02X, 0x%02X\n", value1, value2, value5);
}


