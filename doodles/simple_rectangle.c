#include <cairo.h>
#include <stdio.h>

int main () {

    int width = 300;
    int height = 300;

    cairo_surface_t * surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t * cr = cairo_create (surface);

    cairo_rectangle (cr, 50, 100, width-100, height-200);
    cairo_set_source_rgba (cr, 255, 0, 0, 1);
    cairo_fill (cr);

    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "png/simple_rectangle.png");
}
