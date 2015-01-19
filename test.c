/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/01/15 23:33:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#define DIM 15

typedef struct {
  double edge_u[3];
  double edge_v[3];
  double edge_f[3];
} triangle;



int main(){
  int i,j,k;
  triangle *** a3d;
  a3d = (triangle ***)malloc(DIM * sizeof(triangle**));
  for(i=0; i<DIM;i++){
    a3d[i] = (triangle **)malloc(DIM * sizeof(triangle*));
    for(j=0;j<DIM;j++){
      a3d[i][j] = (triangle *)malloc((DIM-j)*sizeof(triangle));
      for(k=0;k<DIM-j;k++){
        a3d[i][j][k].edge_u[0]=1.0*j;
      }
    }
  }
  for(i=0;i<DIM;i++){
    printf("\n%d",i);
    for(j=0;j<DIM;j++){
      printf("\n\t%d\n\t\t",j);
      for(k=0;k<DIM-j;k++){
        printf("%1.1f ",a3d[i][j][k].edge_u[0]);
      }
    }
  }

  // Trying to free
  for(i=0;i<DIM;i++){
    for(j=0;j<DIM;j++){
      free(a3d[i][j]);
    }
    free(a3d[i]);
  }
}

