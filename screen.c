/*
 * =====================================================================================
 *
 *       Filename:  screen.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20/01/15 17:14:01
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
#include <math.h>
#include "screen.h"

/* Here, we can print each grid function in one triangle */
void print_grid(triangle **grid, int level){
  int i,j,k;
  /* For this level, and for each grid function,
   *  we have three grids */
  printf("[PRINT] Grid function u at level %d\n",level);
  for(i=0;i<3;i++){
    printf("      u[%d]\n",i);
    for(j=0; j<pow(2,level);j++){
      for(k=0;k<pow(2,level)-j;k++){
        printf("%1.1e ",grid[j][k].u[i]);
      }
      printf("\n");
    }
  }
}

void print_multigrid(triangle *** mgrid, int levels){
  int i;
  for(i=0;i<levels;i++)
    print_grid(mgrid[i],i);
}

