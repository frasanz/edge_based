/*
 * =====================================================================================
 *
 *       Filename:  prueba.c
 *
 *    Description:  :c
 *
 *        Version:  1.0
 *        Created:  15/03/15 19:53:42
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

#define NUM_POINTS 5
#define NUM_COMMANDS 2

int main(){
  char * commandsForGnuplot[] = {"set title \"Test\"","plot '-' \n"};
  double xvals[NUM_POINTS] = {1.0, 2.0, 3.0, 4.0, 5.0};
  double yvals[NUM_POINTS] = {5.0, 3.0, 1.0, 3.0, 5.0};

  FILE * temp = fopen("data.temp", "w");

  FILE * gnuplotPipe = popen("gnuplot -persistent", "w");
  int i;
  for(i=0;i<NUM_COMMANDS; i++){
      fprintf(gnuplotPipe,"%s \n",commandsForGnuplot[i]);
  }

  for(i=0;i<NUM_POINTS; i++){
    fprintf(gnuplotPipe, "%lf %lf\n", xvals[i], yvals[i]);
  }
  fprintf(gnuplotPipe, "e");
  return 0;
}

