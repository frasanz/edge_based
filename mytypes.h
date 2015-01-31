/*
 * =====================================================================================
 *
 *       Filename:  mytypes.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/01/15 18:26:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _MYTYPES_H_
#define _MYTYPES_H_
#define U 0
#define V 1
#define F 2

#define edge_u 0 
#define edge_v 1
#define edge_w 2

#define uu 0
#define uv 1
#define uw 2
#define vu 3
#define vv 4
#define vw 5
#define wu 6
#define wv 7
#define ww 8

typedef struct {
  double function_u[3];
  double function_v[3];
  double function_f[3];
} triangle;

typedef struct {
  double op[3][3];
} _operator;

#endif
