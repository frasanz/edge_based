/* This is the jacobi relaxation method on GPU, edge based */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda.h>

typedef struct {
  double function_u[3];
  double function_u_new[3];
  double function_v[3];
  double function_f[3];
} triangle;

void initialize_grid(triangle ** h_grid, int size){
  int i,j,k;
  int triangles_base=(int)pow(2,size);
  for(i=0;i<triangles_base;i++){
    for(j=0;j<triangles_base-i;j++){
      for(k=0;k<3;k++){
        h_grid[i][j].function_u[k]=0.0;
        h_grid[i][j].function_u_new[k]=0.0;
        h_grid[i][j].function_v[k]=0.0;
        h_grid[i][j].function_f[k]=0.0;
      }
    }
  }
  for(i=1;i<triangles_base-1;i++){
    for(j=1;j<triangles_base-i-1;j++){
      for(k=0;k<3;k++){
        h_grid[i][j].function_u[k]=10*sin(i+10*j+20*k);
      }
    }
  }
}

void smoother(triangle ** h_grid, int size){
  int i,j,k;
}

int main(){
  triangle ** h_grid;
  triangle ** d_grid;
  int size=5;
  int i;
  int triangles_base=(int)pow(2,size);

  /* Host allocation */
  h_grid = (triangle **)malloc(triangles_base*sizeof(triangle*));
  for(i=0;i<triangles_base;i++){
    h_grid[i]=(triangle*)malloc((triangles_base-i)*sizeof(triangle));
  }

  /* Initialization */
  initialize_grid(h_grid,size);


  /* Host free */
  for(i=0;i<triangles_base;i++){
    free(h_grid[i]);
  }

  free(h_grid);
  return 0;
}
