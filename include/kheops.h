#ifndef KHEOPS_KHEOPS_H
#define KHEOPS_KHEOPS_H

#include <cairo.h>

void kheops_set_amp_delta (double amp_delta);

void kheops_set_amp_depth (unsigned amp_depth);

void kheops_rel_line_to (cairo_t * cr, const double x1, const double y1);

void kheops_line_to (cairo_t * cr, const double x1, const double y1);

#endif
