/*
 * =====================================================================================
 *
 *       Filename:  initialize_operator.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  24/01/15 16:37:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _INITIALIZE_OPERATOR_H_
#define _INITIALIZE_OPERATOR_H_

#include "operators.h"

void initialize_operators(_operator ** operators, const char * problem, int sizes);
void initialize_operator(_operator * oper, const char * problem, int size);

#endif

