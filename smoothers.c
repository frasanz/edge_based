/*
 * =====================================================================================
 *
 *       Filename:  smoothers.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  31/01/15 16:37:29
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
#include <omp.h>
#include <cblas.h>                                                                   
#include <lapacke.h>
#include "smoothers.h"
#include "module.h"


/* This is only a test of the smoothing procedure
 */
void smooth_1(triangle *** mgrid, int level, _operator ** oper){
  int i,j,l,m;
  double temp0 = 0.0;
  double temp1 = 0.0;
  double temp2 = 0.0;
  double h2 = pow(1/pow(2,level),2);

  for(i=1;i<(int)(pow(2,level)-1);i++){ // For all files, interior points
    for(j=1;j<(int)(pow(2,level)-i-1);j++){ // For all columns
      temp0=0.0;
      temp1=0.0;
      temp2=0.0;
      for(l=0;l<3;l++){
        for(m=0;m<3;m++){
          temp0=temp0+oper[0][vu].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_u];
          if((l!=1) && (m!=1))
            temp1=temp1+oper[0][vv].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_v];
          temp2=temp2+oper[0][vw].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_w];
        }
      }
      mgrid[level][i][j].function_u[edge_v]=
        (mgrid[level][i][j].function_f[edge_v]*h2
         -(temp0+temp1+temp2))/oper[0][vv].op[1][1];
    }
  }
  for(i=1;i<(int)(pow(2,level)-1);i++){ // For all files, interior points
    for(j=1;j<(int)pow(2,level)-i-1;j++){ // For all columns
      temp0=0.0;
      temp1=0.0;
      temp2=0.0;
      for(l=0;l<3;l++){
        for(m=0;m<3;m++){
          temp0=temp0+oper[0][wu].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_u];
          temp1=temp1+oper[0][wv].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_v];
          if((l!=1) && (m!=1))
            temp2=temp2+oper[0][ww].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_w];
        }
      }
      mgrid[level][i][j].function_u[edge_w]=
        (mgrid[level][i][j].function_f[edge_w]*h2
         -(temp0+temp1+temp2))/oper[0][ww].op[1][1];
    }
  }
  for(i=1;i<(int)(pow(2,level)-1);i++){ // For all files, interior points
    for(j=1;j<(int)(pow(2,level)-i-1);j++){ // For all columns
      temp0=0.0;
      temp1=0.0;
      temp2=0.0;
      /* Smoothing edge u */
      for(l=0;l<3;l++){
        for(m=0;m<3;m++){
          if((l!=1) && (m!=1))
            temp0=temp0+oper[0][uu].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_u];
          temp1=temp1+oper[0][uv].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_v];
          temp2=temp2+oper[0][uw].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_w];
        }
      }
      mgrid[level][i][j].function_u[edge_u]=
        (mgrid[level][i][j].function_f[edge_u]*h2
          -(temp0+temp1+temp2))/oper[0][uu].op[1][1];
    }
  }
}

/* TODO: This is not parallel right now 01/04/15 */
void smooth_1_parallel(triangle *** mgrid, int level, _operator ** oper){
  int i,j,l,m;
  double temp[3];
  double h2 = pow(1/pow(2,level),2);

  /* V */

  for(i=1;i<(int)(pow(2,level)-1);i++){ // For all files, interior points
    for(j=1;j<(int)(pow(2,level)-i-1);j++){ // For all columns
      for(l=0;l<3;l++)
        temp[l]=0.0;
      for(l=0;l<3;l++){
        for(m=0;m<3;m++){
        temp[0]=temp[0]+oper[0][vu].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_u];
          if((l!=1) && (m!=1))
            temp[1]=temp[1]+oper[0][vv].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_v];
          temp[2]=temp[2]+oper[0][vw].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_w];
        }
      }
      mgrid[level][i][j].function_u[edge_v]=
        (mgrid[level][i][j].function_f[edge_v]*h2
         -(temp[0]+temp[1]+temp[2]))/oper[0][vv].op[1][1];
    }
  }

  for(i=1;i<(int)(pow(2,level)-1);i++){ // For all files, interior points
    for(j=1;j<(int)pow(2,level)-i-1;j++){ // For all columns
    for(l=0;l<3;l++)
      temp[l]=0.0;
      for(l=0;l<3;l++){
        for(m=0;m<3;m++){
          temp[0]=temp[0]+oper[0][wu].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_u];
          temp[1]=temp[1]+oper[0][wv].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_v];
          if((l!=1) && (m!=1))
            temp[2]=temp[2]+oper[0][ww].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_w];
        }
      }
      mgrid[level][i][j].function_u[edge_w]=
        (mgrid[level][i][j].function_f[edge_w]*h2
         -(temp[0]+temp[1]+temp[2]))/oper[0][ww].op[1][1];
    }
  }

  for(i=1;i<(int)(pow(2,level)-1);i++){ // For all files, interior points
    for(j=1;j<(int)(pow(2,level)-i-1);j++){ // For all columns
    for(l=0;l<3;l++)
      temp[l]=0.0;
      /* Smoothing edge u */
      for(l=0;l<3;l++){
        for(m=0;m<3;m++){
          if((l!=1) && (m!=1))
            temp[0]=temp[0]+oper[0][uu].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_u];
          temp[1]=temp[1]+oper[0][uv].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_v];
          temp[2]=temp[2]+oper[0][uw].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_w];
        }
      }
      mgrid[level][i][j].function_u[edge_u]=
        (mgrid[level][i][j].function_f[edge_u]*h2
            -(temp[0]+temp[1]+temp[2]))/oper[0][uu].op[1][1];
    }
  }
}

void smooth_gaussseidel(triangle ***mgrid, int level, _operator ** oper){
  int i,j,l,m;
  double matrix[9]; /* In fortran order, column major order */
  double B[3];
  double h2 = pow(1/pow(2,level),2);
  /* We need this to solve the matrix in fortran*/
  int N= 3; 
  int nrhs = 1; 
  int lda = 3;
  int ipiv[3];
  int ldb = 3;
  int info;  

  /* Triangles down */
  for(i=1;i<(int)(pow(2,level)-2);i++){     // For all interior triangles
    for(j=1;j<(int)(pow(2,level)-1-i);j++){ // For all interior triangles
      //printf("DOwn: %d %d\n",i,j);
      //printf("%f %f %f\n",B[0],B[1],B[2]);
      B[0]=mgrid[level][i][j].function_f[edge_u]*h2;
      B[1]=mgrid[level][i][j].function_f[edge_v]*h2;
      B[2]=mgrid[level][i][j].function_f[edge_w]*h2;
      /* We're going to build the 3x3 system for each triangle */

      for(l=0;l<3;l++){
        for(m=0;m<3;m++){
          if(l==1 && m==1){
            matrix[0+3*0]=oper[level][uu].op[l][m]*
              mgrid[level][i+1-l][j-1+m].function_u[edge_u];
            matrix[0+3*1]=oper[level][uv].op[l][m]*
              mgrid[level][i+1-l][j-1+m].function_u[edge_v];
            matrix[0+3*2]=oper[level][uw].op[l][m]*
              mgrid[level][i+1-l][j-1+m].function_u[edge_w];
            matrix[1+3*0]=oper[level][vu].op[l][m]*
              mgrid[level][i+1-l][j-1+m].function_u[edge_u];
            matrix[1+3*1]=oper[level][vv].op[l][m]*
              mgrid[level][i+1-l][j-1+m].function_u[edge_v];
            matrix[1+3*2]=oper[level][vw].op[l][m]*
              mgrid[level][i+1-l][j-1+m].function_u[edge_w];
            matrix[2+3*0]=oper[level][wu].op[l][m]*
              mgrid[level][i+1-l][j-1+m].function_u[edge_u];
            matrix[2+3*1]=oper[level][wv].op[l][m]*
              mgrid[level][i+1-l][j-1+m].function_u[edge_v];
            matrix[2+3*2]=oper[level][ww].op[l][m]*
              mgrid[level][i+1-l][j-1+m].function_u[edge_w];

          } else {
            B[0]=B[0]-
                  (oper[level][uu].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_u]+
                   oper[level][uv].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_v]+
                   oper[level][uw].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_w]);
            B[1]=B[1]-
                  (oper[level][vu].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_u]+
                   oper[level][vv].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_v]+
                   oper[level][vw].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_w]);
            B[2]=B[2]-
                  (oper[level][wu].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_u]+
                   oper[level][wv].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_v]+
                   oper[level][ww].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_w]);
          }
        }
      }
      /* System built, now, solve it */
      //printf("%d %d\n",i,j);
      //printf("A=[%f, %f, %f; %f, %f, %f; %f, %f, %f]\n",matrix[0],matrix[3],matrix[6],
      //                                            matrix[1],matrix[4],matrix[7],
      //                                            matrix[2],matrix[5],matrix[8]);
      //printf("B=[%f; %f; %f]\n",B[0],B[1],B[2]);
      N= 3; 
      nrhs = 1; 
      lda = 3;
      ldb = 3;
      dgesv_(&N, &nrhs, matrix, &lda, ipiv, B, &ldb, &info);
      //printf("%e %e %e\n",mgrid[level][i][j].function_u[edge_u],
      //                    mgrid[level][i][j].function_u[edge_v],
       //                   mgrid[level][i][j].function_u[edge_w]);
      //printf("%f %f %f\n",B[0],B[1],B[2]);
      if(info == 0){
        //mgrid[level][i][j].function_u[edge_u]=B[0];
       // mgrid[level][i][j].function_u[edge_v]=B[1];
        //mgrid[level][i][j].function_u[edge_w]=B[2];
        //printf("\t\t%f\n",max_of_triangle(mgrid[level],U,level));
      } else {
        printf("FAIL!: %d\n",info);
      }
    }
  }

  /* Triangles UP */
  for(i=1;i<(int)(pow(2,level)-3);i++){     // For all interior triangles
    for(j=1;j<(int)(pow(2,level)-2-i);j++){ // For all interior triangles
      B[0]=mgrid[level][i][j].function_f[edge_u]*h2;
      B[1]=mgrid[level][i][j].function_f[edge_v]*h2;
      B[2]=mgrid[level][i][j].function_f[edge_w]*h2;
      /* We're going to build the 3x3 system for each triangle */

      for(l=0;l<3;l++){
        for(m=0;m<3;m++){
          if(l==1 && m==1){
            matrix[0+3*0]=oper[level][uu].op[l][m]*
              mgrid[level][(i+1)+1-l][j-1+m].function_u[edge_u];
            matrix[0+3*1]=oper[level][uv].op[l][m]*
              mgrid[level][(i+1)+1-l][j-1+m].function_u[edge_v];
            matrix[0+3*2]=oper[level][uw].op[l][m]*
              mgrid[level][(i+1)+1-l][j-1+m].function_u[edge_w];
            matrix[1+3*0]=oper[level][vu].op[l][m]*
              mgrid[level][i+1-l][j-1+m].function_u[edge_u];
            matrix[1+3*1]=oper[level][vv].op[l][m]*
              mgrid[level][i+1-l][j-1+m].function_u[edge_v];
            matrix[1+3*2]=oper[level][vw].op[l][m]*
              mgrid[level][i+1-l][j-1+m].function_u[edge_w];
            matrix[2+3*0]=oper[level][wu].op[l][m]*
              mgrid[level][i+1-l][(j+1)-1+m].function_u[edge_u];
            matrix[2+3*1]=oper[level][wv].op[l][m]*
              mgrid[level][i+1-l][(j+1)-1+m].function_u[edge_v];
            matrix[2+3*2]=oper[level][ww].op[l][m]*
              mgrid[level][i+1-l][(j+1)-1+m].function_u[edge_w];

          } else {
            B[0]=B[0]-
                  (oper[level][uu].op[l][m]*mgrid[level][(i+1)+1-l][j-1+m].function_u[edge_u]+
                   oper[level][uv].op[l][m]*mgrid[level][(i+1)+1-l][j-1+m].function_u[edge_v]+
                   oper[level][uw].op[l][m]*mgrid[level][(i+1)+1-l][j-1+m].function_u[edge_w]);
            B[1]=B[1]-
                  (oper[level][vu].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_u]+
                   oper[level][vv].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_v]+
                   oper[level][vw].op[l][m]*mgrid[level][i+1-l][j-1+m].function_u[edge_w]);
            B[2]=B[2]-
                  (oper[level][wu].op[l][m]*mgrid[level][i+1-l][(j+1)-1+m].function_u[edge_u]+
                   oper[level][wv].op[l][m]*mgrid[level][i+1-l][(j+1)-1+m].function_u[edge_v]+
                   oper[level][ww].op[l][m]*mgrid[level][i+1-l][(j+1)-1+m].function_u[edge_w]);
          }
        }
      }
      /* System built, now, solve it */
      printf("A=[%e, %e, %e; %e, %e, %e; %e, %e, %e]\n",matrix[0],matrix[3],matrix[6],
                                                  matrix[1],matrix[4],matrix[7],
                                                  matrix[2],matrix[5],matrix[8]);
      printf("B=[%e, %e, %e]\n",B[0],B[1],B[2]);

      printf("%e %e %e\n",mgrid[level][i][j].function_u[edge_u],
                          mgrid[level][i][j].function_u[edge_v],
                          mgrid[level][i][j].function_u[edge_w]);
      dgesv_(&N, &nrhs, matrix, &lda, ipiv, B, &ldb, &info);
      printf("%e %e %e\n",B[0],B[1],B[2]);
      if(info == 0){
        mgrid[level][i+1][j].function_u[edge_u]=B[0];
        mgrid[level][i][j].function_u[edge_v]=B[1];
        mgrid[level][i][j+1].function_u[edge_w]=B[2];
      } else {
        printf("FAIL! %d\t",info);
      }
    }
  }

}
