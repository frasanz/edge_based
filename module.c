/*
 * =====================================================================================
 *
 *       Filename:  module.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  30/01/15 18:36:27
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
#include "mytypes.h"

double max_of_triangle(triangle ** tri, int element, int level){
  int i,j,k;
  double max=0.0;
  for(i=0;i<pow(2,level);i++){
    for(j=0;j<pow(2,level-i);j++){
      for(k=0;k<3;k++){
        if(element==U){
          if(max<fabs(tri[i][j].function_u[k])){
            max=fabs(tri[i][j].function_u[k]);
          }
        } else if(element == V){
          if(max<fabs(tri[i][j].function_v[k])){
            max=fabs(tri[i][j].function_v[k]);
          }
        } else if(element == F){
          if(max<fabs(tri[i][j].function_f[k])){
            max=fabs(tri[i][j].function_f[k]);
          }
        }
      }
    }
  }
  return max;
}

