#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "debug.h"
#include "memory.h"
#include "disassembler.h"


#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define LE16TOBE16(value) ((value >> 8) | (value << 8))
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
    printf("Printing CPU internal state, all numbers in hex\n");
    printf("REGISTERS        MEMORY                                                                                                   STACK\n");
    printf("Reg   value      loc       value     disassembled opcode                                                                  loc     value\n");
    printf("------------     ---------------------------------------------------------------------------------------------------      -----------------\n");
    printf("V0:     %02X       %04X:      %02X%02X      %s0F      %04X\n", 
        cpu_ctx->V[0], address, cpu_ctx->memory.ram[address], cpu_ctx->memory.ram[address+1], disassemble(cpu_ctx, address).chip8_instr, cpu_ctx->memory.stack[15]);
    printf("V1:     %02X       %04X:      %02X%02X      %s0E      %04X\n", 
        cpu_ctx->V[1], address+2, cpu_ctx->memory.ram[address+2], cpu_ctx->memory.ram[address+3], disassemble(cpu_ctx, address+2).chip8_instr, cpu_ctx->memory.stack[14]);
    printf("V2:     %02X       %04X:      %02X%02X      %s0D      %04X\n", 
        cpu_ctx->V[2], address+4, cpu_ctx->memory.ram[address+4], cpu_ctx->memory.ram[address+5], disassemble(cpu_ctx, address+4).chip8_instr, cpu_ctx->memory.stack[13]);
    printf("V3:     %02X       %04X:      %02X%02X      %s0C      %04X\n", 
        cpu_ctx->V[3], address+6, cpu_ctx->memory.ram[address+6], cpu_ctx->memory.ram[address+7], disassemble(cpu_ctx, address+6).chip8_instr, cpu_ctx->memory.stack[12]);
    printf("V4:     %02X       %04X:      %02X%02X      %s0B      %04X\n", 
        cpu_ctx->V[4], address+8, cpu_ctx->memory.ram[address+8], cpu_ctx->memory.ram[address+9], disassemble(cpu_ctx, address+8).chip8_instr, cpu_ctx->memory.stack[11]);
    printf("V5:     %02X       %04X:      %02X%02X      %s0A      %04X\n", 
        cpu_ctx->V[5], address+10, cpu_ctx->memory.ram[address+10], cpu_ctx->memory.ram[address+11], disassemble(cpu_ctx, address+10).chip8_instr, cpu_ctx->memory.stack[10]);
    printf("V6:     %02X       %04X:      %02X%02X      %s09      %04X\n", 
        cpu_ctx->V[6], address+12, cpu_ctx->memory.ram[address+12], cpu_ctx->memory.ram[address+13], disassemble(cpu_ctx, address+12).chip8_instr, cpu_ctx->memory.stack[9]);
    printf("V7:     %02X       %04X:      %02X%02X      %s08      %04X\n", 
        cpu_ctx->V[7], address+14, cpu_ctx->memory.ram[address+14], cpu_ctx->memory.ram[address+15], disassemble(cpu_ctx, address+14).chip8_instr, cpu_ctx->memory.stack[8]);
    printf("V8:     %02X       %04X:      %02X%02X      %s07      %04X\n", 
        cpu_ctx->V[8], address+16, cpu_ctx->memory.ram[address+16], cpu_ctx->memory.ram[address+17], disassemble(cpu_ctx, address+16).chip8_instr, cpu_ctx->memory.stack[7]);
    printf("V9:     %02X       %04X:      %02X%02X      %s06      %04X\n", 
        cpu_ctx->V[9], address+18, cpu_ctx->memory.ram[address+18], cpu_ctx->memory.ram[address+19], disassemble(cpu_ctx, address+18).chip8_instr, cpu_ctx->memory.stack[6]);
    printf("V10:    %02X       %04X:      %02X%02X      %s05      %04X\n", 
        cpu_ctx->V[10], address+20, cpu_ctx->memory.ram[address+20], cpu_ctx->memory.ram[address+21], disassemble(cpu_ctx, address+20).chip8_instr, cpu_ctx->memory.stack[5]);
    printf("V11:    %02X       %04X:      %02X%02X      %s04      %04X\n", 
        cpu_ctx->V[11], address+22, cpu_ctx->memory.ram[address+22], cpu_ctx->memory.ram[address+23], disassemble(cpu_ctx, address+22).chip8_instr, cpu_ctx->memory.stack[4]);
    printf("V12:    %02X       %04X:      %02X%02X      %s03      %04X\n", 
        cpu_ctx->V[12], address+24, cpu_ctx->memory.ram[address+24], cpu_ctx->memory.ram[address+25], disassemble(cpu_ctx, address+24).chip8_instr, cpu_ctx->memory.stack[3]);
    printf("V13:    %02X       %04X:      %02X%02X      %s02      %04X\n", 
        cpu_ctx->V[13], address+26, cpu_ctx->memory.ram[address+26], cpu_ctx->memory.ram[address+27], disassemble(cpu_ctx, address+26).chip8_instr, cpu_ctx->memory.stack[2]);
    printf("V14:    %02X       %04X:      %02X%02X      %s01      %04X\n", 
        cpu_ctx->V[14], address+28, cpu_ctx->memory.ram[address+28], cpu_ctx->memory.ram[address+29], disassemble(cpu_ctx, address+28).chip8_instr, cpu_ctx->memory.stack[1]);
    printf("V15:    %02X       %04X:      %02X%02X      %s00      %04X\n", 
        cpu_ctx->V[15], address+30, cpu_ctx->memory.ram[address+30], cpu_ctx->memory.ram[address+31], disassemble(cpu_ctx, address+30).chip8_instr, cpu_ctx->memory.stack[1]);
    printf("I:      %04X     %04X:      %02X%02X      %s\n", 
        cpu_ctx->I, address+32, cpu_ctx->memory.ram[address+32], cpu_ctx->memory.ram[address+33], disassemble(cpu_ctx, address+32).chip8_instr);
    printf("DT:     %02X       %04X:      %02X%02X      %s\n", 
        cpu_ctx->delay_timer, address+34, cpu_ctx->memory.ram[address+34], cpu_ctx->memory.ram[address+35], disassemble(cpu_ctx, address+34).chip8_instr);
    printf("ST:     %02X       %04X:      %02X%02X      %s\n", 
        cpu_ctx->sound_timer, address+36, cpu_ctx->memory.ram[address+36], cpu_ctx->memory.ram[address+37], disassemble(cpu_ctx, address+36).chip8_instr);
    printf("PC:     %04X     %04X:      %02X%02X      %s\n", 
        cpu_ctx->program_counter, address+38, cpu_ctx->memory.ram[address+38], cpu_ctx->memory.ram[address+39], disassemble(cpu_ctx, address+38).chip8_instr);
    printf("SP:     %02X       %04X:      %02X%02X      %s\n", 
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

    uint8_t *game;
    fread(game, size, 1, f);
    dump_memory(game, size);
}

// 0x6102, 0x75F1,  0x8A10, 0x8121, 0x8232 five random instructions to update values in register


void load_temp_opcode(cpu *cpu_ctx){
    uint16_t test_instr[] = { 
        0x6102, 0x75F1,  0x8A10, 0x8121, 0x8232, 0x1212, // 0x1212 sets PC = 0x212
        0x6102, 0x75F1,  0x8A10, 0x8121, 0x8232, 0x2200, // 0x2204 pushes old PC to stack and then sets PC to 0x200
        0x6102, 0x75F1,  0x8A10, 0x8121, 0x8232, 0x00ee, // 0x00ee pops and set PC to popped value (BX LR)
        0x6102, 0x75F1,  0x8A10, 0x8121, 0x8232, 0x3102, // 0x3102 -> if V1 = 02, PC += 2 
        0x6102, 0x75F1,  0x8A10, 0x8121, 0x8232, 0x3122, // 0x3122 -> if V1 = 22, PC += 2
        0x6302, 0x75F1,  0x8A10, 0x8121, 0x8232, 0x4122, // 0x4122 -> if V1 != 22, PC += 2
        0x6102, 0x75F1,  0x8A10, 0x8121, 0x8232, 0x4102, // 0x4102 -> if V1 != 02, PC += 2
        0x6102, 0x6202,  0x8A10, 0x8121, 0x8232, 0x5120, // 0x5120 -> if V1 = V2, PC += 2 
        0x6102, 0x6212,  0x8A10, 0x8121, 0x8232, 0x5120, // 0x5120 -> if V1 = V2, PC += 2 
    };
    for(int i = 0; i < sizeof(test_instr); i++){
        test_instr[i] = LE16TOBE16(test_instr[i]);
    }
    memory_init(&cpu_ctx->memory);
    load_game(cpu_ctx, (uint8_t *)test_instr, sizeof(test_instr));
}

uint32_t break_points[100] = { -1 };
int break_point_num = 0;

bool break_point_exist(uint32_t address){
    for(int i = 0; i < break_point_num; i++){
        if(break_points[i] == address){
            return true;
        }
    }
    return false;
}

void print_help(){
    printf("execute an instruction at <addr> : e <addr>\n");
    printf("print content of specified memory range : d <starting_addr> <number_of_bytes_to_print>\n");
    printf("print game binary : g\n");
    printf("execute next instruction : n\n");
    printf("set break point for instruction at <addr> : b <addr>\n");
    printf("print all break points : p \n");
    printf("print register content : r\n");
    printf("print register content, stack and next 40 bytes of memory content starting from <addr> : m <addr>\n");
    printf("load test opcodes : l\n");
    printf("run test code : t\n");
    printf("print help menu : h\n");
    printf("close debugger : q\n");
}

void debugger(cpu *cpu_ctx){
    char *file_name = "GAMES/GAMES/15PUZZLE.ch8";
    FILE* f = fopen(file_name, "rb");  
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t *game = (uint8_t *)malloc(size);
    fread(game, size, 1, f);
    memory_init(&cpu_ctx->memory);
    load_game(cpu_ctx, game, size);
    free(game);
    // dump_memory(cpu_ctx->memory.ram, 4096);

    uint16_t opcode = 0;
    char input[20];
    uint32_t address = 512;
    int size_to_dump = 0;
    // char game_name[50];
    printf("Debugging mode\n");
    bool debugger_running = true;
    while(debugger_running){
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
        
        // execute next instruction/step into
        case 'n':
            opcode = memory_get_two_bytes(&cpu_ctx->memory, cpu_ctx->program_counter);
            printf("Executing opcode: %04X\n", opcode);
            execute_opcode(cpu_ctx, opcode);
            address = cpu_ctx->program_counter;
            printf("Next opcode: %04X - %s\n", 
                    memory_get_two_bytes(&cpu_ctx->memory, cpu_ctx->program_counter), 
                    disassemble(cpu_ctx, cpu_ctx->program_counter).chip8_instr
            );
            break;
        
        // set break point
        case 'b':
            sscanf(input, "%*s %d", &address);
            if(address < 512 || address > size + GAME_MEM_SPACE_BEGINNING){
                printf("You have stepped out of memory space allocated for game instructions\n");
                break;
            }
            if(break_point_exist(address)){
                printf("This break point exists already\n");
                break;
            }
            if(address % 2 != 0){
                printf("Every instruction starts at even address\n");
                break;        
            }
            break_points[break_point_num] = address;
            break_point_num++;
            break;

        // print break points
        case 'p':
            printf("all break points\n");
            for(int i = 0; i < break_point_num; i++){
                printf("%u\n", break_points[i]);
            }
            break;
        
        // step into  ---- done, n or e

        // step through  --- if next instruction is a call to a subroutine, skip it and move onto the next instruction

        // run until next break point 
        case 's': // stands for start
            break;

        // print register
        case 'r':
            dump_register_content(cpu_ctx);
            break;
        // prints registers, memory contents and stack
        case 'm':
            sscanf(input, "%*s %d", &address);
            dump_registers_and_memory(cpu_ctx, address);
            break;
        // run test cases
        case 't':
            test();
            break;
        // load test instructions 
        case 'l':
            printf("Loading test instructions, game file will be overwritten\n");
            load_temp_opcode(cpu_ctx);
            break;
        case 'h':
            print_help();
            break;
        case 'q':
            debugger_running = false;
        default:
            printf("Invalid command, type h to see help menu\n");
            break;
        }
    }
    printf("end of debugger\n");
}

void test(){
    // memory test 
    printf("\n========================= MEMORY TEST ========================== \n");    memory mem;
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
    printf("\n========================= CPU REGISTERS TEST ========================== \n");
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
    printf("\n========================= CPU EXECUTE OPCODE TEST ========================== \n");
    execute_opcode(&cpu_ctx, 0x00E0);

    // Stack test 
    printf("\n========================= STACK TEST ========================== \n");
    cpu_init(&cpu_ctx);
    printf("stack pointer is %04X\n", cpu_ctx.stack_pointer);
    push(&cpu_ctx, 0x12);
    push(&cpu_ctx, 0x34);
    push(&cpu_ctx, 0x56);
    printf("stack pointer now pointing to %04X (should be 0x56), and stack pointer is %04X\n", 
        cpu_ctx.memory.stack[cpu_ctx.stack_pointer], cpu_ctx.stack_pointer);
    push(&cpu_ctx, 0x12);
    printf("%04X popped (should be 0x12)\n", pop(&cpu_ctx));
    push(&cpu_ctx, 0x34);
    printf("%04X popped (should be 0x34)\n", pop(&cpu_ctx));
    push(&cpu_ctx, 0x56);
    printf("%04X popped (should be 0x56)\n", pop(&cpu_ctx));
    print_stack(&cpu_ctx);

    // Pop values from the stack
    uint8_t value1 = pop(&cpu_ctx);
    uint8_t value2 = pop(&cpu_ctx);
    uint8_t value5 = pop(&cpu_ctx);
    
    // Print the popped values
    printf("Popped Values: 0x%02X, 0x%02X, 0x%02X\n", value1, value2, value5);
}


