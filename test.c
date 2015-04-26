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
#include "initialize_operator.h"
#include "module.h"
#include "smoothers.h"
#include "restrict.h"
#include "interpolation.h"
#include "defect.h"
#include "correct.h"
#include "draw.h"


void run_test(){

  /* We're going to build a 10 levels multigrid
   * to run some tests */
  int size=12;
  int i,j,k,l;
  int triangles_alloc=0;
  const char * testoutput="test.out";
  const char * testoutput2="smooth.out";
  const char * testrestrictoutput="restrict.out";
  const char * testinterpolateoutput="interpolate.out";
  FILE *f;
  triangle *** mgrid;
  _operator ** operators;

  printf("[TESTS]\n\n");
  /* Calculating the memory needed */
  for(i=0;i<size;i++)
    triangles_alloc=triangles_alloc+3*(pow(2,i)*(pow(2,i)+1)/2);
  printf("\t[INFO] We will need %fMB for this test\n\n",
      1.0*triangles_alloc*sizeof(triangle)/1024/1024);

  
  /* TEST #1, Allocating and deallocating mgrid */
  printf("\t[TEST#1] Allocating and deallocating %d levels, %d times\n",size,15);
  for(i=0;i<15;i++){
    mgrid=allocate_multigrid(size);
    free_multigrid(mgrid,size);
  }
  /* if we reach this point, everyting is ok, probably, as we're not using 
   * memset the allocation actually doesn't nothing */
  printf("\t[TEST#1] OK\n\n");


  mgrid=allocate_multigrid(size);

  
  /* TEST #2, Initializing all grids with a predefined value */
  printf("\t[TEST#2] Initializing all grids with a predefined value: %d\n",5);
  initialize_multigrid(mgrid,size,5);

  /* We're going to check if all the values are the predefined one */
  for(i=0; i< size; i++){
    for(j=0 ; j< pow(2,i); j++){
      for(k=0; k<pow(2,i)-j; k++){
        for(l=0; l<3; l++){
          if(mgrid[i][j][k].function_u[l] != 5.0 ||
             mgrid[i][j][k].function_v[l] != 5.0 ||
             mgrid[i][j][k].function_f[l] != 5.0){
            printf("\t[TEST#2] Error in %d ->(%d %d)",i,j,k);
            exit(EXIT_FAILURE);
          }
        }
      }
    }
  }
  /* if we're here, test #2 is ok */
  printf("\t[TEST#2] maximum value in last function_u(u,v,w) %f\n",max_of_triangle(mgrid[size-1],U,size-1));
  printf("\t[TEST#2] maximum value in last function_v(u,v,w) %f\n",max_of_triangle(mgrid[size-1],U,size-1));
  printf("\t[TEST#2] maximum value in last function_f(u,v,w) %f\n",max_of_triangle(mgrid[size-1],U,size-1));
  printf("\t[TEST#2] OK\n\n");

  /* TEST #3 Initializating all grid, each file has its identified value */
  printf("\t[TEST#3] Initializating all grids, each file has its identified value\n");
  initialize_multigrid_files(mgrid,size);

  /* We're going to check if each file has the desired value */
  for(i=0; i< size; i++){
    for(j=0 ; j< pow(2,i); j++){
      for(k=0; k<pow(2,i)-j; k++){
        for(l=0; l<3; l++){
          if(mgrid[i][j][k].function_u[l] != 1.0*j ||
             mgrid[i][j][k].function_v[l] != 1.0*j ||
             mgrid[i][j][k].function_f[l] != 1.0*j){
            printf("\t[TEST#3] Error in %d ->(%d %d)",i,j,k);
            exit(EXIT_FAILURE);
          }
        }
      }
    }
  }
  /* if we're here, test #3 is ok */
  printf("\t[TEST#3] maximum value in last function_u(u,v,w) %f\n",max_of_triangle(mgrid[size-1],U,size-1));
  printf("\t[TEST#3] maximum value in last function_v(u,v,w) %f\n",max_of_triangle(mgrid[size-1],U,size-1));
  printf("\t[TEST#3] maximum value in last function_f(u,v,w) %f\n",max_of_triangle(mgrid[size-1],U,size-1));
  printf("\t[TEST#3] OK\n\n");

  /* TEST #4 Initializating all grid, each column has its identified value */
  printf("\t[TEST#4] Initializating all grids, each column has its identified value\n");
  initialize_multigrid_columns(mgrid,size);

  /* We're going to check if each file has the desired value */
  for(i=0; i< size; i++){
    for(j=0 ; j< pow(2,i); j++){
      for(k=0; k<pow(2,i)-j; k++){
        for(l=0; l<3; l++){
          if(mgrid[i][j][k].function_u[l] != 1.0*k ||
             mgrid[i][j][k].function_v[l] != 1.0*k ||
             mgrid[i][j][k].function_f[l] != 1.0*k){
            printf("\t[TEST#4] Error in %d ->(%d %d)",i,j,k);
            exit(EXIT_FAILURE);
          }
        }
      }
    }
  }
  /* if we're here, test #3 is ok */
  printf("\t[TEST#4] maximum value in last function_u(u,v,w) %f\n",max_of_triangle(mgrid[size-1],U,size-1));
  printf("\t[TEST#4] maximum value in last function_v(u,v,w) %f\n",max_of_triangle(mgrid[size-1],U,size-1));
  printf("\t[TEST#4] maximum value in last function_f(u,v,w) %f\n",max_of_triangle(mgrid[size-1],U,size-1));
  printf("\t[TEST#4] OK\n\n");


  /* TEST #5, each grid has its level value */
  printf("\t[TEST#5] Initializing all grids, each grid has its level value\n ");
  for(i=0;i<size;i++)
    initialize_grid(mgrid[i],i,i);

  /* We're going to check if each grid has the desired value */
  for(i=0; i< size; i++){
    for(j=0 ; j< pow(2,i); j++){
      for(k=0; k<pow(2,i)-j; k++){
        for(l=0; l<3; l++){
          if(mgrid[i][j][k].function_u[l] != 1.0*i ||
             mgrid[i][j][k].function_v[l] != 1.0*i ||
             mgrid[i][j][k].function_f[l] != 1.0*i){
            printf("\t[TEST#5] Error in %d ->(%d %d)",i,j,k);
            exit(EXIT_FAILURE);
          }
        }
      }
    }
  }
  /* if we're here, test #3 is ok */
  printf("\t[TEST#5] maximum value in last function_u(u,v,w) %f\n",
      max_of_triangle(mgrid[size-1],U,size-1));
  printf("\t[TEST#5] maximum value in last function_v(u,v,w) %f\n",
      max_of_triangle(mgrid[size-1],U,size-1));
  printf("\t[TEST#5] maximum value in last function_f(u,v,w) %f\n",
      max_of_triangle(mgrid[size-1],U,size-1));
  printf("\t[TEST#5] OK\n\n");
  free_multigrid(mgrid,size);

  size=5;
  mgrid=allocate_multigrid(size);
  printf("\t[TEST#6] Printing random multigrid to file: %s\n",testoutput);
  initialize_multigrid_random(mgrid,size);
  f = fopen (testoutput,"w");
  if (f==NULL) {
    printf("\t[TEST#6] Error opening file %s\n",testoutput);
    exit(EXIT_FAILURE);
  } else {
    print_multigrid(f,mgrid,size);
    printf("\t[TEST#6] maximum value in last function_u(u,v,w) %f\n",
        max_of_triangle(mgrid[size-1],U,size-1));
    printf("\t[TEST#6] maximum value in last function_v(u,v,w) %f\n",
        max_of_triangle(mgrid[size-1],U,size-1));
    printf("\t[TEST#6] maximum value in last function_f(u,v,w) %f\n",
        max_of_triangle(mgrid[size-1],U,size-1));
    printf("\t[TEST#6] Ended\n\n");
    fclose(f);
  }

  /* Initialize the last level, border = 0 */
  printf("\t[TEST#7] Putting border=0 in level %d\n",size-1);
  initialize_boundary(mgrid[size-1],size-1,0.0,0); // 0=u, 1=v, 2=f
  f = fopen (testoutput,"a");
  if (f==NULL) {
    printf("\t[TEST#7] Error opening file %s\n",testoutput);
    exit(EXIT_FAILURE);
  } else {
    print_multigrid(f,mgrid,size);
    printf("\t[TEST#7] maximum value in last function_u(u,v,w) %f\n",
        max_of_triangle(mgrid[size-1],U,size-1));
    printf("\t[TEST#7] maximum value in last function_v(u,v,w) %f\n",
        max_of_triangle(mgrid[size-1],V,size-1));
    printf("\t[TEST#7] maximum value in last function_f(u,v,w) %f\n",
        max_of_triangle(mgrid[size-1],F,size-1));
    printf("\t[TEST#7] Ended\n\n");
    fclose(f);
  }
  free_multigrid(mgrid,size);

  size=5;
  printf("\t[TEST#8] Initializing operators: -grad(div)+curl(rot) up to size %d\n",
      size);
  operators=allocate_operators("-grad(div)+curl(rot)",size);
  initialize_operators(operators,"-grad(div)+curl(rot)",size);
  f = fopen(testoutput, "a");
  if(f==NULL){
    printf("\t[TEST#8] Error opening file %s\n", testoutput);
    exit(EXIT_FAILURE);
  } else {
    print_all_operators(f, operators, size);
    printf("\t[TEST#8] Ended\n\n");
    fclose(f);
  }

  printf("\t[TEST#9] Doing lexicographic smoother %d\n",size-1);
  mgrid=allocate_multigrid(size);
  initialize_multigrid_random(mgrid,size);
  initialize_boundary(mgrid[size-1],size-1,0.0,0);
  f = fopen (testoutput2,"w");
  if (f==NULL) {
    printf("\t[TEST#9] Error opening file %s\n",testoutput);
    exit(EXIT_FAILURE);
  } else {
      print_grid_u(f,mgrid[size-1],size-1);
      fclose(f);
    }
    for(j=0;j<100;j++){
      smooth_1(mgrid,size-1,operators);
      printf("\t[TEST#9] iter %d: maximum value in last function_u(u,v,w) %f\n",
          j,max_of_triangle(mgrid[size-1],U,size-1));

    }
    f = fopen (testoutput2,"a");
    if (f==NULL) {
      printf("\t[TEST#9] Error opening file %s\n",testoutput);
      exit(EXIT_FAILURE);
    } else {
      print_grid_u(f,mgrid[size-1],size-1);
      fclose(f);
    }
    printf("\t[TEST#9] Ended\n\n");
    free_multigrid(mgrid,size);

    size = 5;
    printf("\t[TEST#10] Restriction from %d to %d\n",size-1, size-2);
    mgrid=allocate_multigrid(size);
    initialize_multigrid_random(mgrid,size);
    initialize_boundary(mgrid[size-1],size-1,0.0,0);
    initialize_grid(mgrid[size-2],size-2,0.0);
    restrict_one(mgrid,size-1);
    f = fopen (testrestrictoutput,"w");
    if (f==NULL) {
      printf("\t[TEST#10] Error opening file %s\n",testrestrictoutput);
      exit(EXIT_FAILURE);
    } else {
      print_grid_v(f,mgrid[size-1],size-1);
      print_grid_f(f,mgrid[size-2],size-2);
      fclose(f);
    }
    printf("\t[TEST#10] Max in level %d function_v=%e\n",size-1,
        max_of_triangle(mgrid[size-1],V,size-1));
    printf("\t[TEST#10] Max in level %d function_f=%e\n",size-2,
          max_of_triangle(mgrid[size-2],F,size-2));
    printf("\t[TEST#10] Ended\n\n");
    free_multigrid(mgrid,size);

    printf("\t[TEST#11] Interpolation from %d to %d\n",size-2,size-1);
    mgrid=allocate_multigrid(size);
    initialize_multigrid_random(mgrid,size);
    initialize_boundary(mgrid[size-2],size-2,0.0,0);
    initialize_grid(mgrid[size-1],size-1,0.0);
    interpolate_one(mgrid,size-2);
    f = fopen (testinterpolateoutput,"w");
    if (f==NULL) {
      printf("\t[TEST#11] Error opening file %s\n",testinterpolateoutput);
      exit(EXIT_FAILURE);
    } else {
      print_grid_u(f,mgrid[size-2],size-2);
      print_grid_u(f,mgrid[size-1],size-1);
      fclose(f);
    }
    printf("\t[TEST#11] Ended\n\n");
    free_multigrid(mgrid,size);
  }

  void multigrid_two(){
    int triangles_alloc=0;
    int size=6;
      int i,j;
      triangle *** mgrid;
    _operator ** operators;
    FILE *f;
    double defect_ant=1.0;
    double defect=1.0;
    const char * testrestrictoutput="two.out";
    char aux[256];

    /* Open F file for output */
    f = fopen (testrestrictoutput,"w");
    if (f==NULL) {
      printf("\t[INFO] Error opening file %s\n",testrestrictoutput);
      exit(EXIT_FAILURE);
    } 

      /* Calculating the memory needed */
    for(i=0;i<size;i++)
      triangles_alloc=triangles_alloc+3*(pow(2,i)*(pow(2,i)+1)/2);
    printf("\t[INFO] We will need %fMB for this test\n\n",
        1.0*triangles_alloc*sizeof(triangle)/1024/1024);

    /* Initializing operators */
    printf("\t[INFO] Initializing operators: -grad(div)+curl(rot) up to size %d\n",
        size);
    operators=allocate_operators("-grad(div)+curl(rot)",size);
    initialize_operators(operators,"-grad(div)+curl(rot)",size);

    /* Allocating memory*/
    printf("\t[INFO] Allocating memory up to %d  levels\n",size);
    mgrid=allocate_multigrid(size);

    /* Initializing all grids with predefinied 0 value */
    printf("\t[INFO] Initializing all grids with a predefined value: %d\n",0); 
    initialize_multigrid(mgrid, size,0);

    /* Initializing las grid function_u random */
    printf("\t[INFO] Initializing last grid function_u random\n");
    initialize_grid_function_u_random(mgrid[size-1],size-1);

    /* Initializing the boundary in the function_u */
    printf("\t[INFO] Boundary=%d in funcion_u, (level %d)\n",0,size);
    initialize_boundary(mgrid[size-1],size-1,0.0,0);


    /* The initialization is done, at this point we're going to start
     * with the two-levels multigrid 
     */
  /* Pre-smooth u_m, f_m -> u_m */


  int draw_step=199;
        for(i=0;i<240;i++){
    if(i==draw_step){
      sprintf(aux,"%s_%d","1_U_level_sup_step#",draw_step);
      draw_triangle(mgrid[size-1], size-1, U, edge_v,aux);
    }

 
    /* Compute the defect u_m, f_m -> v_m*/
    compute_defect(mgrid, size-1, operators);
    if(i==draw_step){
      sprintf(aux,"%s_%d","2_V(defect)_level_sup_step#",draw_step);
      draw_triangle(mgrid[size-1], size-1, V, edge_v,aux);
    }


    /* Restrict the defect v_m -> f_m-1 */
    initialize_grid(mgrid[size-2],size-2,0.0);
    restrict_one(mgrid, size-1);
    if(i==draw_step){
      sprintf(aux,"%s_%d","3_F(restricted)_level_inf_step#",draw_step);
      draw_triangle(mgrid[size-2], size-2, F, edge_v,aux);
    }

    /* Compute the solution in the lowest level -> u_m-1,
     * in this case we're going to do 10 iteration of the 
     * smoothing procedure, starting with a random value */
    for(j=0;j<1000;j++){
      smooth_1(mgrid,size-2,operators);
    }
    compute_defect(mgrid, size-2, operators);
    printf("\t\t[INFO] iter %d: defect level down=%e\n",
        i,max_of_triangle(mgrid[size-2],V,size-2));
    printf("\t\t[INFO] iter %d: max value u level down=%e\n",
        i,max_of_triangle(mgrid[size-2],U,size-2));
    if(i==draw_step){
      sprintf(aux,"%s_%d","4_U(solution)_level_inf_step#",draw_step);
      draw_triangle(mgrid[size-2], size-2, U, edge_v,aux);
    }



    /* Interpolate u_m-1 -> v_m */
    interpolate_linear(mgrid,size-2);
    if(i==draw_step){
      sprintf(aux,"%s_%d","5_V(interpolation)_level_sup_step#",draw_step);
      draw_triangle(mgrid[size-1], size-1, V, edge_v,aux);
    }



    /* Corrected solution u_m, v_m -> u_m */
    correct_one(mgrid, size-1);
    if(i==draw_step){
      sprintf(aux,"%s_%d","6_U(corrected)_level_sup_step#",draw_step);
      draw_triangle(mgrid[size-1], size-1, U, edge_v,aux);
    }



    /* Post-smooth u_m, f_m -> u_m */
    smooth_1(mgrid, size-1, operators);
    if(i==draw_step){
      sprintf(aux,"%s_%d","7_U(postsmooth)_level_sup_step#",draw_step);
      draw_triangle(mgrid[size-1], size-1, U, edge_v,aux);
    }

    /* Compute the defect to check u_m, f_m -> v_m */
    compute_defect(mgrid, size-1, operators);
    defect_ant=defect;
    defect=max_of_triangle(mgrid[size-1],V,size-1);
    printf("\t[INFO] iter %d: maximum value in last function_v(u,v,w) %e, ratio=%f\n",
          i,defect, defect/defect_ant);
  }
  fclose(f);
}

void firstmultigrid(){

  printf("\t[INFO] Called first multigrid\n");
  int triangles_alloc=0;
  int size=12;
  int i;
  triangle *** mgrid;
  _operator ** operators;
  FILE *f;
  double defect_ant=1.0;
  double defect=1.0;
  const char * fileoutput="firstmultigrid.out";

  /* Open output file */
  f = fopen(fileoutput, "w");
  if (f==NULL){
    printf("\t[INFO] Error opening file %s\n",fileoutput);
    exit(EXIT_FAILURE);
  }

  /* Calculating needed memory */
  for(i=0;i<size;i++){
    triangles_alloc=triangles_alloc+3*(pow(2,i)*(pow(2,i)+1)/2);
  }
  printf("\t[INFO] We'll need %fMB for this test\n\n",
     1.0*triangles_alloc*sizeof(triangle)/1024/1024);

  /* Initializing operators */
  printf("\t[INFO] Initializing operators: -grad(div)+curl(rot) up to size %d\n",
      size);
  operators=allocate_operators("-grad(div)+curl(rot)",size);
  initialize_operators(operators, "-grad(div)+curl(rot)",size);

  /* Allocating memory */
  printf("\t[INFO] Allocating memory up to %d levels\n",size);
  mgrid=allocate_multigrid(size);

  /* Initializing all grids with predefinied 0 value */
  printf("\t[INFO] Initializing all grids with a predefinied value: %d\n",0);
  initialize_multigrid(mgrid,size,0);

  /* Initializing las grid function_u random */
  printf("\t[INFO] Initializing last grid function_u random\n");
  initialize_grid_function_u_random(mgrid[size-1],size-1);

  /* Initializing the boundary in the function_u */
  printf("\t[INFO] Boundary=%d in funcion_u, (level %d)\n",0,size-1);
  initialize_boundary(mgrid[size-1],size-1,0.0,0);

  /* Here is the main loop */
  for(i=0;i<100;i++){
    initialize_grid_function_value(mgrid[size-1],size-1,0.0,V);
    initialize_grid_function_value(mgrid[size-1],size-1,0.0,F);
    defect_ant=defect;
    defect=firstmultigrid_loop(mgrid,operators,size,size-1,2);

    printf("\t[INFO] iter %d: maximum value in last function_v(u,v,w) %e, ratio=%f\n",
          i,defect, defect/defect_ant);
  }
}

double firstmultigrid_loop(triangle ***mgrid, _operator ** operators, 
    int size, int level, int times){
    int j;
  //printf("\tlevel %d smooth\n",level);
  smooth_1(mgrid, level, operators);

  //printf("\tlevel %d, defect\n",level);
  compute_defect(mgrid,level, operators);
  initialize_grid(mgrid[level-1],level-1,0.0);
  //printf("\tlevel %d, restrict from %d to %d\n",level, level, level-1);
  restrict_one(mgrid, level);

  if(level==3){
    //printf("\tlevel %d, exact\n",level-1);
    for(j=0;j<2000;j++)
      smooth_1(mgrid,level-1,operators);
  }else{
      firstmultigrid_loop(mgrid, operators, size, level-1,times);
  }
  //printf("\tlevel %d, interpolate from %d to %d\n",level, level-1, level);
  interpolate_linear(mgrid,level-1);
  //printf("\tlevel %d correct\n", level);
  correct_one(mgrid,level);
  //printf("\tlevel %d, smooth\n",level);
  smooth_1(mgrid,level, operators);

  if(times>=2 && level > 3){
      //printf("recall\n");
      firstmultigrid_loop(mgrid,operators,size,level,times-1);
  }
  if(level==size-1){
    compute_defect(mgrid,level,operators);
    return max_of_triangle(mgrid[level],V,level);
  }
  return 0.0;
}

void firstmultigridparallel(){

  printf("\t[INFO] Called firstmultigridparallel\n");
  int triangles_alloc=0;
  int size=5;
  int i;
  triangle *** mgrid;
  _operator ** operators;
  FILE *f;
  double defect_ant=1.0;
  double defect=1.0;
  const char * fileoutput="firstmultigrid.out";

  /* Open output file */
  f = fopen(fileoutput, "w");
  if (f==NULL){
    printf("\t[INFO] Error opening file %s\n",fileoutput);
    exit(EXIT_FAILURE);
  }

  /* Calculating needed memory */
  for(i=0;i<size;i++){
    triangles_alloc=triangles_alloc+3*(pow(2,i)*(pow(2,i)+1)/2);
  }
  printf("\t[INFO] We'll need %fMB for this test\n\n",
     1.0*triangles_alloc*sizeof(triangle)/1024/1024);

  /* Initializing operators */
  printf("\t[INFO] Initializing operators: -grad(div)+curl(rot) up to size %d\n",
      size);
  operators=allocate_operators("-grad(div)+curl(rot)",size);
  initialize_operators(operators, "-grad(div)+curl(rot)",size);

  /* Allocating memory */
  printf("\t[INFO] Allocating memory up to %d levels\n",size);
  mgrid=allocate_multigrid(size);

  /* Initializing all grids with predefinied 0 value */
  printf("\t[INFO] Initializing all grids with a predefinied value: %d\n",0);
  initialize_multigrid(mgrid,size,0);

  /* Initializing las grid function_u random */
  printf("\t[INFO] Initializing last grid function_u random\n");
  initialize_grid_function_u_random(mgrid[size-1],size-1);

  /* Initializing the boundary in the function_u */
  printf("\t[INFO] Boundary=%d in funcion_u, (level %d)\n",0,size-1);
  initialize_boundary(mgrid[size-1],size-1,0.0,0);

  /* Here is the main loop */
  for(i=0;i<1;i++){
    initialize_grid_function_value(mgrid[size-1],size-1,0.0,V);
    initialize_grid_function_value(mgrid[size-1],size-1,0.0,F);
    defect_ant=defect;
    defect=firstmultigridparallel_loop(mgrid,operators,size,size-1,2);

    printf("\t[INFO] iter %d: maximum value in last function_v(u,v,w) %e, ratio=%f\n",
          i,defect, defect/defect_ant);
  }
}

double firstmultigridparallel_loop(triangle ***mgrid, _operator ** operators, 
    int size, int level, int times){
    int j;
  //printf("\tlevel %d smooth\n",level);
  smooth_1_parallel(mgrid, level, operators);

  //printf("\tlevel %d, defect\n",level);
  compute_defect(mgrid,level, operators);
  initialize_grid(mgrid[level-1],level-1,0.0);
  //printf("\tlevel %d, restrict from %d to %d\n",level, level, level-1);
  restrict_one(mgrid, level);

  if(level==3){
    //printf("\tlevel %d, exact\n",level-1);
    for(j=0;j<2000;j++)
      smooth_1(mgrid,level-1,operators);
  }else{
      firstmultigrid_loop(mgrid, operators, size, level-1,times);
  }
  //printf("\tlevel %d, interpolate from %d to %d\n",level, level-1, level);
  interpolate_linear(mgrid,level-1);
  //printf("\tlevel %d correct\n", level);
  correct_one(mgrid,level);
  //printf("\tlevel %d, smooth\n",level);
  smooth_1_parallel(mgrid,level, operators);

  if(times>=2 && level > 3){
      //printf("recall\n");
      firstmultigridparallel_loop(mgrid,operators,size,level,times-1);
  }
  if(level==size-1){
    compute_defect(mgrid,level,operators);
    return max_of_triangle(mgrid[level],V,level);
  }
  return 0.0;
}



void  test_draw(){
  printf("\t[INFO] Called test draw\n");
  triangle *** mgrid;
  int size=5;
  mgrid=allocate_multigrid(size);
  initialize_multigrid_columns(mgrid, size);
  draw_triangle(mgrid[size-1], size-1,U,edge_u,"Test draw");
}

void test_restrict(){
  printf("\t[INFO] Called test_restrict\n");
  triangle *** mgrid;
  int size=7;
  mgrid=allocate_multigrid(size);
  initialize_grid_function_v_random(mgrid[size-1],size-1);
  initialize_grid(mgrid[size-2],size-2,0.0);
  draw_triangle(mgrid[size-1],size-1,V,edge_u,"V, edge_u level Up");
  draw_triangle(mgrid[size-1],size-1,V,edge_v,"V, edge_v level Up");
  draw_triangle(mgrid[size-1],size-1,V,edge_w,"V, edge_w level Up");
  restrict_one(mgrid, size-1);
  draw_triangle(mgrid[size-2],size-2,F,edge_u,"f, edge_u level down");
  draw_triangle(mgrid[size-2],size-2,F,edge_v,"f, edge_v level down");
  draw_triangle(mgrid[size-2],size-2,F,edge_w,"f, edge_w level down");
}

void test_interpolate(){
  printf("\t[INFO] Called test_interpolate\n");
  triangle *** mgrid;
  int size=10;
  mgrid=allocate_multigrid(size);
  initialize_multigrid(mgrid,size,0);
  initialize_grid_columns(mgrid[size-2],size-2);
  draw_triangle(mgrid[size-2],size-2,U,edge_u,"U__edge_u__level_down");
  draw_triangle(mgrid[size-2],size-2,U,edge_v,"U__edge_v__level_down");
  draw_triangle(mgrid[size-2],size-2,U,edge_w,"U__edge_w__level_down");
  interpolate_one(mgrid, size-2);
  draw_triangle(mgrid[size-1],size-1,V,edge_u,"V__edge_u__level_up");
  draw_triangle(mgrid[size-1],size-1,V,edge_v,"V__edge_v__level_up");
  draw_triangle(mgrid[size-1],size-1,V,edge_w,"V__edge_w__level_up");
}

void test_interpolate_linear(){
  printf("\t[INFO] Called test_interpolate_linear\n");
  triangle *** mgrid;
  int size=5;
  mgrid=allocate_multigrid(size);
  initialize_multigrid(mgrid,size,0);
  initialize_grid(mgrid[size-2],size-2,5.0);
  interpolate_linear(mgrid, size-2);
  draw_triangle(mgrid[size-1],size-1,V,edge_u,"V__edge_u__level_up");
  draw_triangle(mgrid[size-1],size-1,V,edge_v,"V__edge_v__level_up");
  draw_triangle(mgrid[size-1],size-1,V,edge_w,"V__edge_w__level_up");
}



void test_smooth(){
  printf("\t[INFO] Called test_smooth\n");
  char title[256];
  int i;
  triangle *** mgrid;
  int size=7;
  _operator ** operators;

  operators=allocate_operators("-grad(div)+curl(rot)",size);
  initialize_operators(operators,"-grad(div)+curl(rot)",size);

  mgrid=allocate_multigrid(size);
  initialize_multigrid(mgrid,size,0);
  initialize_grid_function_u_random(mgrid[size-1],size-1);
  initialize_boundary(mgrid[size-1],size-1,0.0,0);
  for(i=0;i<9;i++){
    smooth_1(mgrid,size-1,operators);
    if(i%1==0){
      sprintf(title,"%s_%d","U__edge_u_iter",i);
      draw_triangle(mgrid[size-1],size-1,U,edge_u,title);
      //sprintf(title,"%s_%d","U__edge_v_iter",i);
      //draw_triangle(mgrid[size-1],size-1,U,edge_v,title);
      //sprintf(title,"%s_%d","U__edge_w_iter",i);
      //draw_triangle(mgrid[size-1],size-1,U,edge_w,title);
    }
  }
}

void test_defect(){
  int size=3;
  int i;
  printf("\t[INFO] Called test_defect\n");
  triangle *** mgrid;
  _operator ** operators;
  operators=allocate_operators("-grad(div)+curl(rot)",size);
  initialize_operators(operators,"-grad(div)+curl(rot)",size);

  mgrid=allocate_multigrid(size);
  initialize_multigrid(mgrid,size,0);
  initialize_grid_function_u_random(mgrid[size-1],size-1);
  initialize_boundary(mgrid[size-1],size-1,0.0,0);
 for(i=0;i<20;i++){
    smooth_1(mgrid,size-1,operators);
  }
  compute_defect(mgrid,size-1,operators);
  draw_triangle(mgrid[size-1],size-1,V,edge_u,"defect_edge_u_iter_5");
  draw_triangle(mgrid[size-1],size-1,U,edge_u,"U_edge_u_iter_5");
  draw_triangle(mgrid[size-1],size-1,V,edge_v,"defect_edge_v_iter_5");
  draw_triangle(mgrid[size-1],size-1,U,edge_v,"U_edge_v_iter_5");
  draw_triangle(mgrid[size-1],size-1,V,edge_w,"defect_edge_w_iter_5");
  draw_triangle(mgrid[size-1],size-1,U,edge_w,"U_edge_w_iter_5");
}

