/* This is the jacobi relaxation method on GPU, edge based */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda.h>

typedef struct {
  double function_u[3];
  double function_v[3];
  double function_f[3];
} triangle;



int main(){
  triangle ** h_grid;
  triangle ** d_grid;
  int size=5;
  int i,j;

  int triangles_base=(int)pow(2,size);

  /* Host allocation */
  h_grid = (triangle **)malloc(triangles_base*sizeof(triangle*));
  for(i=0;i<triangles_base;i++){
    h_grid[i]=(triangle*)malloc((triangles_base-i)*sizeof(triangle));
  }


  /* Host free */
  for(i=0;i<triangles_base;j++){
    free(h_grid[i]);
  }
  free(h_grid);
  return 0;
}
