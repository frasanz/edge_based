/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/01/15 23:33:56
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
#include <string.h>
#include <strings.h>
#include "mytypes.h"
#include "memory.h"
#include "initialize.h"
#include "screen.h"
#include "test.h"




void run_test(){

  /* We're going to build a 10 levels multigrid
   * to run some tests */
  int size=10;
  int i;

  printf("[TESTS]\n\n");
  triangle *** mgrid;
  
  /* TEST #1, Allocating and deallocating mgrid */
  printf("\t[TEST#1] Allocating and deallocating %d levels, %d times\n",size,10);
  for(i=0;i<10;i++){
    mgrid=allocate_multigrid(size);
    free_multigrid(mgrid,size);
  }
  /* if we reach this point, everyting is ok, probably, as we're not using 
   * memset the allocation actually doesn't nothing */
  printf("\t[TEST#1] OK\n\n");
  

  /* TEST #2, Initializing all grids with a predefined value */
  printf("\t[TEST#2] Initializing all grids with a predefined value: %d\n",5);
  mgrid=allocate_multigrid(size);
  initialize_multigrid(mgrid,size,5);
}
