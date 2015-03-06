/*
 * =====================================================================================
 *
 *       Filename:  defect.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/02/15 18:30:04
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
#include "defect.h"


// TODO: have a look if we need interior points or more
void compute_defect(triangle*** mgrid, int level, _operator** oper){
  int i,j,l,m;
  double temp0;
  double temp1;
  double temp2;
  /* defect in edge u */
  for(i=1;i<(int)(pow(2,level)-1);i++){ // For all files, interior points
    for(j=1;j<(int)(pow(2,level)-i-1);j++){ // for all columns, interior points
      for(l=0;l<3;l++){
        for(m=0;m<3;m++){
         temp0=temp0+oper[level][uu].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_u];
         temp1=temp1+oper[level][uv].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_v];
         temp2=temp2+oper[level][uw].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_w];
        }
      }
      mgrid[level][i][j].function_v[edge_u]=
        mgrid[level][i][j].function_f[edge_u]+(temp0+temp1+temp2);
    }
  }
  /* defect in edge v */
  for(i=1;i<(int)(pow(2,level)-1);i++){ // For all files, interior points
    for(j=1;j<pow(2,level)-i-1;j++){ // For all columns
      temp0=0.0;
      temp1=0.0;
      temp2=0.0;
      for(l=0;l<3;l++){
        for(m=0;m<3;m++){
         temp0=temp0+oper[level][vu].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_u];
         temp1=temp1+oper[level][vv].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_v];
         temp2=temp2+oper[level][vw].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_w];
        }
      }
      mgrid[level][i][j].function_v[edge_v]=
        mgrid[level][i][j].function_f[edge_v]+(temp0+temp1+temp2);
    }
  }
  /* defect in edge w */
  for(i=1;i<(int)(pow(2,level)-1);i++){ // For all files, interior points
    for(j=1;j<pow(2,level)-i-1;j++){ // For all columns
      temp0=0.0;
      temp1=0.0;
      temp2=0.0;
      for(l=0;l<3;l++){
        for(m=0;m<3;m++){
          temp0=temp0+oper[0][wu].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_u];
          temp1=temp1+oper[0][wv].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_v];
          temp2=temp2+oper[0][ww].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_w];
        }
      }
      mgrid[level][i][j].function_v[edge_w]=
        mgrid[level][i][j].function_f[edge_w]+(temp0+temp1+temp2);
    }
  }
}



