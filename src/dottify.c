#include "dottify.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


cairo_surface_t * dottify (const char * filepath, int step) {
    cairo_surface_t * image;
    cairo_surface_t * surface;
    cairo_t * cr;
    int width, height, stride;
    unsigned char * imgPtr; 
    image = cairo_image_surface_create_from_png (filepath);
    if (cairo_surface_status (image)) {
        printf ("ERROR: %s not valid path", filepath);
        exit (EXIT_FAILURE);
    }
    imgPtr = cairo_image_surface_get_data (image);
    width = cairo_image_surface_get_width (image);
    height = cairo_image_surface_get_height (image);
    stride = cairo_image_surface_get_stride (image);
    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cr = cairo_create (surface);
    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint (cr);
    /* printf ("definition = %d x %d\n", width, height); */
    /* printf ("stride = %d\n", stride); */
    /* printf ("step = %d\n", step); */
    int x0 = 0, y0 = 0;
    int x, y;
    int r, g, b, a;
    double rMoy, gMoy, bMoy, aMoy, l;
    int p;
    int area = step * step;
    double radius;
    while (y0 < height) {
        while (x0 < width) {
            r = 0; g = 0; b = 0 ; a = 0;
            for (y = y0 ; y < y0 + step ; ++y) {
                for (x = x0 ; x < x0 + step ; ++x) {
                    p = y * stride + 4 * x;
                    b += * (imgPtr + p);
                    g += * (imgPtr + p + 1);
                    r += * (imgPtr + p + 2);
                    a += * (imgPtr + p + 3);
                }
            }
            aMoy = (double) a / area / 255;
            rMoy = (double) r / area / 255;
            gMoy = (double) g / area / 255;
            bMoy = (double) b / area / 255;
            l = (double) (r + g + b) / 3 / area / 255;
            radius = (1-l) * step / 2;
            cairo_arc (cr, x0 + (double)step / 2, y0 + (double)step/2, radius, 0, 2 * M_PI);
            cairo_set_source_rgb (cr, rMoy, gMoy, bMoy);
            /* cairo_set_source_rgb (cr, 0, 0, 0); */
            cairo_fill (cr);
            x0 += step;
        }
        x0 = 0;
        y0 += step;
    }
    cairo_surface_destroy (image);
    return surface;
}

