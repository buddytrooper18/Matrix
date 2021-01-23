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
    freeMatrix(&m);
    return 0;
    

}

