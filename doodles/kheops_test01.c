#include <cairo.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "kheops.h"

int main () {

    unsigned width = 1280;
    unsigned height = 720;
    unsigned margin = 100;

    srand (time(NULL));

    cairo_surface_t * surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t * cr = cairo_create (surface);

    cairo_set_antialias (cr, CAIRO_ANTIALIAS_BEST);
    cairo_set_line_width (cr, 0.5);
    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint (cr);
    cairo_set_source_rgb (cr, 0, 0, 0);

    kheops_set_amp_delta (0.04);
    kheops_set_amp_depth (5);
    double step = 0.05;

    for (double k = 0 ; k < height ; k += step) {
       cairo_move_to (cr, 0, k); 
       kheops_line_to2 (cr, width, k);
       cairo_stroke (cr);
    }

    /* for (double k = 0 ; k < height ; k += step) { */
       /* cairo_move_to (cr, 0, k);  */
       /* kheops_rel_line_to (cr, width, 0); */
       /* cairo_stroke (cr); */
    /* } */


    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "png/kheops_test01.png");
}
