/*
 * =====================================================================================
 *
 *       Filename:  edged_based.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/01/15 18:25:38
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
#include "memory.h"
#include "initialize.h"


#define SIZE 5

int main(int argc, char **argv){

  triangle *** mgrid;
  mgrid = allocate_multigrid(SIZE);
  initialize_multigrid(mgrid, SIZE,1.0);
  free_multigrid(mgrid,SIZE);
  return 0;
}

