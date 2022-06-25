#include <stdlib.h>
#include <math.h>
#define arrLen(arr) (int)(sizeof(arr)/(sizeof(int32_t)))

typedef struct vec32 {
    int32_t **contents;
    int rows;
    int cols;
} vec32;

int32_t **build2dArr(size_t rows, size_t cols) {
    if (rows <= 0 || cols <= 0) {
        printf("Rows and Cols must be positive numbers");
        exit(1);
    }
    int32_t **retArr = (int32_t **)(malloc(sizeof(int32_t *) * cols));
    // init cols
    for (int k = 0; k < cols; k++) {
        retArr[k] = (int32_t *)(malloc(rows * sizeof(int32_t)));
    }
    // set values to 0
    for (int i = 0; i < cols; i++) {
        int32_t *row = retArr[i];
        for (int j = 0; j < rows; j++) {
            row[j] = 0;
        }
    }
    return retArr;
}

vec32* initVec(int32_t **data, size_t rows, size_t cols) {
    vec32 *retVec = (vec32*)(malloc(sizeof(vec32)));
    retVec->contents = data;
    retVec->rows = (int)rows;
    retVec->cols = (int)cols;
    return retVec;
}

vec32* initIdentity (size_t dimension) {
    vec32* retVec = (vec32*)(malloc(sizeof(vec32)));
    int32_t** contents = build2dArr(dimension,dimension);
    // set values on diagonals
    for (int i = 0; i<dimension; i++) {
        int32_t* row = contents[i];
        for (int j = 0; j<dimension; j++) {
            row[j] = (j == i) ? 1 : 0;
        }
    }
    //populate fields
    retVec->contents = contents;
    retVec->rows = dimension;
    retVec->cols = dimension;
    return retVec;
}

void printVec(vec32* vec) {
    for (int i = 0; i<vec->cols; i++) {
        for (int j = 0; j<vec->rows; j++) {
            printf("%d ",vec->contents[i][j]);
        }
        printf("\n");
    }
}

int32_t dotProduct(vec32* v1, vec32* v2) {
    int product = 0;
    // must have identical dimensions.
    if (v1->cols != v2->cols || v1->rows != v2->rows) {
        fprintf(stderr,"Incompatible vectors\n");
        exit(1);
    }

    for (int i = 0; i<v1->cols; i++ ) {
        for (int j = 0; j<v1->rows; j++) {
            product += (v1->contents[i][j] * v1->contents[i][j]);
        }
    }

    return product;
}

int32_t magnitude(vec32* vec) {
    if (vec->rows > 1) {
        fprintf(stderr,"Incompatible vector\n");
        exit(1);
    }

    int product = 0;
    for (int i = 0; i< vec->cols; i++) {
        product += (vec->contents[0][i] * vec->contents[0][i]);
    }
    return sqrt(((double) product));
}