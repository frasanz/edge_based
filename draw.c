/*
 * =====================================================================================
 *
 *       Filename:  draw.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  21/03/15 11:44:08
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
#include "draw.h"

#define NUM_COMMANDS 2



void draw_triangle(triangle ** tri, int level, int function, int edge){
  char * commandsForGnuplot[] = {"set title \"Test\"","splot 'data.temp' u 1:2:3\n"};
  FILE * temp = fopen("data.temp", "w");
  FILE * gnuplotPipe = popen("gnuplot -persistent", "w");
  int i,j;

  for (i=0; i < pow(2,level); i++){
    for(j=0;j<pow(2,level)-i;j++){
      fprintf(temp, "%lf %lf %lf\n", 1.0*i/pow(2,level), 1.0*j/pow(2,level),
          tri[i][j].function_u[edge]);
    }
  }
  for(i=0;i<NUM_COMMANDS; i++){
    fprintf(gnuplotPipe,"%s \n",commandsForGnuplot[i]);
  }
}

