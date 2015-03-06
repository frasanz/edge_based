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
  if(checkCmdLineFlag(argc, (const char **)argv, "two")){
    printf("\t[INFO] calling multigrid_two\n\n");
    multigrid_two();
    return 0;
  }
  if(checkCmdLineFlag(argc, (const char **)argv, "firstmultigrid")){
    printf("\t[INFO] calling firstmultigrid\n\n");
    firstmultigrid();
    return 0;
  }

  return 0;
}

