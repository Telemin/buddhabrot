#include"mandel.h"

int main(){

  unsigned int stepnum = 0;
//  int nthreads = omp_get_max_threads();
//  omp_set_num_threads(nthreads);

  //Start by setting up our particle arrays
  double* zx = (double*)malloc(sizeof(double)*num_particles);
  double* zy = (double*)malloc(sizeof(double)*num_particles);
  double* cx = (double*)malloc(sizeof(double)*num_particles);
  double* cy = (double*)malloc(sizeof(double)*num_particles);
/*  double* zx = (double*)aligned_alloc(cache_align, sizeof(double)*num_particles);
  double* zy = (double*)aligned_alloc(cache_align, sizeof(double)*num_particles);
  double* cx = (double*)aligned_alloc(cache_align, sizeof(double)*num_particles);
  double* cy = (double*)aligned_alloc(cache_align, sizeof(double)*num_particles);*/

  //Now set up our initial grid - naively for now...
//  #pragma omp parallel for default(none) shared(cx, cy) schedule(static,0x100)
  for(int ii=0; ii<xres; ii++){
    for(int kk=0; kk<yres; kk++){
      printf("%d%d\n",ii,kk);
      cx[ii*yres + kk] = ii;
      cy[ii*yres + kk] = kk;
//      cx[ii*yres + kk] = ((double)ii * (double)xrange)/(double)xres + (double)xmin ;
//      cy[ii*yres + kk] = ((double)kk * (double)yrange)/(double)yres + (double)ymin ;
    }
  }


  for(stepnum=0; stepnum<1; stepnum++){
//  #pragma omp parallel for default(none) shared(zx, zy, cx, cy) 
  for(long ii=0; ii<num_particles; ii++){
    double zxt;
    zxt = zx[ii]*zx[ii] - zy[ii]*zy[ii] + cx[ii];
    zy[ii] = 2*zx[ii]*zy[ii] + cy[ii];
    zx[ii] = zxt;
  }
  
  FILE* outfile;
  char fname[100];
  sprintf(fname, "%04u.txt",stepnum);
  outfile = fopen(fname,"w");
  if(!outfile){
    printf("Unable to open output file!");
  } else {
    for(int ii=0; ii<num_particles; ii++){
      printf("%f,%f\n",zx[ii],zy[ii]);
      fprintf(outfile,"%f,%f\n",zx[ii],zy[ii]);
      }
/*    size_t written;
    written = fwrite(zx,sizeof(double),num_particles,outfile);
    printf("wrote: %u\n", (unsigned int)written);
    written = fwrite(zy,sizeof(double),num_particles,outfile);
    printf("wrote: %u\n", (unsigned int)written);*/
    fclose(outfile);
  }
  }

  return 0;
}
