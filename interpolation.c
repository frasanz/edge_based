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
      if(j==0){
        mgrid[level_sup][I  ][J  ].function_v[edge_u] = 0.5*value1;
        if(j==(int)(pow(2,level_inf)-i-1)){
          mgrid[level_sup][I  ][J+1].function_v[edge_u]=0.5*value1;
        }
      } else {
        value2=mgrid[level_inf][i][j-1].function_u[edge_u];
        mgrid[level_sup][I  ][J  ].function_v[edge_u] = 0.75*value1+0.25*value2;
        mgrid[level_sup][I  ][J-1].function_v[edge_u] = 0.25*value1+0.75*value2;
        if(j==(int)(pow(2,level_inf)-i-1)){
          mgrid[level_sup][I  ][J+1].function_v[edge_u]=0.5*value1;
        } 
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
        if(j==0){
            mgrid[level_sup][I+1][J  ].function_v[edge_v]=0.5*value1;
         }
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
        if(j==(int)(pow(2,level_inf)-i-1)){
          mgrid[level_sup][I+1][J  ].function_v[edge_w]=0.5*value1;
        }
      }
    }
  }
  /* We can do right now middle files */
  /* EDGE U - MIDDLE FILES */
  for(i=1;i<(int)(pow(2,level_sup)-1);i=i+2){
    for(j=0;j<(int)(pow(2,level_sup)-1-i);j++){
      /* edge_u */
      mgrid[level_sup][i  ][j  ].function_v[edge_u]=
        0.5*mgrid[level_sup][i-1][j  ].function_v[edge_u]+
        0.5*mgrid[level_sup][i+1][j  ].function_v[edge_u];

        }
    /* edge_u */
    mgrid[level_sup][i][(int)(pow(2,level_sup)-1-i)].function_v[edge_u]=
      0.5*mgrid[level_sup][i-1][j+1].function_v[edge_u]+
      0.5*mgrid[level_sup][i+1][j-1].function_v[edge_u];
   mgrid[level_sup][i][(int)(pow(2,level_sup)-2-i)].function_v[edge_u]=
      0.5*mgrid[level_sup][i-1][(int)(pow(2,level_sup)-2-i)+1].function_v[edge_u]+
      0.5*mgrid[level_sup][i+1][(int)(pow(2,level_sup)-2-i)-1].function_v[edge_u];
  }
  mgrid[level_sup][i][0].function_v[edge_u]=
    mgrid[level_sup][i-1][0].function_v[edge_u];

  /* EDGE V - middle files */
  for(i=0;i<(int)(pow(2,level_sup)-1);i=i+2){
    for(j=0;j<=i;j++){
      if(i==j){ // Base of triangle
        mgrid[level_sup][i-j][j].function_v[edge_v]=
          0.5*mgrid[level_sup][i-j+1][j].function_v[edge_v];
      }else{
      mgrid[level_sup][i-j][j].function_v[edge_v]=
        (mgrid[level_sup][i-j+1][j].function_v[edge_v]+
         mgrid[level_sup][i-j-1][j].function_v[edge_v])/2;
      }
    }
  }
  for(i=0;i<(int)(pow(2,level_sup)-1);i++){
    for(j=1;j<=(int)(pow(2,level_sup)-i-1);j=j+2){
      if(i==0){
        mgrid[level_sup][i][j].function_v[edge_w]=
          0.5*mgrid[level_sup][i+1][j-1].function_v[edge_w];
      }else{
        mgrid[level_sup][i][j].function_v[edge_w]=
          (mgrid[level_sup][i+1][j-1].function_v[edge_w]+
           mgrid[level_sup][i-1][j+1].function_v[edge_w])/2;
      }
    }
  }
}
