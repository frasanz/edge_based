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

/* Interpolate the solution of the sublevel */
void interpolate_one(triangle*** mgrid, int level_inf){
  int i,j;
  int I,J;
  int level_sup=level_inf+1;
  float value;
  for(i=0;i<(int)(pow(2,level_inf));i++){
    I=2*i;
    for(j=0;j<(int)(pow(2,level_inf)-i);j++){
      J=2*j;
      /*** edge_u ***/
      value=mgrid[level_inf][i][j].function_u[edge_u];
      mgrid[level_sup][I  ][J  ].function_v[edge_u]= value;
      mgrid[level_sup][I  ][J+1].function_v[edge_u]= value;
      mgrid[level_sup][I+1][J  ].function_v[edge_u]= value;
      if(i>0)
            mgrid[level_sup][I-1][J+1].function_v[edge_u]= value;
      /*** edge_v ***/
      value=mgrid[level_inf][i][j].function_u[edge_v];
      mgrid[level_sup][I  ][J  ].function_v[edge_v]= value;
      mgrid[level_sup][I  ][J+1].function_v[edge_v]= value;
      mgrid[level_sup][I+1][J  ].function_v[edge_v]= value;
      if(j<pow(2,level_inf)-i-1) // Not in the diag
        mgrid[level_sup][I+1][J+1].function_v[edge_v]= value;
      /*** edge_w ***/
      value = mgrid[level_inf][i][j].function_u[edge_w];
      mgrid[level_sup][I  ][J  ].function_v[edge_w]= value;
      mgrid[level_sup][I  ][J+1].function_v[edge_w]= value;
      mgrid[level_sup][I+1][J  ].function_v[edge_w]= value;
      if(j>0)
         mgrid[level_sup][I+1][J-1].function_v[edge_w]= value;
    }
  }
}

void interpolate_linear(triangle *** mgrid, int level_inf){
  int i,j;
  int I,J;
  int level_sup=level_inf+1;
  float value1;
  float value2;
  for(i=0;i<(int)(pow(2,level_inf));i++){
    I=2*i;
    for(j=0;j<(int)(pow(2,level_inf)-i);j++){
      J=2*j;
      /*** edge_u ***/
      value1=mgrid[level_inf][i][j].function_u[edge_u];
      if(j>0){
        value2=mgrid[level_inf][i][j-1].function_u[edge_u];
        mgrid[level_sup][I  ][J  ].function_v[edge_u] = 0.75*value1+0.25*value2;
        mgrid[level_sup][I  ][J-1].function_v[edge_u] = 0.25*value1+0.75*value2;
        if(j==(int)(pow(2,level_inf)-i-1)){
          mgrid[level_sup][I  ][J+1].function_v[edge_u]=0.5*value1;
        }
      }else if(j==0){
        mgrid[level_sup][I  ][J  ].function_v[edge_u] = 0.5*value1;
      }
      /***edge_v***/
      value1=mgrid[level_inf][i][j].function_v[edge_v];
      if(i>0){
        value2=mgrid[level_inf][i-1][j+1].function_u[edge_v];
        mgrid[level_sup][I  ][J+1].function_v[edge_v]=0.75*value1+0.25*value2;
        mgrid[level_sup][I-1][J+2].function_v[edge_v]=0.25*value1+0.75*value2;
        if(j==0){
          mgrid[level_sup][I+1][J  ].function_v[edge_v]=0.5*value1;
        }
      }else if(i==0){
        mgrid[level_sup][I  ][J+1].function_v[edge_v]=0.5*value1;
      }
      /***edge_w***/
      value1=mgrid[level_inf][i][j].function_v[edge_w];
      if(i>0){
        value2=mgrid[level_inf][i-1][j].function_u[edge_w];
        mgrid[level_sup][I  ][J  ].function_v[edge_w]=0.75*value1+0.25*value2;
        mgrid[level_sup][I-1][J  ].function_v[edge_w]=0.25*value1+0.75*value2;
        if(j==(int)(pow(2,level_inf)-i-1)){
          mgrid[level_sup][I+1][J  ].function_v[edge_w]=0.5*value1;
        }
      }else if(i==0){
        mgrid[level_sup][I  ][J  ].function_v[edge_w]=0.5*value1;

      }
    }
  }
}
