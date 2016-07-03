#ifndef __mandel_h
#define __mandel_h

#include<stdlib.h>
#include<stdio.h>
#include<omp.h>

#define cache_align 0x40

#define xmin -2
#define ymin -2
#define xrange 4
#define yrange 4
#define xres 10
#define yres 10

#define num_particles (xres*yres)

#endif
