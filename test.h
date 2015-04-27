/*
 * =====================================================================================
 *
 *       Filename:  test.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20/01/15 18:52:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __TEST_H_
#define __TEST_H_

void run_test();
void multigrid_two();
void firstmultigrid();
double firstmultigrid_loop(triangle ***, _operator **, int, int,int);
void firstmultigridparallel();
double firstmultigridparallel_loop(triangle ***, _operator **, int, int,int);
void test_draw();
void test_restrict();
void test_interpolate();
void test_interpolate_linear();
void test_smooth();
void test_defect();

#endif

