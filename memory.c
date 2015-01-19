/*
 * =====================================================================================
 *
 *       Filename:  memory.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  19/01/15 17:45:53
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
#include "memory.h"
#include <math.h>

triangle *** allocate_multigrid(int levels){
  int i,j;
  int size;
  
  triangle *** mgrid;
  /* creating a pointer to each of the grids */
  mgrid = (triangle ***)malloc(levels*sizeof(triangle **));
  if(mgrid == NULL){
    fprintf(stderr,"\t[ERROR] error in malloc\n");
    exit(EXIT_FAILURE);
  }
  for(i=0;i<levels;i++){
    size = pow(2,i);
    mgrid[i]=(triangle **)malloc(size*sizeof(triangle*));
    if(mgrid[i]==NULL){
      fprintf(stderr,"\t[ERROR] error in malloc\n");
      exit(EXIT_FAILURE);
    }
    for(j=0;j<size;j++){
      mgrid[i][j]=(triangle*)malloc((size-j)*sizeof(triangle));
      if(mgrid[i][j]==NULL){
        fprintf(stderr,"\t[ERROR] error in malloc\n");
        exit(EXIT_FAILURE);
      }
    }
  }
  return mgrid;
}

void free_multigrid(triangle *** mgrid, int levels){
  int i,j;
  for(i=0;i<levels;i++){
    for(j=0;j<pow(2,i);j++){
      free(mgrid[i][j]);
    }
  }
  for(i=0;i<levels;i++){
    free(mgrid[i]);
  }
  free(mgrid);
}
