#include <stdio.h>
#include <stdint.h>
#include "cpu.h"
#include "debug.h"
#include <pthread.h>

#ifdef __linux__ 
    #include<SDL2/SDL.h>
#elif __WIN64__
    #include "win64_sdl/include/SDL2/SDL.h"
#elif __APPLE__
    #include <SDL2/SDL.h>
#endif

void *run_game(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320, SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == NULL) {
        printf("SDL_CreateWindow error: %s\n", SDL_GetError());
        return NULL;
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
}

void run_debugger(){
    // debugger(cpu_ctx);
    cpu cpu_ctx;

    pthread_t game_thread;
    pthread_t debugger_thread;

    // Create threads for game and debugger
    pthread_create(&game_thread, NULL, run_game, NULL);
    pthread_create(&debugger_thread, NULL, debugger, (void *)&cpu_ctx);

    // Wait for both threads to finish
    pthread_join(game_thread, NULL);
    pthread_join(debugger_thread, NULL);
}

int main(int argc, char *argv[]){
    
    
    char* file_name = "GAMES/GAMES/CAVE.ch8";
    // dump_game_content(file_name);

    run_debugger();
    
    return 0;
} 