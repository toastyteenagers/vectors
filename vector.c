#include <stdio.h>
#include <stdint.h>
#ifndef _VECTOR_H
#define _VECTOR_H
#include "vector.h"
#endif

int main (void) {
   vec32 *id1 = initIdentity(5);
   double **a2 = init2dArr(5,5);
   a2[1][1] = 5;
   vec32 *vec2 = initVec(a2,5,5);
   printVec(multiply(id1,vec2));
}