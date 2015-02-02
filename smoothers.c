/*
 * =====================================================================================
 *
 *       Filename:  smoothers.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  31/01/15 16:37:29
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
#include "smoothers.h"


/* This is only a test of the smoothing procedure
 * At this moment I don't have very clear anything
 */
void smooth_1(triangle *** mgrid, int level){
  int i,j,l,m;
  double temp0 = 0.0;
  double temp1 = 0.0;
  double temp2 = 0.0;

  for(i=1;i<pow(2,level)-1;i++){ // For all files, interior points
    for(j=1;j<pow(2,level-i)-1;j++){ // For all columns
      /* Smoothing edge u */
      for(l=0;l<3;l++){
        for(m=0;m<3;m++){
          temp0=temp0+oper[0][uu].op[3*l+m]*mgrid[level][i+1-l][j-1+m].function_u[edge_u];
          temp1=temp1+oper[0][uv].op[3*l+m]*mgrid[level][i+1-l][j-1+m].function_u[edge_v];
          temp2=temp2+oper[0][uw].op[3*l+m]*mgrid[level][i+1-l][j-1+m].function_u[edge_w];
        }
      }
      mgrid[level][i][j].function_u[edge_u]+temp0+temp1+temp2;
      temp0=0.0;
      temp1=0.0;
      temp2=0.0;

      for(l=0;l<3;l++){
        for(j=0;j<3;j++){
          temp0=temp0+oper[0][vu].op[3*l+m]*mgrid[level][i+1-l][j-1+m].function_u[edge_u];
          temp1=temp1+oper[0][vv].op[3*l+m]*mgrid[level][i+1-l][j-1+m].function_u[edge_v];
          temp2=temp2+oper[0][vw].op[3*l+m]*mgrid[level][i+1-l][j-1+m].function_u[edge_w];
        }
      }
      mgrid[level][i][j].function_u[edge_v]+temp0+temp1+temp2;

      /* Smoothing edge w */
      mgrid[level][i][j].function_u[edge_w]=
        oper[0][wu].op[0]*mgrid[level][i+1][j-1].function_u[edge_u]+
        oper[0][wu].op[1]*mgrid[level][i+1][j  ].function_u[edge_u]+
        oper[0][wu].op[3]*mgrid[level][i  ][j-1].function_u[edge_u]+
        oper[0][wu].op[4]*mgrid[level][i  ][j  ].function_u[edge_u]+
          oper[0][wv].op[0]*mgrid[level][i+1][j-1].function_u[edge_v]+
          oper[0][wv].op[3]*mgrid[level][i  ][j-1].function_u[edge_v]+
          oper[0][wv].op[4]*mgrid[level][i  ][j  ].function_u[edge_v]+
          oper[0][wv].op[7]*mgrid[level][i-1][j  ].function_u[edge_v]+
            oper[0][ww].op[1]*mgrid[level][i+1][j  ].function_u[edge_w]+
            oper[0][ww].op[4]*mgrid[level][i  ][j  ].function_u[edge_w]+
            oper[0][ww].op[7]*mgrid[level][i-1][j  ].function_u[edge_w];
  }
}

