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




void run_test(){

  /* We're going to build a 10 levels multigrid
   * to run some tests */
  int size=10;
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
    int size=4;
    int i,j;
    triangle *** mgrid;
    _operator ** operators;
    FILE *f;
    double defect_ant=1.0;
    double defect=1.0;
    const char * testrestrictoutput="two.out";

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

  for(i=0;i<30;i++){
    smooth_1(mgrid, size-1, operators);

    /* Compute the defect u_m, f_m -> v_m*/
    compute_defect(mgrid, size-1, operators);


    /* Restrict the defect v_m -> f_m-1 */
    restrict_one(mgrid, size-1);



    /* Compute the solution in the lowest level -> u_m-1,
     * in this case we're going to do 10 iteration of the 
     * smoothing procedure, starting with a random value */
    initialize_grid_function_u_random(mgrid[size-2],size-2);
    initialize_boundary(mgrid[size-2],size-2,0.0,0);
    for(j=0;j<10;j++){
      smooth_1(mgrid,size-2,operators);
    }

    /* Interpolate u_m-1 -> v_m */
    interpolate_one(mgrid,size-2);

    /* Corrected solution u_m, v_m -> u_m */
    correct_one(mgrid, size-1);

    /* Post-smooth u_m, f_m -> u_m */
    smooth_1(mgrid, size-1, operators);

    /* Compute the defect to check u_m, f_m -> v_m */
    compute_defect(mgrid, size-1, operators);
    defect_ant=defect;
    defect=max_of_triangle(mgrid[size-1],V,size-1);
    printf("\t[INFO] iter %d: maximum value in last function_v(u,v,w) %f, ratio=%f\n",
          i,defect, defect/defect_ant);
  }
  fclose(f);
}

void firstmultigrid(){

  printf("\t[INFO] Called first multigrid\n");
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
    defect_ant=defect;
    defect=firstmultigrid_loop(mgrid,operators,size,size-1);
    printf("\t[INFO] iter %d: maximum value in last function_v(u,v,w) %f, ratio=%f\n",
          i,defect, defect/defect_ant);
  }
}

double firstmultigrid_loop(triangle ***mgrid, _operator ** operators, int size, int level){
  int j;
  printf("\t[INFO] in level %d\n",level);
  /*smooth_1(mgrid, level, operators);
  compute_defect(mgrid,level, operators);
  restrict_one(mgrid, level);*/
  if(level==3){
    //nitialize_grid_function_u_random(mgrid[level-1],level-1);
    //initialize_boundary(mgrid[level-1],level-1,0.0,0);
      //for(j=0;j<10;j++){
      //smooth_1(mgrid,level-1,operators);
      printf("\t\t[INFO] Down level\n");
  }else{
    printf("Recall multigrid in from level %d to level %d\n",level, level-1);
    firstmultigrid_loop(mgrid, operators, size, level-1);
  }
  //interpolate_one(mgrid,level-1);
  /*correct_one(mgrid,level);
  smooth_1(mgrid,level, operators);
  if(level==size-1){
    compute_defect(mgrid,level,operators);
    return max_of_triangle(mgrid[level],V,level);
  }*/
  return 0.0;
}

