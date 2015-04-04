/*
 * =====================================================================================
 *
 *       Filename:  initialize.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  19/01/15 18:43:06
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
#include <time.h>
#include "initialize.h"
#include "math.h"

/* Here, we can initialize all functions in one triangle */
void initialize_grid(triangle **grid, int level, int value){
  int i,j;
  for(i=0; i<pow(2,level); i++){
    for(j=0; j<pow(2,level)-i;j++){
      grid[i][j].function_u[edge_u]=1.0*value;
      grid[i][j].function_u[edge_v]=1.0*value;
      grid[i][j].function_u[edge_w]=1.0*value;

      grid[i][j].function_v[edge_u]=1.0*value;
      grid[i][j].function_v[edge_v]=1.0*value;
      grid[i][j].function_v[edge_w]=1.0*value;

      grid[i][j].function_f[edge_u]=1.0*value;
      grid[i][j].function_f[edge_v]=1.0*value;
      grid[i][j].function_f[edge_w]=1.0*value;
    }
  }
}

void initialize_multigrid(triangle *** mgrid, int levels, int value){
  int i;
  for(i=0;i<levels;i++)
    initialize_grid(mgrid[i],i,value);
}
void initialize_multigrid_levels(triangle *** mgrid, int levels){
  int i;
  for(i=0;i<levels;i++)
    initialize_grid(mgrid[i],i,i);
}


/* some initialization tools */
void initialize_grid_files(triangle **grid, int level){
  int i,j;
  for(i=0; i<pow(2,level);i++){
    for(j=0; j<pow(2,level)-i; j++){
      grid[i][j].function_u[edge_u]=1.0*i;
      grid[i][j].function_u[edge_v]=1.0*i;
      grid[i][j].function_u[edge_w]=1.0*i;

      grid[i][j].function_v[edge_u]=1.0*i;
      grid[i][j].function_v[edge_v]=1.0*i;
      grid[i][j].function_v[edge_w]=1.0*i;

      grid[i][j].function_f[edge_u]=1.0*i;
      grid[i][j].function_f[edge_v]=1.0*i;
      grid[i][j].function_f[edge_w]=1.0*i;

    }
  }
}

void initialize_multigrid_files(triangle *** mgrid, int levels){
  int i;
  for(i=0; i<levels;i++)
    initialize_grid_files(mgrid[i], i);
}

void initialize_grid_columns(triangle **grid, int level){
  int i,j;
  for(i=0; i<pow(2,level);i++){
    for(j=0; j<pow(2,level)-i; j++){
      grid[i][j].function_u[edge_u]=1.0*j;
      grid[i][j].function_u[edge_v]=1.0*j;
      grid[i][j].function_u[edge_w]=1.0*j;

      grid[i][j].function_v[edge_u]=1.0*j;
      grid[i][j].function_v[edge_v]=1.0*j;
      grid[i][j].function_v[edge_w]=1.0*j;

      grid[i][j].function_f[edge_u]=1.0*j;
      grid[i][j].function_f[edge_v]=1.0*j;
      grid[i][j].function_f[edge_w]=1.0*j;
    }
  }
}

void initialize_multigrid_columns(triangle *** mgrid, int levels){
  int i;
  for(i=0; i<levels;i++)
    initialize_grid_columns(mgrid[i], i);
}

void initialize_grid_random(triangle **grid, int level){
  int i,j,k;
  // generate different seed for random number                                     
  for(i=0; i<pow(2,level);i++){
    for(j=0;j<pow(2,level)-i;j++){
      for(k=0;k<3;k++){
        grid[i][j].function_u[k]= rand();
        grid[i][j].function_v[k]= rand();
        grid[i][j].function_f[k]= rand();
      }
    }
  }
}
void initialize_grid_function_u_random(triangle **grid, int level){
  int i,j,k;
  // generate different seed for random number                                     
  for(i=0; i<pow(2,level);i++){
    for(j=0;j<pow(2,level)-i;j++){
      for(k=0;k<3;k++){
        grid[i][j].function_u[k]= rand();
      }
    }
  }
}
void initialize_grid_function_u_random2(triangle **grid, int level){
  int i,j,k;
  // generate different seed for random number                                     
  for(i=0; i<pow(2,level);i++){
    for(j=0;j<pow(2,level)-i;j++){
      for(k=0;k<3;k++){
        grid[i][j].function_u[k]= sin(i+10*j+100+k);
      }
    }
  }
}





/* Note, we're initializing boundary only in function_u */
void initialize_boundary(triangle **grid, int level, double value,int element){
  int i,j;
  int max=(int)(pow(2,level));
  for(i=0;i<max;i++){
    for(j=0;j<3;j++){
      if(element==U){
        grid[i][0].function_u[j]=value;
        grid[0][i].function_u[j]=value;
        grid[i][max-i-1].function_u[j]=value;
      } else if(element==V){
        grid[i][0].function_v[j]=value;
        grid[0][i].function_v[j]=value;
        grid[i][max-i-1].function_v[j]=value;
      } else {
        grid[i][0].function_f[j]=value;
        grid[0][i].function_f[j]=value;
        grid[i][max-i-1].function_f[j]=value;
      }
    }
  }
}
/* Note, we're initializing boundary only in function_u */
void initialize_bigboundary(triangle **grid, int level, double value,int element){
  int i,j;
  int max=(int)(pow(2,level));
  for(i=0;i<max;i++){
    for(j=0;j<3;j++){
      if(element==U){
        grid[i][0].function_u[j]=value;
        grid[0][i].function_u[j]=value;
        grid[i][max-i-1].function_u[j]=value;
      } else if(element==V){
        grid[i][0].function_v[j]=value;
        grid[0][i].function_v[j]=value;
        grid[i][max-i-1].function_v[j]=value;
      } else {
        grid[i][0].function_f[j]=value;
        grid[0][i].function_f[j]=value;
        grid[i][max-i-1].function_f[j]=value;
      }
    }
  }
  for(i=1;i<max-1;i++){
    if(element==U){
      printf("Here\n");
      grid[1][i].function_u[0]=value;
      grid[i][1].function_u[2]=value;
      grid[i][max-i-2].function_u[1]=value;
    }
  }
}

void initialize_multigrid_random(triangle *** mgrid, int levels){
  int i=0;
  time_t t;                                                                        
  srand((unsigned) time(&t));                                                      
  for(i=0;i<levels;i++)
    initialize_grid_random(mgrid[i],i);
}
void initialize_grid_function_value(triangle **grid, 
    int level,double value, int element){
  int i,j,k;
  // generate different seed for random number                                     
  for(i=0; i<pow(2,level);i++){
    for(j=0;j<pow(2,level)-i;j++){
      for(k=0;k<3;k++){
        if(element==U)
          grid[i][j].function_u[k]=value;
        else if(element==V){
          grid[i][j].function_v[k]=value;
        } else {
          grid[i][j].function_f[k]=value;
        }
      }
    }
  }
}
