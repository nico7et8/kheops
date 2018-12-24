#ifndef KHEOPS_PERLIN_H
#define KHEOPS_PERLIN_H

#define RAND1 ((double)rand()/(double)RAND_MAX)
#define RAND11 (2*(double)rand()/(double)RAND_MAX-1)
#define RAND255 ((rand() % 255))

double * perlin1D (const unsigned samples, const unsigned depth, double amplitude);

#endif
