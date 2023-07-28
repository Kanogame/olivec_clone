#ifndef OLIVE_C_
#define OLIVE_C_

void swap_int(int *value1, int *value2) {
    int mem = *value1;
    *value1 = *value2;
    *value2 = mem;
}

void olivec_fill(uint32_t *pixels, size_t width, size_t height, uint32_t color) {
    for (size_t i =0; i < width*height; i++) {
        pixels[i] = color;
    }
}


void olivec_fill_rect(uint32_t *pixels, size_t pixels_width, size_t pixels_height, int x0, int y0, size_t w, size_t h, uint32_t color) {
    for (int dy = 0; dy <(int) h; dy++) {
        int y = y0 + dy;
        if (0 <= y && y < (int)pixels_height) {
            for (int dx = 0; dx < (int) w; dx++) {
                int x = x0 + dx;
                if (0 <= x && x < (int) pixels_width) {
                    pixels[y*pixels_width + x] = color;
                }
            }
        }
    }
}

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

void sort_triangle_points_by_y(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3) {
    if (*y1 > *y2) {
        swap_int(*y1, *y2);
        swap_int(*x1, *x2);
    }
    if (*y2 > *y3) {
        swap_int(*y2, *y3);
        swap_int(*x2, *x3);
    }
    if (*y1 > *y2) {
        swap_int(*y1, *y2);
        swap_int(*x1, *x2);
    }
} 

void olivec_fill_triangle(uint32_t *pixels, size_t width, size_t height, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color) {

}

typedef int Errno;

#define return_defer(value) do {result = (value); goto defer;} while (0)

Errno olivec_save_to_ppm_file(uint32_t *pixels, size_t width, size_t height, const char *file_path) {
    int result = 0;
    FILE *f = NULL;
    {
        FILE *f = fopen(file_path, "wb");
        if (f == NULL)return_defer(errno); 

        fprintf(f, "P6\n%zu %zu\n255\n", width, height);
        if (ferror(f))return_defer(errno); 

        for (size_t i =0 ; i < width*height; i++) {
            uint32_t pixel = pixels[i];
            uint8_t bytes[3] = {
                (pixel>>8*0)&0xFF,
                (pixel>>8*1)&0xFF,
                (pixel>>8*2)&0xFF,
            };
            fwrite(bytes, sizeof(bytes), 1, f);
            if (ferror(f)) return_defer(errno);
        }
    }

defer:
    if (f) fclose(f);
    return result;
}

#endif // OLIVE_C_