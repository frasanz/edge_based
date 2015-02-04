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

void compute_defect(triangle*** mgrid, int level, _operator** oper){
  int i,j;
  for(i=1;i<(int)(pow(2,level)-1);i++){ // For all files, interior points
    for(j=1;j<(int)(pow(2,level)-i-1);j++){ // for all columns, interior points

    }
  }
}



