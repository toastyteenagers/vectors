#include <stdlib.h>
#include <math.h>
#define arrLen(arr) (int)(sizeof(arr)/(sizeof(double)))

typedef struct vec32 {
    float_t **contents;
    int rows;
    int cols;
} vec32;

double** init2dArr(size_t rows, size_t cols) {
    if (rows <= 0 || cols <= 0) {
        printf("Rows and Cols must be positive numbers");
        exit(1);
    }
    double **retArr = (double **)(malloc(sizeof(double *) * cols));
    // init cols
    for (int k = 0; k < cols; k++) {
        retArr[k] = (double *)(malloc(rows * sizeof(double)));
    }
    // set values to 0
    for (int i = 0; i < cols; i++) {
        double *row = retArr[i];
        for (int j = 0; j < rows; j++) {
            row[j] = 0;
        }
    }
    return retArr;
}

vec32* initVec(double **data, size_t rows, size_t cols) {
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
    double** contents = init2dArr(dimension,dimension);
    // set values on diagonals
    for (int i = 0; i<dimension; i++) {
        double* row = contents[i];
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
            printf("%f ",vec->contents[i][j]);
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

void scalarMultiply(vec32* vec, double scalar) {
    for (int i =0; i< vec->rows; i++) {
        for (int j = 0; vec->cols; j++) {
            vec->contents[i][j] *= scalar;
        }
    }
}

double dotProduct(vec32* vec1, vec32* vec2) {
    if (vec1->cols != vec2->cols || vec1->rows != vec2->rows) {
        fprintf(stderr,"Incompatible vectors\n");
        exit(1);
    }

    double product = 0;
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

    vec32* vec1Copy = copyVec(vec1);
    
    double vec1DotVec2 = dotProduct(vec1,vec2);
    double vec1Squared  = magnitude(vec1);
    vec1Squared = vec1Squared*vec1Squared;
    double projectionScalar = vec1DotVec2/vec1Squared;
    scalarMultiply(vec1Copy, projectionScalar);
    return vec1Copy;
}

static double detHelper(vec32* vec, vec32* copy, int n) {
    double det = 0;
    int32_t alternatingSign = 1;
    
    if (n ==2) {
        return vec->contents[0][0]*vec->contents[1][1] - vec->contents[0][1]*vec->contents[1][0];
    } else {
        for (int i = 0; i < n; i++) {
            int c1,c2;
            c1 = c2 = 0;
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (j != 0 && k != i) {
                        copy->contents[c1][c2] = vec->contents[j][k];
                        c2++;
                        if (c2 > n-2) {
                            c1++;  
                            c2=0;
                        }
                    }
                }
            }
            det += alternatingSign * (vec->contents[0][i]*detHelper(vec,copy,n-1));
            alternatingSign *= -1;
        }
    }
    return det;
}

double det(vec32* vec) {
    if (vec->cols != vec->rows) {
        fprintf(stderr,"Incompatible vectors\n");
        exit(1);
    } 
    if (vec->cols > 15) {
        fprintf(stderr,"Not advised to use det on large vectors, attempting anyway. \n");
    }
    vec32* copy = copyVec(vec);
    double result = detHelper(vec,copy,vec->rows);
    free(copy);
    return result;
}

vec32* crossProduct3d(vec32* vec1, vec32* vec2) {
    if (vec1->cols != 1 && vec2->cols != 1 && vec1->rows != 3 && vec2->cols != 3) {
        fprintf(stderr,"Incompatible vectors\n");
        exit(1);
    }
    vec32* retVec = initEmptyVec(3,1);
    
    //x  component
    retVec->contents[0][0] = vec1->contents[0][1]*vec2->contents[0][2] - vec1->contents[0][2]*vec2->contents[0][1];
    //y component
    retVec->contents[0][1] = (-1)*(vec1->contents[0][0]*vec2->contents[0][2] - vec1->contents[0][2]*vec2->contents[0][0]);
    //z component
    retVec->contents[0][2] = vec1->contents[0][0]*vec2->contents[0][1] - vec1->contents[0][1]*vec2->contents[0][0];

    return retVec;
}   
