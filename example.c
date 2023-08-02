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
            olivec_fill_circle(pixels, WIDTH, HEIGHT, x*CELL_WIDTH + CELL_WIDTH / 2, y*CELL_HEIGHT + CELL_HEIGHT / 2, radius / 2, 0xFF00FF00);
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

bool triangle_example() {
    olivec_fill(pixels, WIDTH, HEIGHT, 0xFF202020);
    int x1 = WIDTH/2, y1 = HEIGHT/8;
    int x2 = WIDTH/8, y2 =  HEIGHT/2;
    int x3 = WIDTH*7/8, y3 = HEIGHT*7/8;

    int radius = 10;
    olivec_fill_circle(pixels, WIDTH, HEIGHT, x1, y1, radius, 0xFF00FFFF);
    olivec_fill_circle(pixels, WIDTH, HEIGHT, x2, y2, radius, 0xFF00FFFF);
    olivec_fill_circle(pixels, WIDTH, HEIGHT, x3, y3, radius, 0xFF00FFFF);

    olivec_fill_triangle(pixels, WIDTH, HEIGHT, x1, y1, x2, y2, x3, y3, 0xFF0000FF);

    const char *file_path = "triangle.ppm";
    Errno err = olivec_save_to_ppm_file(pixels, WIDTH, HEIGHT, file_path);
    if (err) {
        fprintf(stderr, "ERROR: could not save file %s: %s\n", file_path, strerror(errno));
        return false;
    }
    return true;
}

int main(void) {
    if (!triangle_example()) return -1;
    if (!checker_example()) return -1;
    if (!circle_example()) return -1;
    if (!lines_example()) return -1;
    return 0;
}