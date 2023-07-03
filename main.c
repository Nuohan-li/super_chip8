#include <stdio.h>
#include <stdint.h>
#include "cpu.h"
#include "debug.h"

#ifdef __linux__ 
#include<SDL2/SDL.h>
int main(int argc, char *argv[]){
    
    SDL_Init(SDL_INIT_EVERYTHING)

    SDL_Window *window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (window == NULL) {
        printf("SDL_CreateWindow error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Event event;
    while(1){
        if(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                break;
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

    cpu cpu_ctx;
    char* file_name = "GAMES/GAMES/CAVE.ch8";
    dump_game_content(file_name);
    test();
    debugger(&cpu_ctx);
    return 0;
} 
#elif __WIN64__
#include "win64_sdl/include/SDL2/SDL.h"
int main(int argc, char *argv[]){
    
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("SDL test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_ALLOW_HIGHDPI); 
    if(window == NULL){
        printf("window creation failed\n");
        return 1;
    }
    SDL_Event event;
    while(1){
        if(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                break;
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

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