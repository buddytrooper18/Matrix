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
#define BUFFERSIZE 16
typedef enum operation {
  ex = -1, tpose, scalmult, scaldiv, det, inv
} OPERATION;
int operationAsk() {
  char buffer[BUFFERSIZE] = {'\0'};
  printf("enter operation: \nt = transpose\nx = scalar multiplication\n/ = scalar division\nd = determinant\ni = inverse\ne = exit\n");
  if (scanf("%c", buffer) > 0) {
    switch(buffer[0]) {
      case't':
        return tpose;
      case'x':
        return scalmult;
      case'/':
        return scaldiv;
      case'd':
        return det;
      case'i':
        return inv;
      case'e':
        return ex;
      default: 
        break;
    }
  }
  return ex;
}

bool doOperation(OPERATION code, MATRIX* m, MATRIX** result) {
  switch(code) {
    case tpose:
        return doTranspose(m, result);
    case scalmult:
        return scalmult;
    case scaldiv:
        return scaldiv;
    case det:
        return det;
    case inv:
        return inv;
  }
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

