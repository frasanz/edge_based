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




void run_test(){

  /* We're going to build a 10 levels multigrid
   * to run some tests */
  int size=10;
  int i,j,k,l;
  int triangles_alloc=0;
  const char * testoutput="test.out";
  const char * testoutput2="smooth.out";
  const char * testrestrictoutput="restrict.out";
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
  for(j=0;j<1;j++){
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
  restrict_one(mgrid,size-2);
  f = fopen (testrestrictoutput,"w");
  if (f==NULL) {
    printf("\t[TEST#9] Error opening file %s\n",testrestrictoutput);
    exit(EXIT_FAILURE);
  } else {
    print_grid_u(f,mgrid[size-1],size-1);
    print_grid_u(f,mgrid[size-2],size-2);
    fclose(f);
  }
  printf("\t[TEST#10] Ended\n\n");
  free_multigrid(mgrid,size);
}
