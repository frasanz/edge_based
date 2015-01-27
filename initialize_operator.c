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
#include "initialize_operator.h"

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
  operators=(_operator**)malloc(sizes*sizeof(_operator*));
  for(i=0;i<sizes;i++){
    operators[i]=(_operator*)malloc(9*sizeof(_operator));
    initialize_operator(operators[i],problem,i);
  }

}
void initialize_operator(_operator  * oper, const char * problem, int size){

  if(strcmp(problem,"-grad(div)+curl(rot)")==0){

    _operator grad_div_uu={{{   0,   0,  0 },\
                            {-2/3,-2/3,-2/3},\
                            {   0,   0,   0}}};

    _operator grad_div_uv={{{   0,   0,   0},\
                            {-2/3, 2/3,   0},\
                            {   0, 2/3,-2/3}}};

    _operator grad_div_uw={{{   0,   0,   0},\
                            {   0,-2/3,-2/3},\
                            {   0, 2/3,-2/3}}};

    _operator grad_div_vu={{{-2/3, 2/3,   0},\
                            {   0, 2/3,-2/3},\
                            {   0,   0,   0}}};

    _operator grad_div_vv={{{ 2/3,   0,   0},\
                            {   0,   0,   0},\
                            {   0,   0,   0}}};

    _operator grad_div_vw={{{   0, 2/3,   0},\
                            {   0,-4/3,   0},\
                            {   0,   0, 2/3}}};

    _operator grad_div_wu={{{-2/3, 2/3,   0},\
                            { 2/3,-2/3,   0},\
                            {   0,   0,   0}}};


    _operator grad_div_wv={{{ 2/3,   0,   0},\
                            {-2/3,-2/3,   0},\
                            {   0, 2/3,   0}}};

    _operator grad_div_ww={{{   0, 2/3,   0},\
                            {   0,-4/3,   0},\
                            {   0, 2/3,   0}}};

    _operator rot_rot_uu={{{ 0, 0, 0},\
                           { 0, 8, 0},\
                           { 0, 0, 0}}};

    _operator rot_rot_uv={{{ 0, 0, 0},\
                           { 0, 4, 0},\
                           { 4, 0, 0}}};

    _operator rot_rot_uw={{{ 0, 0, 0},\
                           { 0,-4, 0},\
                           { 0, 0,-4}}};

    _operator rot_rot_vu={{{ 0,-4, 0},\
                           { 0,-4, 0},\
                           { 0, 0, 0}}};

    _operator rot_rot_vv={{{ 0, 0, 0},\
                           { 0, 8, 0},\
                           { 0, 0, 0}}};

    _operator rot_rot_vw={{{ 0, 0, 0},\
                           { 0, 4, 4},\
                           { 0, 0, 0}}};

    _operator rot_rot_wu={{{-4, 0, 0},\
                           { 0,-4, 0},\
                           { 0, 0, 0}}};

    _operator rot_rot_wv={{{ 0, 0, 0},\
                           { 4, 4, 0},\
                           { 0, 0, 0}}};

    _operator rot_rot_ww={{{ 0, 0, 0},\
                           { 0, 8, 0},\
                           { 0, 0, 0}}};
  }
}
