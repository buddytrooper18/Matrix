#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matrix.h"

//hw: work on inputNumbers and use strtok()

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
  printf("enter operation: \nt = transpose\nx = scalar multiplication\n/ = scalar division\nd = determinant\ni = inverse\ne = exit\n");
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

bool doTranspose(MATRIX* m, MATRIX** result) {
  
  return false;
}

bool scalarMultiplication(MATRIX* m, MATRIX** result) {
  
  return false;
}

bool scalarDivision(MATRIX* m, MATRIX** result) {
  
  return false;
}

bool determinant(MATRIX* m, MATRIX** result) {
  
  return false;
}

bool inverse(MATRIX* m, MATRIX** result) {
  
  return false;
}

bool doOperation(OPERATION code, MATRIX* m, MATRIX** result) {
  switch(code) {
    case TPOSE:
        return doTranspose(m, result);
    case SCALMULT:
        return scalmult;
    case SCALDIV:
        return scaldiv;
    case DET:
        return det;
    case INV:
        return inv;
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
    while((code = operationAsk())!= ex) {
      doOperation(code, m, result);
    }
    operation(code);
    freeMatrix(&m);
    return 0;
    

}

