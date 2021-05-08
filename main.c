#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "matrix.h"
#define EPSILON 0.00000000000000000001

/* We will examine the vector, matrix, and table structures using vanilla C 
doing this will help learning the following concepts: 
1) memory management
2) input, output
3) vector, matrix, and table operations
*/

//typedef Vector<double> VECTORD;

//is matrix Vector<Vector<T>>?
typedef enum operation {
  EX = -1, TPOSE, SCALMULT, SCALDIV, DET, INV
} OPERATION;
int operationAsk() {
  char input = '\0';
  printf("enter operation: \nt - transpose\nx - scalar multiplication\n/ - scalar division\nd - determinant\ni - inverse\ne - exit\n");
  if (scanf("%c", &input) > 0) {
    switch(input) {
      case't':
        return TPOSE;
      case'x':
        return SCALMULT;
      case'/':
        return SCALDIV;
      case'd':
        return DET;
      case'i':
        return INV;
      case'e':
        return EX;
        break;
    }
  }
  return EX;
}

double inputFactor(const char*);

bool doOperation(OPERATION code, MATRIX* m, MATRIX** result) {
  double factor;
  switch(code) {
    case TPOSE:
        return doTranspose(m, result);
    case SCALMULT:
        return doScalarMultiplication(m, inputFactor("multiplier"), result);
    case SCALDIV:
        factor = inputFactor("divisor");
        return fabs(factor) >= EPSILON && doScalarMultiplication(m, 1.0/factor, result);
    case DET:
        return doDeterminant(m, result);
    case INV:
        return doInverse(m, result);
    default: 
      break;
    
  }
  return false;
}

MATRIX* createSetupMatrix(int count, const char** values) {
  if(count > 1 && values != NULL) {
    int rows, columns;
    sscanf(values[1], "%d", &rows);
    if(count > 2) {
      sscanf(values[2], "%d", &columns);
      return initializeMatrix(columns, rows); 
    }
    return initializeMatrix(columns, columns);  
  } 
  return NULL;
}

int main(int argc, char const *argv[]) {
    /*double matrixValues[] = {1.0, 1.5, 2.0, 35.0};
    MATRIX* matrix = initializeMatrix(2, 2);
    setMatrixValues(matrixValues, sizeof(matrixValues) / sizeof(double), matrix);
    logVector(matrix->rows[1]);


    freeMatrix(&matrix);*/
    printf("argc = %d\n", argc);
    for(int i = 0; i < argc; i++)
      printf("%s\n", argv[i]);
    MATRIX* m = createSetupMatrix(argc, argv);
    inputValues(m);
    printf("matrixInput _ _ _ _ _ _ _\n");
    printMatrix(m);
    int code;
    MATRIX* result = NULL;
    while((code = operationAsk())!= EX) {
      doOperation(code, m, &result);
    }
    //operation(code);
    freeMatrix(&m);
    freeMatrix(&result);
    return 0;
    

}

