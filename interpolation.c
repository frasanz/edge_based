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
  for(i=0;i<pow(2,level_inf);i++){
    I=2*i;
    for(j=0;j<pow(2,level_inf)-i;j++){
      J=2*j;
      /*** edge_u ***/
      mgrid[level_sup][I  ][J  ].function_u[edge_u]=1.0*i+0.1*j;
      mgrid[level_sup][I  ][J+1].function_u[edge_u]=1.0*i+0.1*j;
      mgrid[level_sup][I+1][J  ].function_u[edge_u]=1.0*i+0.1*j;
      if(i>0)
        mgrid[level_sup][I-1][J+1].function_u[edge_u]=1.0*i+0.1*j;
      /*** edge_v ***/
      mgrid[level_sup][I  ][J  ].function_u[edge_v]=1.0*i+0.1*j;
      mgrid[level_sup][I  ][J+1].function_u[edge_v]=1.0*i+0.1*j;
      mgrid[level_sup][I+1][J  ].function_u[edge_v]=1.0*i+0.1*j;
      if(j<pow(2,level_inf)-i-1) // Not in the diag
        mgrid[level_sup][I+1][J+1].function_u[edge_v]=1.0*i+0.1*j;
      /*** edge_w ***/
      mgrid[level_sup][I  ][J  ].function_u[edge_w]=1.0*i+0.1*j;
      mgrid[level_sup][I  ][J+1].function_u[edge_w]=1.0*i+0.1*j;
      mgrid[level_sup][I+1][J  ].function_u[edge_w]=1.0*i+0.1*j;
      if(j>0)
        mgrid[level_sup][I+1][J-1].function_u[edge_w]=1.0*i+0.1*j;


    }
  }
}

