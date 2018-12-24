#ifndef KHEOPS_PERLIN_H
#define KHEOPS_PERLIN_H

#include <stdlib.h>

#define RAND1 ((double)rand()/(double)RAND_MAX)
#define RAND11 (2*(double)rand()/(double)RAND_MAX-1)
#define RAND255 ((rand() % 255))

double * perlin1D (
        const size_t samples,
        const unsigned depth, 
        double amplitude
        );

double ** perlin2D (
        const size_t xSamples,
        const size_t ySamples,
        const unsigned depth,
        double amplitude);

#endif
