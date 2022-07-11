#include <stdio.h>
#include <stdint.h>
#ifndef _VECTOR_H
#define _VECTOR_H
#include "vector.h"
#endif

int main (void) {
   vec32* vec = initIdentity(5);
   printf("%f\n",det(vec));
   free(vec);
}