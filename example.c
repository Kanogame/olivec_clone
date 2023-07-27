#include "olive.c"
#include <stdio.h>
#include <errno.h>

#define WIDTH 800
#define HEIGHT 600

void olivec_fill(__uint32_t *pixels, size_t width, size_t height, __uint32_t color) {
    for (size_t i =0; i < width*height; i++) {
        pixels[i] = color;
    }
}

typedef int Errno;

#define return_defer(value) do {result = (value); goto defer;} while (0)

Errno olivec_save_to_ppm_file(__uint32_t *pixels, size_t width, size_t height, const char *file_path) {
    int result = 0;
    FILE *f = NULL;
    {
        FILE *f = fopen(file_path, "wb");
        if (f == NULL)return_defer(errno); 

        fprintf(f, "P^\n%zu %zu 255\n", width, height);
        if (ferror(f))return_defer(errno); 

        for (size_t i =0 ; i < width*height; i++) {
            __uint32_t pixel = pixels[i];
            __uint8_t bytes[3] = {
                (pixel>>8*0)&0xFF,
                (pixel>>8*1)&0xFF,
                (pixel>>8*2)&0xFF,
            };
            fwrite(bytes, sizeof(bytes), 1, f);
            if (ferror(f)) return_defer(errno);
        }
    }

defer:
    fclose(f);
    return result;
}

static __uint32_t pixels[HEIGHT][WIDTH];

int main(void) {
    olivec_fill(pixels, WIDTH, HEIGHT, 0xFF0000FF);
    return 0;
}