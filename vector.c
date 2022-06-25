#include <stdio.h>
#include <stdint.h>
#ifndef _VECTOR_H
#define _VECTOR_H
#include "vector.h"
#endif

int main (void) {
    int32_t **vec1Contents = build2dArr(1,2);
    vec1Contents[0][0] = 3;
    vec1Contents[0][1] = 4;
    vec32 *vec1 = initVec(vec1Contents,1,2);
    printf("%d\n",magnitude(vec1));
}