#include<stdlib.h>
#include<stdio.h>
#include<omp.h>

#define cache_align 0x40

#define xmin -2
#define ymin -2
#define xrange 4
#define yrange 4
#define xres 1000
#define yres 1000
#define num_particles (xres*yres)
#define MAX_ITER 10

int main(){

  double* cx = aligned_alloc(cache_align, sizeof(double)*num_particles);
  double* cy = aligned_alloc(cache_align, sizeof(double)*num_particles);
  double* zx = aligned_alloc(cache_align, sizeof(double)*num_particles);
  double* zy = aligned_alloc(cache_align, sizeof(double)*num_particles);

  for(int ii=0; ii<xres; ii++){
    for(int kk=0; kk<yres; kk++){
      int idx = ii*yres + kk;
      cx[idx] = ((double)ii/(xres-1) * xrange) + xmin;
      cy[idx] = ((double)kk/(yres-1) * yrange) + ymin;
      zx[idx] = 0.;
      zy[idx] = 0.;
    }
  }

  for(unsigned int stepnum; stepnum<MAX_ITER; stepnum++){

  for(int ii=0; ii<num_particles; ii++){
    double zxt = zx[ii]*zx[ii] - zy[ii]*zy[ii] + cx[ii];
    zy[ii] = 2*zx[ii]*zy[ii] + cy[ii];
    zx[ii] = zxt;
  }

  FILE* outfile;
  char fname[100];
  sprintf(fname, "out.bin");
  outfile = fopen(fname,"wb");
  if(!outfile){
    printf("Unable to open output file!");
  } else {
    size_t written;
    written = fwrite(zx,sizeof(double),num_particles,outfile);
    written = fwrite(zy,sizeof(double),num_particles,outfile);
    fclose(outfile);
  }
  }

  return 0;
}
