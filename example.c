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

void swap_int(int *value1, int *value2) {
    int mem = *value1;
    *value1 = *value2;
    *value2 = mem;
}

void olivec_draw_line(uint32_t *pixels, size_t pixels_width, size_t pixels_height, int x1, int y1, int x2, int y2, uint32_t color) {
    int dx = x2 -x1;
    int dy = y2 -y1;

    if (dx != 0) {
        int k = dy/dx;
        int c = y1 - dy*x1/dx;

        if (x1 > x2) swap_int(&x1, &x2);
        for (int x = x1; x <= x2; x++) {
            if (0 <= x && x < (int) pixels_width) {
                int sy1 = dy*x/dx +c;
                int sy2 = dy*(x + 1)/dx +c;
                if (sy1 > sy2) swap_int(&sy1, &sy2);
                for (int y = sy1; y <= sy2; y++) {
                    if (0 <= y && y < (int) pixels_height) {
                        pixels[y*pixels_width + x] = color;
                    }
                }
            }
        }
    } else {
        int x = x1;
        if (0 <= x && x < (int) pixels_width) {
            if (y1 < y2) swap_int(&y1, &y2);
            for (int y = y1; y <= y1; y++) {
                if (0 <= y && y < (int) pixels_height) {
                    pixels[y*pixels_width +x] = color;
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

bool lines_example() {
    olivec_fill(pixels, WIDTH, HEIGHT, 0xFF202020);

    olivec_draw_line(pixels, WIDTH, HEIGHT, 0, 0, WIDTH / 8, HEIGHT, 0xFF0000FF);

    const char *file_path = "lines.ppm";
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
    if (!lines_example()) return -1;
    return 0;
}