#include <cairo.h>
#include <stdio.h>
#include <math.h>

int main () {

    int width = 400;
    int height = 300;

    cairo_surface_t * surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t * cr = cairo_create (surface);

    cairo_save (cr);
    cairo_translate (cr, width/2, height/2);
    cairo_scale (cr, 1, 0.5);
    cairo_arc (cr, 0, 0, 100, 0, 2*M_PI);
    cairo_set_source_rgba (cr, 255, 0, 0, 1);
    cairo_fill (cr);
    cairo_restore (cr);

    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "png/simple_ellipse.png");
}
