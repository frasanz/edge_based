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



void draw_triangle(triangle ** tri, int level, int function, int edge,char * title){
  char  filename[256];
  char  command1[256];
  char  command2[256];
  int i,j;
  sprintf(filename,"%s.%s",title,"temp");
  sprintf(command1,"%s \"%s\""," set term wxt; set pm3d; set ticslevel 0; set title",title);
  sprintf(command2,"%s '%s' u 1:2:3\n","splot",filename);
  char * commandsForGnuplot[] = {command1, command2};
  FILE * temp = fopen(filename, "w");
  FILE * gnuplotPipe = popen("gnuplot -persistent", "w");

  for (i=0; i < pow(2,level); i++){
    for(j=0;j<pow(2,level)-i;j++){
      if(function==U){
        fprintf(temp, "%lf %lf %lf\n", 1.0*i/pow(2,level), 1.0*j/pow(2,level),
            tri[i][j].function_u[edge]);
      } else if(function==V){
        fprintf(temp, "%lf %lf %lf\n", 1.0*i/pow(2,level), 1.0*j/pow(2,level),
            tri[i][j].function_v[edge]);
      } else if(function==F){
        fprintf(temp, "%lf %lf %lf\n", 1.0*i/pow(2,level), 1.0*j/pow(2,level),
            tri[i][j].function_f[edge]);
      }
    }
    fprintf(temp,"\n");
  }
  for(i=0;i<NUM_COMMANDS; i++){
    fprintf(gnuplotPipe,"%s \n",commandsForGnuplot[i]);
  }
  fclose(temp);
}

