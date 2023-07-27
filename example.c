#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "olive.c"

#define WIDTH 800
#define HEIGHT 600


static uint32_t pixels[HEIGHT*WIDTH];

#define COLS 8
#define ROWS 6
#define CELL_WIDTH (WIDTH/COLS)
#define CELL_HEIGHT (HEIGHT/ROWS)
#define BACKGROUND_COLOR 0xFF202020;

bool checker_example() {
    olivec_fill(pixels, WIDTH, HEIGHT, 0xFF202020);

    for (int y = 0; y< ROWS; y++) {
        for (int x = 0; x< COLS; x++) {
            uint32_t color;
            if ((x+y)%2 == 0) {
                color = 0xFF0000FF;
            } else {
                color = BACKGROUND_COLOR;
            }
            olivec_fill_rect(pixels, WIDTH, HEIGHT, x*CELL_WIDTH, y*CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, color);
        }
    }
    const char *file_path = "checker_example.ppm";
    Errno err = olivec_save_to_ppm_file(pixels, WIDTH, HEIGHT, file_path);
    if (err) {
        fprintf(stderr, "ERROR: could not save file %s: %s\n", file_path, strerror(errno));
        return false;
    }

    return true;
}

int main(void) {
    checker_example();
    return 0;
}