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
            } else if(event.type == SDL_KEYDOWN){
                char key = event.key.keysym.sym;
                printf("%c pressed\n", key);
            } else if(event.type == SDL_KEYUP){
                char key = event.key.keysym.sym;
                printf("%c released\n", key);
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[]){
    char* file_name = "GAMES/GAMES/CAVE.ch8";
    cpu cpu_ctx;
    cpu_init(&cpu_ctx);
    pthread_t debugger_thread;
    pthread_create(&debugger_thread, NULL, debugger, (void *)&cpu_ctx);
    run_game();
    pthread_join(debugger_thread, NULL);
    // test();
    
    return 0;
} 