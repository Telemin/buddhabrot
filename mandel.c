#include<stdlib.h>
#include<stdio.h>
#include<omp.h>
#include<math.h>

#define CACHE_ALIGN 0x40

#define XMIN -2
#define YMIN -2
#define XRANGE 4
#define YRANGE 4
#define GRID_XRES 1000
#define GRID_YRES 1000
#define GRIDCELLS (GRID_XRES * GRID_YRES)
#define XRES 10000
#define YRES 10000
#define NPART (XRES*YRES)
#define MAX_ITER 1000


void grid_deposit(unsigned long* grid, long startidx, long endidx, double* zx, double* zy){
  for(unsigned long ii=startidx; ii<=endidx; ii++){
    int gridx = floor((zx[ii] - XMIN) * GRID_XRES / XRANGE);
    int gridy = floor((zy[ii] - YMIN) * GRID_YRES / YRANGE);
    grid[gridx*GRID_YRES + gridy]++;
  }
  return;
}
  

long remove_escapees(long startidx, long endidx, double* zx
                    ,double* zy, double* cx, double* cy){
/*
 * This function is designed to remove all escapee particles with indices between startidx
 * and endidx from the arrays zx,zy,cx,cy.  This is done by iterating through the list and
 * replacing each escapee found in the forwards direction with a non-escapee found in the
 * backwards direction.  We are done when the search indices meet in the middle. Note endidx
 * is assumed to be the index of the last particle, NOT lastparticle+1.
*/
  long fwdidx = startidx;
  long bwdidx = endidx;
  for(; fwdidx<bwdidx; fwdidx++){                               //start searching forwards, we are done if indices meet
    if(zx[fwdidx]*zx[fwdidx] + zy[fwdidx]*zy[fwdidx] < 4){      //if particle is good we can move on 
      continue;                                        
      }
    for(; bwdidx > fwdidx; bwdidx--){                           //loop backwards, we are done if indices meet
      if(zx[bwdidx]*zx[bwdidx] + zy[bwdidx]*zy[bwdidx] < 4){    //if particle is good copy to fwdidx location
        zx[fwdidx] = zx[bwdidx];                                //and explicitly decrement bwdidx
        zy[fwdidx] = zy[bwdidx];
        cx[fwdidx] = cx[bwdidx];
        cy[fwdidx] = cy[bwdidx];
        bwdidx--;
        break;
      }
    } //when we drop out the end here bwdidx = fwdidx, fwdidx will get ++ed once more 

  }//when we get to here, bwdidx is pointing to the last unchecked particle
  if(zx[bwdidx]*zx[bwdidx] + zy[bwdidx]*zy[bwdidx] >= 4){
    bwdidx--;
  }
  return(bwdidx);
}

int main(){

  double* cx = aligned_alloc(CACHE_ALIGN, sizeof(double)*NPART);
  double* cy = aligned_alloc(CACHE_ALIGN, sizeof(double)*NPART);
  double* zx = aligned_alloc(CACHE_ALIGN, sizeof(double)*NPART);
  double* zy = aligned_alloc(CACHE_ALIGN, sizeof(double)*NPART);
  unsigned long* grid = aligned_alloc(CACHE_ALIGN, sizeof(unsigned long)*GRIDCELLS);

  for(int ii=0; ii<XRES; ii++){
    for(int kk=0; kk<YRES; kk++){
      int idx = ii*YRES + kk;
      cx[idx] = ((double)ii/(XRES-1) * XRANGE) + XMIN;
      cy[idx] = ((double)kk/(YRES-1) * YRANGE) + YMIN;
      zx[idx] = cx[idx];
      zy[idx] = cy[idx];
    }
  }

  unsigned long stepnum;
  
  unsigned long endidx = NPART -1;
  
  int b = 20;

  for(stepnum=0; stepnum<MAX_ITER; stepnum++){
    #pragma omp parallel for default(none) shared(zx, zy, cx, cy, endidx) num_threads(6)
    for(unsigned long ii=0; ii<=endidx; ii++){
      double zxt = zx[ii]*zx[ii] - zy[ii]*zy[ii] + cx[ii];
      zy[ii] = 2*zx[ii]*zy[ii] + cy[ii];
      zx[ii] = zxt;
    }
  endidx = remove_escapees(0, endidx, zx,zy, cx, cy);
  grid_deposit(grid, 0, endidx, zx, zy);
  printf("%lu particles remaining\n",endidx);
  printf("Progress: %lu/%u\n", stepnum, MAX_ITER);
  }



    FILE* outfile;
    char fname[100];
    sprintf(fname, "%lu.bin", stepnum);
    outfile = fopen(fname,"wb");
    if(!outfile){
      printf("Unable to open output file!");
    } else {
      size_t written;
      written = fwrite(grid,sizeof(unsigned long),GRIDCELLS,outfile);
      fclose(outfile);
    }

    return 0;
}
