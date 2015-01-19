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

#endif

