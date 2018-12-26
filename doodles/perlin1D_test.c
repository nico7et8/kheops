#include "perlin.h"
#include <cairo.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main () {

    unsigned width = 1200;
    unsigned height = 800;

    cairo_surface_t * surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t * cr = cairo_create (surface);

    RAND255;

    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint(cr);
    cairo_set_source_rgb (cr, 0, 0, 0);

    unsigned margin = 100;
    double length = width - 2*margin;

    cairo_set_line_width (cr, 0.5);

    double * noise; 

    double r, g, b;

    for (size_t k=0 ; k <100 ; ++k) {

            r = RAND1;
            g = RAND1;
            b = RAND1;

    for (size_t d=0 ; d < 3 ; ++d) {

        srand(k);


        switch (d) {
            case 0:
                cairo_set_source_rgba (cr, r, g*0.7, b*0.7, 1);
                break;
            case 1:
                cairo_set_source_rgba (cr, r*0.7, g, b*0.7, 1);
                break;
            case 2:
                cairo_set_source_rgba (cr, r*0.7, g*0.7, b, 1);
                break;
        }

            noise = perlin1D (length, 5, 200);


            double x=margin;
            double y0= height/4 * (d+1);
            double y = y0;
            cairo_move_to (cr, x, y);

            for (size_t x=margin ; x < width - margin ; ++x) {
                y = y0 + noise[x-margin]; 
                cairo_line_to (cr, x, y);
            }
            cairo_stroke (cr);
            cairo_line_to (cr, width-margin, k);
        }
    }

    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "png/perlin1D_test.png");
    cairo_surface_destroy (surface);

    return 0;

}
