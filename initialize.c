/*
 * =====================================================================================
 *
 *       Filename:  initialize.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  19/01/15 18:43:06
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
#include "initialize.h"
#include "math.h"

/* Here, we can initialize all functions in one triangle */
void initialize_grid(triangle **grid, int level, int value){
  int i,j;
  for(i=0; i<pow(2,level); i++){
    for(j=0; j<pow(2,level)-i;i++){
      grid[i][j].u[0]=1.0*value;
      grid[i][j].u[1]=1.0*value;
      grid[i][j].u[2]=1.0*value;
    }
  }
}

void initialize_multigrid(triangle *** mgrid, int levels, int value){
  int i;
  for(i=0;i<levels;i++)
    initialize_grid(mgrid[i],i,value);
}

