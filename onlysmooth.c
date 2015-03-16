/*
 * =====================================================================================
 *
 *       Filename:  onlysmooth.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/03/15 20:07:38
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
#include "initialize_operator.h"
#include "module.h"
#include "smoothers.h"
#include "restrict.h"
#include "interpolation.h"
#include "defect.h"
#include "correct.h"

void onlysmooth(){
  int size=5;
  int i,j;
  triangle *** mgrid;
  _operator ** operators;

  printf("[ONLYSMOOTH]\n\n");
  mgrid=allocate_multigrid(size);

  /* Initialize all grids with 0 */
  initialize_multigrid(mgrid,size,0);

  /* Initialize las grid, function_u with random value */
  initialize_grid_function_u_random(mgrid[size-1],size-1);

  /* Initializing the boundary in the function_u */
  initialize_boundary(mgrid[size-1],size-1,0.0,0);


  
  free_multigrid(size);
}
