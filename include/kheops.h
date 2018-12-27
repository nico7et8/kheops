#ifndef KHEOPS_KHEOPS_H
#define KHEOPS_KHEOPS_H

#include <cairo.h>
#include <stdlib.h>

void kheops_set_amp_delta (double amp_delta);

void kheops_set_amp_depth (unsigned amp_depth);

void kheops_rel_line_to (cairo_t * cr, const double x1, const double y1);

void kheops_line_to (cairo_t * cr, const double x1, const double y1);

void kheops_curve_to (cairo_t * cr, double x1, double y1, double x2, double y2, double x3, double y3);

void kheops_curve_to2 (cairo_t * cr, double x1, double y1, double x2, double y2, double x3, double y3);
double vect_norm (double x, double y);

void kheops_move_to (cairo_t * cr, double x, double y);

void kheops_stroke (cairo_t * cr);

#endif
