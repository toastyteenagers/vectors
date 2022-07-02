#include <stdlib.h>
#include <math.h>
#define arrLen(arr) (int)(sizeof(arr)/(sizeof(int32_t)))
//TODO: NEED TO CONVERT FROM INT32_T TO DOUBLE.
typedef struct vec32 {
    int32_t **contents;
    int rows;
    int cols;
} vec32;

int32_t** init2dArr(size_t rows, size_t cols) {
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

vec32* initEmptyVec(size_t rows, size_t cols) {
    vec32 *retVec = (vec32*)(malloc(sizeof(vec32)));
    retVec->contents = init2dArr(rows,cols);
    retVec->rows = (int)rows;
    retVec->cols = (int)cols;
    return retVec;
}

vec32* copyVec(vec32* in) {
    return initVec(in->contents, in->rows, in->cols);
}

vec32* initIdentity (size_t dimension) {
    vec32* retVec = (vec32*)(malloc(sizeof(vec32)));
    int32_t** contents = init2dArr(dimension,dimension);
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

double magnitude(vec32* vec) {
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

void scalarMultiply(vec32* vec, int32_t scalar) {
    for (int i =0; i< vec->rows; i++) {
        for (int j = 0; vec->cols; j++) {
            vec->contents[i][j] *= scalar;
        }
    }
}

int32_t dotProduct(vec32* vec1, vec32* vec2) {
    if (vec1->cols != vec2->cols || vec1->rows != vec2->rows) {
        fprintf(stderr,"Incompatible vectors\n");
        exit(1);
    }

    int32_t product = 0;
    for (int i = 0; i<vec1->cols; i++) {
        for (int j = 0; j<vec1->rows; j++) {
            product += (vec1->contents[i][j]) * (vec2->contents[i][j]);
        }
    }
    return product;
}

vec32* transpose(vec32* inputVector) {
    vec32* returnVector = initEmptyVec(inputVector->cols, inputVector->rows);

     for (int i = 0; i<inputVector->cols; i++) {
        for (int j = 0; j<inputVector->rows; j++) {
            returnVector->contents[j][i] = inputVector->contents[i][j];
        }
    }
    return returnVector;
}

vec32* multiply(vec32* vec1, vec32* vec2) {
    if (vec1->rows != vec2->cols) {
        fprintf(stderr,"Incompatible vectors\n");
        exit(1);
    }

    vec32* returnVector = initEmptyVec(vec1->cols, vec2->rows);
    for (int i = 0; i < vec1->cols; i++) {
        for (int j = 0; j < vec2->cols; j++) {
            for (int k = 0; k < vec1->rows; k++) {
                returnVector->contents[i][j] = returnVector->contents[i][j] + (vec1->contents[i][k] * vec2->contents[k][j]);
            }
        }
    }
    return returnVector;
}

vec32* normalize(vec32* vec) {
    vec32* returnVector = copyVec(vec);
    double mag = magnitude(vec);
    for (int i = 0; i < returnVector->rows; i++) {
        for (int j = 0; j < returnVector->cols; j++) {
            returnVector->contents[i][j] =  returnVector->contents[i][j]/mag;
        }
    }
    
    return returnVector;
}


vec32* vectorProject(vec32* vec1, vec32* vec2) {
    if ((vec1->cols > 1 || vec2->cols > 1) || (vec1->rows != vec2->rows)) {
        fprintf(stderr,"Incompatible vectors\n");
        exit(1);
    }

    vec32* vec1Copy = copy(vec1);
    
    int32_t vec1DotVec2 = dotProduct(vec1,vec2);
    double vec1Squared  = magnitude(vec1);
    vec1Squared = vec1Squared*vec1Squared;
    int32_t projectionScalar = vec1DotVec2/vec1Squared;
    scalarMultiply(vec1Copy, projectionScalar);

    return vec1Copy;
}
//cross product
//determinant 