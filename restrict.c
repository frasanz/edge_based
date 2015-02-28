/*
 * =====================================================================================
 *
 *       Filename:  restrict.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/02/15 17:07:00
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
#include "restrict.h"

void restrict_one(triangle ***mgrid, int level_sup){
  int i,j;
  int I,J;
  int level_inf = level_sup-1;
  // loop over all interior points
  for(i=1;i<pow(2,level_inf)-1;i++){
    I=2*i;
    for(j=1;j<pow(2,level_inf)-i-1;j++){
      J=2*j;
      mgrid[level_inf][i][j].function_f[edge_u]=(
            3*(mgrid[level_sup][I  ][J  ].function_v[edge_u]+
               mgrid[level_sup][I  ][J+1].function_v[edge_u]+
               mgrid[level_sup][I-1][J+1].function_v[edge_u])+
               mgrid[level_sup][I+1][J  ].function_v[edge_u]+
               mgrid[level_sup][I-1][J  ].function_v[edge_u]+
               mgrid[level_sup][I-1][J+2].function_v[edge_u])/12;

      mgrid[level_inf][i][j].function_f[edge_v]=(
            3*(mgrid[level_sup][I+1][J  ].function_v[edge_v]+
               mgrid[level_sup][I  ][J+1].function_v[edge_v]+
               mgrid[level_sup][I+1][J+1].function_v[edge_v])+
               mgrid[level_sup][I  ][J  ].function_v[edge_v]+
               mgrid[level_sup][I+2][J  ].function_v[edge_v]+
               mgrid[level_sup][I  ][J+2].function_v[edge_v])/12;

      mgrid[level_inf][i][j].function_f[edge_w]=(
            3*(mgrid[level_sup][I  ][J  ].function_v[edge_w]+
               mgrid[level_sup][I+1][J  ].function_v[edge_w]+
               mgrid[level_sup][I+1][J-1].function_v[edge_w])+
               mgrid[level_sup][I  ][J+1].function_v[edge_w]+
               mgrid[level_sup][I  ][J-1].function_v[edge_w]+
               mgrid[level_sup][I+2][J-1].function_v[edge_w])/12;
    }
  }
}

