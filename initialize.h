/*
 * =====================================================================================
 *
 *       Filename:  initialize.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  19/01/15 18:33:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __INITIALIZE_H_
#define __INITIALIZE_H_

#include "mytypes.h"
void initialize_grid(triangle ** triangle, int level,int value);
void initialize_multigrid(triangle *** triangle, int levels, int value);
void initialize_multigrid_levels(triangle *** triangle, int levels);
void initialize_grid_files(triangle ** grid, int level);
void initialize_multigrid_files(triangle *** mgrid, int level);
void initialize_grid_columns(triangle ** grid, int level);
void initialize_multigrid_columns(triangle *** mgrid, int level);
void initialize_grid_random(triangle **grid, int level);
void initialize_grid_function_u_random(triangle **grid, int level);
void initialize_grid_function_v_random(triangle **grid, int level);
void initialize_grid_function_u_random2(triangle **grid, int level);
void initialize_grid_function_v_random2(triangle **grid, int level);
void initialize_multigrid_random(triangle ***grid, int levels);
void initialize_boundary(triangle **grid, int level, double value, int element); 
void initialize_bigboundary(triangle **grid, int level, double value, int element); 
void initialize_grid_function_value(triangle **grid, int level, double value,int element);
#endif

