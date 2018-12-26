#ifndef KHEOPS_KHEOPS_H
#define KHEOPS_KHEOPS_H

#include <cairo.h>

void kheops_set_depth (unsigned depth);

void kheops_set_amplitude (double amplitude);

void kheops_line_to (cairo_t * cr, double vx, double vy);


#endif
