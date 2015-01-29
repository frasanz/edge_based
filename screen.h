/*
 * =====================================================================================
 *
 *       Filename:  screen.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20/01/15 17:12:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __SCREEN_H_
#define __SCREEN_H_

#include "mytypes.h"

void print_grid(FILE *f, triangle ** , int level);
void print_multigrid(FILE *f,triangle ***, int levels);
void print_all_operators(FILE *f, _operator** op, int levels);
void print_level_operator(FILE *f, _operator* op, int level);

#endif

