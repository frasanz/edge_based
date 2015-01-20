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
#include <string.h>
#include <strings.h>
#include "mytypes.h"
#include "memory.h"
#include "initialize.h"
#include "screen.h"
#include "test.h"
#include "helper.h"


#define SIZE 4

int main(int argc, char **argv){
  if(checkCmdLineFlag(argc, (const char **)argv, "test")){
    run_test();
    return 0;
  }
  triangle *** mgrid;
  mgrid = allocate_multigrid(SIZE);
  initialize_multigrid_files(mgrid, SIZE);
  print_multigrid(mgrid,SIZE);
  initialize_multigrid_columns(mgrid, SIZE);
  print_multigrid(mgrid,SIZE);
  initialize_multigrid_levels(mgrid, SIZE);
  print_multigrid(mgrid,SIZE);
  free_multigrid(mgrid,SIZE);
  return 0;
}

