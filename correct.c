/*
 * =====================================================================================
 *
 *       Filename:  correct.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/03/15 11:26:11
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
#include "correct.h"

void correct_one(triangle *** mgrid, int level){
  int i,j;

  for(i=1;i<(int)(pow(2,level)-1);i++){
    for(j=1;j<(int)(pow(2,level)-i-1);j++){
      mgrid[level][i][j].function_u[edge_u]= 
        mgrid[level][i][j].function_u[edge_u]+ 
        mgrid[level][i][j].function_u_int[edge_u];
      mgrid[level][i][j].function_u[edge_v]=
        mgrid[level][i][j].function_u[edge_v]+
        mgrid[level][i][j].function_u_int[edge_v];
      mgrid[level][i][j].function_u[edge_w]=
        mgrid[level][i][j].function_u[edge_w]+
        mgrid[level][i][j].function_u_int[edge_w];
    }
  }
}

