#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "olive.c"
//olivec EP1 1:13:24
#define WIDTH 800
#define HEIGHT 600


static uint32_t pixels[HEIGHT*WIDTH];

#define COLS 8
#define ROWS 6
#define CELL_WIDTH (WIDTH/COLS)
#define CELL_HEIGHT (HEIGHT/ROWS)
#define BACKGROUND_COLOR 0xFF202020;

void olivec_fill_circle(uint32_t *pixels, size_t pixels_width, size_t pixels_height, int cx, int cy, int r, uint32_t color) {
    int x1 = cx -r;
    int y1 = cy -r;
    int x2 = cx +r;
    int y2 = cy +r;
    for (int y = y1; y <= y2; y++) {
        if (0 <= y && y < (int) pixels_height) {
            for (int x = x1; x <= x2; x++) {
                if (0 <= x && x < (int) pixels_width) {
                    int dx = x -cx;
                    int dy = y -cy;
                    if (dx*dx + dy*dy <= r*r) {
                        pixels[y*pixels_width + x] = color;
                    }
                }
            }
        }
    }
}

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
    const char *file_path = "checker.ppm";
    Errno err = olivec_save_to_ppm_file(pixels, WIDTH, HEIGHT, file_path);
    if (err) {
        fprintf(stderr, "ERROR: could not save file %s: %s\n", file_path, strerror(errno));
        return false;
    }

    return true;
}

bool circle_example() {
    olivec_fill(pixels, WIDTH, HEIGHT, 0xFF202020);
    int radius = CELL_WIDTH;
    if (CELL_HEIGHT < radius) {
        radius = CELL_HEIGHT;
    }

     for (int y = 0; y< ROWS; y++) {
        for (int x = 0; x< COLS; x++) {
            olivec_fill_circle(pixels, WIDTH, HEIGHT, x*CELL_WIDTH + CELL_WIDTH / 2, y*CELL_HEIGHT + CELL_HEIGHT / 2, radius / 2, 0xFF2020FF);
        }
    }

    //olivec_fill_circle(pixels, WIDTH, HEIGHT, WIDTH /2, HEIGHT / 2, 100, 0xFF2020FF);

    const char *file_path = "circle.ppm";
    Errno err = olivec_save_to_ppm_file(pixels, WIDTH, HEIGHT, file_path);
    if (err) {
        fprintf(stderr, "ERROR: could not save file %s: %s\n", file_path, strerror(errno));
        return false;
    }
    return true;
}

int main(void) {
    if (!checker_example()) return -1;
    if (!circle_example()) return -1;
    return 0;
}