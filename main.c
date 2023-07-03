#include <stdio.h>
#include <stdint.h>
#include "cpu.h"
#include "debug.h"

#ifdef __linux__ 
    int main(){
        cpu cpu_ctx;
        char* file_name = "GAMES/GAMES/CAVE.ch8";
        dump_game_content(file_name);
        test();
        debugger(&cpu_ctx);
        return 0;
    }
#elif __WIN64__
    int main(){
        cpu cpu_ctx;
        char* file_name = "GAMES/GAMES/CAVE.ch8";
        dump_game_content(file_name);
        test();
        debugger(&cpu_ctx);
        return 0;
    } 
#elif __APPLE__
    int main(){
        cpu cpu_ctx;
        char* file_name = "GAMES/GAMES/CAVE.ch8";
        dump_game_content(file_name);
        test();
        debugger(&cpu_ctx);
        return 0;
    } 
#endif