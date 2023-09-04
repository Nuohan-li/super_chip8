#include "display.h"

void init_display(display *screen){
    for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 64; x++) {
            screen->pixels_array[y][x] = false;
        }
    }
}


// Set a pixel to the on state
void screen_set_pixel(display *screen, int x, int y) {
    if (x >= 0 && x < 64 && y >= 0 && y < 32) {
        screen->pixels_array[y][x] = true;
    }
}

void screen_reset_pixel(display *screen, int x, int y) {
    if (x >= 0 && x < 64 && y >= 0 && y < 32) {
        screen->pixels_array[y][x] = false;
    }
}


// Get the state of a pixel
bool pixel_state(display *screen, int x, int y) {
    if (x >= 0 && x < 64 && y >= 0 && y < 32) {
        return screen->pixels_array[y][x];
    }
    return false; // Return false for out-of-bounds coordinates
}


// Draw a sprite on the screen
bool draw_sprite(display *screen, int x, int y, const char *sprite_ptr, int num_bytes) {
    bool collision = false;
    for (int i = 0; i < num_bytes; i++) {
        for (int j = 0; j < 8; j++) {
            int current_x = x + j;
            int current_y = y + i;

            // Check if the current position is within bounds
            if (current_x >= 0 && current_x < 64 && current_y >= 0 && current_y < 32) {
                bool current_pixel = (sprite_ptr[i] & (0x80 >> j)) != 0;
                if (current_pixel && screen->pixels_array[current_y][current_x]) {
                    collision = true;
                }
                // Replace existing pixel or draw fresh if does not exist.
                screen->pixels_array[current_y][current_x] ^= current_pixel;
            }
        }
    }
    return collision;
}