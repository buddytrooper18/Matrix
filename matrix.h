#if !defined __matrix_h__
#define __matrix_h__ 1 
#include <stdbool.h>
#include "vector.h"
//is matrix Vector<Vector<T>>?
struct Matrix {
    VECTOR** rows;
    size_t count;
};
typedef struct Matrix MATRIX;
MATRIX* initializeMatrix(const int, const int);
void freeMatrix(MATRIX**);
bool setMatrixValue(const int, const double,  MATRIX*);
bool setMatrixValues(double*, size_t, MATRIX*);
double inputNumber();
void inputValues(MATRIX*);
void inputRow(int, VECTOR* v);
int inputNumbers();
void printMatrixRow(MATRIX*, int);
void printMatrix(MATRIX*);
#endif//__matrix_h__
