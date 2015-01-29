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

void print_multigrid(FILE *f, triangle *** mgrid, int levels){
  int i;
  for(i=0;i<levels;i++)
    print_grid(f,mgrid[i],i);
}

/* Here, we can print each grid function in one triangle */
void print_grid(FILE *f, triangle **grid, int level){
  int i,j,k;
  /* For this level, and for each grid function,
   *  we have three grids */
  fprintf(f,"[PRINT] Grid function u at level %d\n",level);
  for(i=0;i<3;i++){
    fprintf(f,"\tu[%d]\n",i);
    for(j=0; j<pow(2,level);j++){
      for(k=0;k<pow(2,level)-j;k++){
        fprintf(f,"%1.1e ",grid[j][k].u[i]);
      }
      fprintf(f,"\n");
    }
    fprintf(f,"\tv[%d]\n",i);
    for(j=0; j<pow(2,level);j++){
      for(k=0;k<pow(2,level)-j;k++){
        fprintf(f,"%1.1e ",grid[j][k].v[i]);
      }
      fprintf(f,"\n");
    }
    fprintf(f,"\tf[%d]\n",i);
    for(j=0; j<pow(2,level);j++){
      for(k=0;k<pow(2,level)-j;k++){
        fprintf(f,"%1.1e ",grid[j][k].f[i]);
      }
      fprintf(f,"\n");
    }
  }
}

void print_all_operators(FILE *f, _operator ** op, int levels){
  int i;
  for(i=0;i<levels; i++){
    fprintf(f,"\n---- Operators level %d ----\n",i);
    print_level_operator(f,op[i],i);
  }
}


void print_level_operator(FILE *f, _operator *oper, int level){
  int i,j,k;
  for(i=0;i<9;i++){
      fprintf(f,"\n");
    for(j=0;j<3;j++){
      for(k=0;k<3;k++){
        fprintf(f, "%1.3f ",oper[i].op[j][k]);
      }
      fprintf(f,"\n");
    }
  }
}
