#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __linux__ 
    #include<SDL2/SDL.h>
#elif __WIN64__
    #include "win64_sdl/include/SDL2/SDL.h"
#elif __APPLE__
    #include <SDL2/SDL.h>
#endif

#define RELEASED false
#define PRESSED true

typedef struct input{
    bool key_state[16];
    char keys[16];
}input;

// this function resets all keys' state to RELEASED and load the SDL key sets for CHIP8 into keys array
void init_keyboard(input *inp, char *sdl_keys);

// this function returns the index of the key pressed/released
int get_key(input *inp, char sdl_key);

// this function sets the state of a given key to PRESSED, key = index of key state in key_state array
void set_key_pressed(input *inp, int key);

// this function sets the state of a given key to RELEASE 
void set_key_released(input *inp, int key);

// this function returns the current state of a key given the index
bool key_current_state(input *inp, int key);



