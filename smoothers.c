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
  for(i=1;i<pow(2,level)-1;i++){ // For all files, interior points
    for(j=1;j<pow(2,level-i)-1;j++){ // For all columns
        mgrid[level][i][j].U[0]=oper[0][0].op[3]*mgrid[level][i][j-1]+
                                oper[0][0].op[4]*mgrid[level][i][j]+
                                oper[0][0].op[5]*mgrid[level][i][j+1];
    }
  }
}

