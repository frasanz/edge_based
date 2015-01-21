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
#include <time.h>
#include "initialize.h"
#include "math.h"

/* Here, we can initialize all functions in one triangle */
void initialize_grid(triangle **grid, int level, int value){
  int i,j;
  for(i=0; i<pow(2,level); i++){
    for(j=0; j<pow(2,level)-i;j++){
      grid[i][j].u[0]=1.0*value;
      grid[i][j].u[1]=1.0*value;
      grid[i][j].u[2]=1.0*value;

      grid[i][j].v[0]=1.0*value;
      grid[i][j].v[1]=1.0*value;
      grid[i][j].v[2]=1.0*value;

      grid[i][j].f[0]=1.0*value;
      grid[i][j].f[1]=1.0*value;
      grid[i][j].f[2]=1.0*value;
    }
  }
}

void initialize_multigrid(triangle *** mgrid, int levels, int value){
  int i;
  for(i=0;i<levels;i++)
    initialize_grid(mgrid[i],i,value);
}
void initialize_multigrid_levels(triangle *** mgrid, int levels){
  int i;
  for(i=0;i<levels;i++)
    initialize_grid(mgrid[i],i,i);
}


/* some initialization tools */
void initialize_grid_files(triangle **grid, int level){
  int i,j;
  for(i=0; i<pow(2,level);i++){
    for(j=0; j<pow(2,level)-i; j++){
      grid[i][j].u[0]=1.0*i;
      grid[i][j].u[1]=1.0*i;
      grid[i][j].u[2]=1.0*i;

      grid[i][j].v[0]=1.0*i;
      grid[i][j].v[1]=1.0*i;
      grid[i][j].v[2]=1.0*i;

      grid[i][j].f[0]=1.0*i;
      grid[i][j].f[1]=1.0*i;
      grid[i][j].f[2]=1.0*i;

    }
  }
}

void initialize_multigrid_files(triangle *** mgrid, int levels){
  int i;
  for(i=0; i<levels;i++)
    initialize_grid_files(mgrid[i], i);
}

void initialize_grid_columns(triangle **grid, int level){
  int i,j;
  for(i=0; i<pow(2,level);i++){
    for(j=0; j<pow(2,level)-i; j++){
      grid[i][j].u[0]=1.0*j;
      grid[i][j].u[1]=1.0*j;
      grid[i][j].u[2]=1.0*j;

      grid[i][j].v[0]=1.0*j;
      grid[i][j].v[1]=1.0*j;
      grid[i][j].v[2]=1.0*j;

      grid[i][j].f[0]=1.0*j;
      grid[i][j].f[1]=1.0*j;
      grid[i][j].f[2]=1.0*j;
    }
  }
}

void initialize_multigrid_columns(triangle *** mgrid, int levels){
  int i;
  for(i=0; i<levels;i++)
    initialize_grid_columns(mgrid[i], i);
}

void initialize_grid_random(triangle **grid, int level){
  int i,j,k;
  // generate different seed for random number                                     
  time_t t;                                                                        
  srand((unsigned) time(&t));                                                      
  for(i=0; i<pow(2,level);i++){
    for(j=0;j<pow(2,level)-i;j++){
      for(k=0;k<3;k++){
        grid[i][j].u[k]= (double)(rand() & 0xFF) / 10.0f;
        grid[i][j].v[k]= (double)(rand() & 0xFF) / 10.0f;
        grid[i][j].f[k]= (double)(rand() & 0xFF) / 10.0f;
      }
    }
  }
}
void initialize_multigrid_random(triangle *** mgrid, int levels){
  int i=0;
  for(i=0;i<levels;i++)
    initialize_grid_random(mgrid[i],i);
}





