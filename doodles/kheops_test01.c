#include <cairo.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "kheops.h"
#include "perlin.h"

int main () {

    unsigned width = 1000;
    unsigned height = 1000;

    srand(time(NULL));
    RAND255;

    cairo_surface_t * surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t * cr = cairo_create (surface);

    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint (cr);


    /* kheops_set_amp_delta (0.1); */
    /* kheops_set_amp_depth (10); */

    cairo_set_source_rgb (cr, 1,0,0);
    cairo_set_line_width (cr, 0.5);

    int rowMax = 30;
    int colMax = rowMax;
    double yStep = height / rowMax;
    double xStep = width / colMax;
    double x0, y0 = 0;
    double my = yStep / 5;
    double mx = xStep / 5;
    double l = 0.25;
    double c;

    double ** perlin = perlin2D (colMax, rowMax, 1, 1);

    for (int row = 0 ; row < rowMax ; ++ row) {
        x0 = 0;
        for (int col = 0 ; col < colMax ; ++col) {
            if (rand() % 2 == 0) {
                c = perlin[row][col] / 2 + 0.5;    
                cairo_set_source_rgba (cr, c, 0, 0, 1);
                cairo_move_to (cr, x0+mx, y0+my);
                cairo_line_to (cr, x0+xStep-mx, y0+my);
                cairo_line_to (cr, x0+xStep-mx, y0+yStep-my);
                cairo_line_to (cr, x0+mx, y0+yStep-my);
                cairo_line_to (cr, x0+mx, y0+my);
                cairo_stroke(cr);
            }
            x0 += xStep;
            printf ("% 5.2f ", c);
        }
        printf ("\n");
        y0 += yStep;
    }
    
    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "png/kheops_test01.png");
}
