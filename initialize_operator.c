/*
 * =====================================================================================
 *
 *       Filename:  initialize_operator.c
 *
 *    Description:  :
 *
 *        Version:  1.0
 *        Created:  27/01/15 18:19:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "initialize_operator.h"

_operator ** allocate_operators(const char * problem, int size){
  int i;
  _operator ** operators;
  if(strcmp(problem,"-grad(div)+curl(rot)")==0){
    operators=(_operator**)malloc(size*sizeof(_operator*));
    for(i=0;i<size;i++){
      operators[i]=(_operator*)malloc(9*sizeof(_operator));
    }
  }
  return operators;
}

void initialize_operators(_operator ** operators, 
  const char * problem, 
  int sizes){
  int i;

  /* We're going to malloc and initialize each level of operators */
  /* INFO operator[i][j]
   * i-> level
   * j 0->uu
   *   1->uv
   *   2->uw
   *   3->wu
   *   ....
   *   */
  for(i=0;i<sizes;i++){
    initialize_operator(operators[i],problem,i);
  }
}
void initialize_operator(_operator  * oper, const char * problem, int size){

  int i,j;
  double inv_l2=1/(pow(2,size));

  if(strcmp(problem,"-grad(div)+curl(rot)")==0){

    _operator grad_div_uu={{{       0,       0,       0},\
                            { 2.0/3.0,-4.0/3.0, 2.0/3.0},\
                            {       0,       0,       0}}};

    _operator grad_div_uv={{{       0,       0,       0},\
                            {-2.0/3.0, 2.0/3.0,       0},\
                            {       0, 2.0/3.0,-2.0/3.0}}};

    _operator grad_div_uw={{{       0,       0,       0},\
                            {       0,-2.0/3.0, 2.0/3.0},\
                            {       0, 2.0/3.0,-2.0/3.0}}};

    _operator grad_div_vu={{{-2.0/3.0, 2.0/3.0,       0},\
                            {       0, 2.0/3.0,-2.0/3.0},\
                            {       0,       0,       0}}};

    _operator grad_div_vv={{{ 2.0/3.0,       0,       0},\
                            {       0,-4.0/3.0,       0},\
                            {       0,       0, 2.0/3.0}}};

    _operator grad_div_vw={{{       0, 2.0/3.0,       0},\
                            {       0,-2.0/3.0,-2.0/3.0},\
                            {       0,       0, 2.0/3.0}}};

    _operator grad_div_wu={{{-2.0/3.0, 2.0/3.0,       0},\
                            { 2.0/3.0,-2.0/3.0,       0},\
                            {       0,       0,       0}}};


    _operator grad_div_wv={{{ 2.0/3.0,       0,       0},\
                            {-2.0/3.0,-2.0/3.0,       0},\
                            {       0, 2.0/3.0,       0}}};

    _operator grad_div_ww={{{       0, 2.0/3.0,       0},\
                            {       0,-4.0/3.0,       0},\
                            {       0, 2.0/3.0,       0}}};

    _operator rot_rot_uu={{{   0,   0,   0},\
                           {   0, 8.0,   0},\
                           {   0,   0,   0}}};

    _operator rot_rot_uv={{{   0,   0,   0},\
                           {   0, 4.0,   0},\
                           {   0, 4.0,   0}}};

    _operator rot_rot_uw={{{   0,   0,   0},\
                           {   0,-4.0,   0},\
                           {   0,   0,-4.0}}};

    _operator rot_rot_vu={{{   0,-4.0,   0},\
                           {   0,-4.0,   0},\
                           {   0,   0,   0}}};

    _operator rot_rot_vv={{{   0,   0,   0},\
                           {   0, 8.0,   0},\
                           {   0,   0,   0}}};

    _operator rot_rot_vw={{{   0,   0,   0},\
                           {   0,   4,   4},\
                           {   0,   0,   0}}};

    _operator rot_rot_wu={{{-4.0,   0,   0},\
                           {   0,-4.0,   0},\
                           {   0,   0,   0}}};

    _operator rot_rot_wv={{{   0,   0,   0},\
                           { 4.0, 4.0,   0},\
                           {   0,   0,   0}}};

    _operator rot_rot_ww={{{   0,   0,   0},\
                           {   0, 8.0,   0},\
                           {   0,   0,   0}}};
    for(i=0;i<3;i++){
      for(j=0;j<3;j++){
        oper[uu].op[i][j]=inv_l2*(-grad_div_uu.op[i][j]+rot_rot_uu.op[i][j]);
        oper[uv].op[i][j]=inv_l2*(-grad_div_uv.op[i][j]+rot_rot_uv.op[i][j]);
        oper[uw].op[i][j]=inv_l2*(-grad_div_uw.op[i][j]+rot_rot_uw.op[i][j]);
        oper[vu].op[i][j]=inv_l2*(-grad_div_vu.op[i][j]+rot_rot_vu.op[i][j]);
        oper[vv].op[i][j]=inv_l2*(-grad_div_vv.op[i][j]+rot_rot_vv.op[i][j]);
        oper[vw].op[i][j]=inv_l2*(-grad_div_vw.op[i][j]+rot_rot_vw.op[i][j]);
        oper[wu].op[i][j]=inv_l2*(-grad_div_wu.op[i][j]+rot_rot_wu.op[i][j]);
        oper[wv].op[i][j]=inv_l2*(-grad_div_wv.op[i][j]+rot_rot_wv.op[i][j]);
        oper[ww].op[i][j]=inv_l2*(-grad_div_ww.op[i][j]+rot_rot_ww.op[i][j]);
      }
    }
  }
}
