#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct display{
    // CHIP8 display is 64 x 32 pixels 
    bool pixels_array[32][64];
} display;

// this function initializes the display
void init_display(display *screen);

// this function sets a pixel of the display 
void screen_set_pixel(display *screen, int x, int y);

// this function resets a pixel
void screen_reset_pixel(display *screen, int x, int y);

// this function returns the state of a pixel, return -1 if out of bound
int pixel_state(display *screen, int x, int y);

// this function draws the sprite on the screen
// things to watch out for -> collision of sprites, collision of sprite on the edge of the screen
bool draw_sprite(display *screen, int x, int y, const char *sprite_ptr, int num_byte);
