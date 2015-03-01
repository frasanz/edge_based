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
 * TODO: include f?
 */
void smooth_1(triangle *** mgrid, int level, _operator ** oper){
  int i,j,l,m;
  double temp0 = 0.0;
  double temp1 = 0.0;
  double temp2 = 0.0;
  double h2 = pow(1/pow(2,level),2);

  for(i=1;i<(int)(pow(2,level)-1);i++){ // For all files, interior points
    for(j=1;j<(int)(pow(2,level)-i-1);j++){ // For all columns
      temp0=0.0;
      temp1=0.0;
      temp2=0.0;
      /* Smoothing edge u */
      for(l=0;l<3;l++){
        for(m=0;m<3;m++){
          if((l!=1) && (m!=1))
            temp0=temp0-oper[0][uu].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_u];
          temp1=temp1-oper[0][uv].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_v];
          temp2=temp2-oper[0][uw].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_w];
        }
      }
      mgrid[level][i][j].function_u[edge_u]=
        (mgrid[level][i][j].function_f[edge_u]*h2
          +temp0+temp1+temp2)/oper[0][uu].op[1][1];
    }
  }
  for(i=1;i<(int)(pow(2,level)-1);i++){ // For all files, interior points
    for(j=1;j<pow(2,level)-i-1;j++){ // For all columns
      temp0=0.0;
      temp1=0.0;
      temp2=0.0;
      for(l=0;l<3;l++){
        for(m=0;m<3;m++){
          temp0=temp0-oper[0][vu].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_u];
          if((l!=1) && (m!=1))
            temp1=temp1-oper[0][vv].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_v];
          temp2=temp2-oper[0][vw].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_w];
        }
      }
      mgrid[level][i][j].function_u[edge_v]=
        (mgrid[level][i][j].function_f[edge_v]*h2
         +temp0+temp1+temp2)/oper[0][vv].op[1][1];
    }
  }
  for(i=1;i<(int)(pow(2,level)-1);i++){ // For all files, interior points
    for(j=1;j<pow(2,level)-i-1;j++){ // For all columns
      temp0=0.0;
      temp1=0.0;
      temp2=0.0;
      for(l=0;l<3;l++){
        for(m=0;m<3;m++){
          temp0=temp0-oper[0][wu].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_u];
          temp1=temp1-oper[0][wv].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_v];
          if((l!=1) && (m!=1))
            temp2=temp2-oper[0][ww].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_w];
        }
      }
      mgrid[level][i][j].function_u[edge_w]=
        (mgrid[level][i][j].function_f[edge_w]*h2
         +temp0+temp1+temp2)/oper[0][ww].op[1][1];
    }
  }
}

