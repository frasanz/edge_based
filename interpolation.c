/*
 * =====================================================================================
 *
 *       Filename:  interpolation.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/02/15 18:12:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <math.h>
#include "interpolation.h"

void interpolate_one(triangle*** mgrid, int level_inf){
  int i,j;
  int I,J;
  int level_sup=level_inf+1;
  for(i=1;i<pow(2,level_inf);i++){
    I=2*i;
    for(j=0;j<pow(2,level_inf)-i;j++){
      J=2*j;
      mgrid[level_sup][I  ][J  ].function_u[edge_u]=
      mgrid[level_sup][I  ][J+1].function_u[edge_u]=
      mgrid[level_sup][I+1][J  ].function_u[edge_u]=
      mgrid[level_inf][i][j].function_u[edge_u];
    }
  }


}

