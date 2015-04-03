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
#include "draw.h"

void onlysmooth(){
  int size=10;
  int i;
  double val=1.0;
  double val_ant=1.0;
  double def=1.0;
  double def_ant=1.0;
  triangle *** mgrid;
  _operator ** operators;

  printf("[ONLYSMOOTH]\n\n");
  mgrid=allocate_multigrid(size);

  /* Initialize all grids with 0 */
  initialize_multigrid(mgrid,size,0);

  /* Initialize las grid, function_u with random value */
  initialize_grid_function_u_random(mgrid[size-1],size-1);

  /* Only for testing  */
  initialize_grid_function_value(mgrid[size-1],size-1,0.0,F);
  /* Initializing the boundary in the function_u */
  initialize_boundary(mgrid[size-1],size-1,0.0,U);

  /* Initializing operators */
  operators=allocate_operators("-grad(div)+curl(rot)",size);
  initialize_operators(operators,"-grad(div)+curl(rot)",size);

  for(i=0;i<2;i++){
    smooth_1(mgrid, size-1, operators);
    smooth_1(mgrid, size-1, operators);
    val_ant=val;
    val=max_of_triangle(mgrid[size-1],U,size-1);
    compute_defect(mgrid,size-1, operators);
    def_ant=def;
    def=max_of_triangle(mgrid[size-1],V,size-1);
    printf("\t[ONLYSMOOTH] iter %d: max %e ratio in function_u \
 %e maxdef %e ration in function_v %f\n"
      ,i,val, val/val_ant,def,def/def_ant);
    /*if(i%300==0){
      draw_triangle(mgrid[size-1],size-1,U,edge_u,aux);
      sprintf(aux,"iter_%d_edge_v",i);
      draw_triangle(mgrid[size-1],size-1,U,edge_v,aux);
      sprintf(aux,"iter_%d_edge_w",i);
      draw_triangle(mgrid[size-1],size-1,U,edge_w,aux);
    }*/
  }
  free_multigrid(mgrid,size);
}

void onlysmoothparallel(){
  int size=10;
  int i;
  double val=1.0;
  double val_ant=1.0;
  double def=1.0;
  double def_ant=1.0;
  triangle *** mgrid;
  _operator ** operators;

  printf("[ONLYSMOOTHPARALLEL]\n\n");
  mgrid=allocate_multigrid(size);

  /* Initialize all grids with 0 */
  initialize_multigrid(mgrid,size,0);

  /* Initialize las grid, function_u with random value */
  initialize_grid_function_u_random(mgrid[size-1],size-1);

  /* Only for testing  */
  initialize_grid_function_value(mgrid[size-1],size-1,0.0,F);
  /* Initializing the boundary in the function_u */
  initialize_boundary(mgrid[size-1],size-1,0.0,U);

  /* Initializing operators */
  operators=allocate_operators("-grad(div)+curl(rot)",size);
  initialize_operators(operators,"-grad(div)+curl(rot)",size);

  for(i=0;i<10;i++){
    smooth_1_parallel(mgrid, size-1, operators);
    smooth_1_parallel(mgrid, size-1, operators);
    val_ant=val;
    val=max_of_triangle(mgrid[size-1],U,size-1);
    compute_defect(mgrid,size-1, operators);
    def_ant=def;
    def=max_of_triangle(mgrid[size-1],V,size-1);
    printf("\t[ONLYSMOOTHPARALLEL] iter %d: max %e ratio in function_u \
 %e maxdef %e ration in function_v %f\n"
      ,i,val, val/val_ant,def,def/def_ant);
    /*if(i%300==0){
      draw_triangle(mgrid[size-1],size-1,U,edge_u,aux);
      sprintf(aux,"iter_%d_edge_v",i);
      draw_triangle(mgrid[size-1],size-1,U,edge_v,aux);
      sprintf(aux,"iter_%d_edge_w",i);
      draw_triangle(mgrid[size-1],size-1,U,edge_w,aux);
    }*/
  }
  free_multigrid(mgrid,size);
}
void onlysmoothgaussseidel(){
  int size=5;
  int i;
  double val=1.0;
  double val_ant=1.0;
  double def=1.0;
  double def_ant=1.0;
  char aux[256];
  triangle *** mgrid;
  _operator ** operators;

  printf("[ONLYSMOOTHGAUSSSEIDEL]\n\n");
  mgrid=allocate_multigrid(size);

  /* Initialize all grids with 0 */
  initialize_multigrid(mgrid,size,0);

  /* Initialize las grid, function_u with random value */
  initialize_grid_function_value(mgrid[size-1],size-1,0.0,F);
  initialize_grid_function_u_random(mgrid[size-1],size-1);
  initialize_bigboundary(mgrid[size-1],size-1,0.0,U);


  /* Initializing operators */
  operators=allocate_operators("-grad(div)+curl(rot)",size);
  initialize_operators(operators,"-grad(div)+curl(rot)",size);

  for(i=0;i<3;i++){
    sprintf(aux,"%s_%d","U_level_edge_u",i);
    draw_triangle(mgrid[size-1], size-1, U, edge_u,aux);
    sprintf(aux,"%s_%d","U_level_edge_v",i);
    draw_triangle(mgrid[size-1], size-1, U, edge_v,aux);
    sprintf(aux,"%s_%d","U_level_edge_w",i);
    draw_triangle(mgrid[size-1], size-1, U, edge_w,aux);
    smooth_1(mgrid,size-1,operators);
    smooth_gaussseidel(mgrid, size-1, operators);
    val_ant=val;
    val=max_of_triangle(mgrid[size-1],U,size-1);
    compute_defect(mgrid,size-1, operators);
    def_ant=def;
    def=max_of_triangle(mgrid[size-1],V,size-1);
    printf("\t[ONLYSMOOTHGAUSSSEIDEL] iter %d: max %e ratio in function_u \
 %e maxdef %e ration in function_v %f\n"
      ,i,val, val/val_ant,def,def/def_ant);
    /*if(i%300==0){
      draw_triangle(mgrid[size-1],size-1,U,edge_u,aux);
      sprintf(aux,"iter_%d_edge_v",i);
      draw_triangle(mgrid[size-1],size-1,U,edge_v,aux);
      sprintf(aux,"iter_%d_edge_w",i);
      draw_triangle(mgrid[size-1],size-1,U,edge_w,aux);
    }*/
  }
  free_multigrid(mgrid,size);
}

