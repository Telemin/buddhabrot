#include<stdlib.h>
#include<stdio.h>
#include<omp.h>

#define cache_align 0x40

#define xmin -2
#define ymin -2
#define xrange 4
#define yrange 4
#define xres 5
#define yres 5
#define num_particles (xres*yres)

int main(){

  unsigned int stepnum = 0;

  double* cx = aligned_alloc(cache_align, sizeof(double)*num_particles);
  double* cy = aligned_alloc(cache_align, sizeof(double)*num_particles);

  for(int ii=0; ii<xres; ii++){
    for(int kk=0; kk<yres; kk++){
      cx[ii*yres + kk] = ((double)ii/(xres-1) * xrange) + xmin;
      cy[ii*yres + kk] = ((double)kk/(yres-1) * yrange) + ymin;
    }
  }


  FILE* outfile;
  char fname[100];
  sprintf(fname, "out.bin");
  outfile = fopen(fname,"wb");
  if(!outfile){
    printf("Unable to open output file!");
  } else {
    size_t written;
    written = fwrite(cx,sizeof(double),num_particles,outfile);
    written = fwrite(cy,sizeof(double),num_particles,outfile);
    fclose(outfile);
  }

  return 0;
}
