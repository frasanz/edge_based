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
 *   Organization:  Poca
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
#include "onlysmooth.h"
#include "draw.h"
#include "exact.h"


#define SIZE 4

int main(int argc, char **argv){
  if(checkCmdLineFlag(argc, (const char **)argv, "test")){
    run_test();
    return 0;
  } else if(checkCmdLineFlag(argc, (const char **)argv, "two")){
    printf("\t[INFO] calling multigrid_two\n\n");
    multigrid_two();
    return 0;
  } else if(checkCmdLineFlag(argc, (const char **)argv, "firstmultigrid")){
    printf("\t[INFO] calling firstmultigrid\n\n");
    firstmultigrid();
    return 0;
  } else if(checkCmdLineFlag(argc, (const char **)argv, "firstmultigridparallel")){
    printf("\t[INFO] calling firstmultigridparallel\n\n");
    firstmultigridparallel();
    return 0;
  } else if(checkCmdLineFlag(argc, (const char **)argv, "onlysmooth")){
    printf("\t[INFO] calling onlysmooth\n\n");
    onlysmooth();
    return 0;
  } else if(checkCmdLineFlag(argc, (const char **)argv, "onlysmoothparallel")){
    printf("\t[INFO] calling onlysmoothparallel\n\n");
    onlysmoothparallel();
    return 0;
  } else if(checkCmdLineFlag(argc, (const char **)argv, "onlysmoothgaussseidel")){
    printf("\t[INFO] calling onlysmoothgausseidel\n\n");
    onlysmoothgaussseidel();
    return 0;
  } else if(checkCmdLineFlag(argc, (const char **)argv, "test_draw")){
    printf("\t[INFO] calling test_draw\n\n");
    test_draw();
    return 0;
  } else if(checkCmdLineFlag(argc, (const char **)argv, "test_restrict")){
    printf("\t[INFO] calling test_restrict\n\n");
    test_restrict();
    return 0;
  } else if(checkCmdLineFlag(argc, (const char  **)argv, "test_interpolate")){
    printf("\t[INFO] calling test_interpolate\n\n");
    test_interpolate();
    return 0;
  } else if(checkCmdLineFlag(argc, (const char **)argv, "test_smooth")){
    printf("\t[INFO] calling test_smooth\n\n");
    test_smooth();
    return 0;
  } else if(checkCmdLineFlag(argc, (const char **)argv, "test_defect")){
    printf("\t[INFO] calling test_defect\n\n");
    test_defect();
    return 0;
  } else if(checkCmdLineFlag(argc, (const char **)argv, "test_interpolate_linear")){
    printf("\t[INFO] Calling test_interpolate_linear\n\n");
    test_interpolate_linear();
    return 0;
  } else if(checkCmdLineFlag(argc, (const char **)argv, "test_exact")){
    printf("/t[INFO] Calling test_exact\n\n");
    test_exact();
    return 0;
  }
  else{
    printf("\t[INFO] invalid option\n\n");
    return -1;
  }
  return 0;
}

