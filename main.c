#include <stdio.h>
#include <stdint.h>
#include "cpu.h"
#include "debug.h"


int main(){
    uint8_t* file_name = "GAMES/GAMES/CAVE.ch8";
    dump_game_content(file_name);
    test();
    return 0;
}