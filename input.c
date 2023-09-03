#include "input.h"

void init_keyboard(input *inp, char *sdl_keys){
    for(int i = 0; i < 16; i++){
        inp->keys[i] = sdl_keys[i];
        inp->key_state[i] = RELEASED;
    }
}

int get_key(input *inp, char sdl_key){
    int index = 0;
    for(int i = 0; i < 16; i++){
        if(inp->keys[i] = sdl_key){
            index = i;
            
        }
        break;
    }

    return index;

}
