#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "matrix.h"

static const char* skipSpaces(const char*);
size_t rowTableSize(const size_t count) {
  return sizeof(VECTOR*) * count;
}

size_t matrixMemorySize(const int rowSize, const int count) {
  return sizeof(MATRIX) + vectorMemorySize(rowSize) * count + rowTableSize(count); 
}

void setupRows(const size_t rowSize, MATRIX* result) {
  void* p = (void*)result + rowTableSize(result->count);
  for(int i = 0; i < result->count; i++){
    result->rows[i] = (VECTOR*)p;
    setupVectorItemsSize(rowSize, result->rows[i]);
    p += vectorMemorySize(rowSize);
  }
}

MATRIX* initializeMatrix(const int rowSize, const int count) {
  if( rowSize > 0 && count > 0) {
    MATRIX* result = (MATRIX*)malloc(matrixMemorySize(rowSize, count));
    if(result != NULL) {
      result->count = count;
      result->rows = (VECTOR**)(result + sizeof(MATRIX));
      setupRows(rowSize, result);
    }
    return result;
  }
  return NULL;
}

void checkThenFree(void** a) {
    if(a != NULL && *a != NULL) {
        free(*a);
    }
}

void freeMatrix(MATRIX** m) {
  if(m != NULL && *m != NULL){
    free(*m);
    *m = NULL;
  }
}

// void initializeMatrix()
double inputNumber(const char* number) { //dostnwork
  double result = 0.0;
  int n = 0;
  if (number != NULL && *number != '\0') {
    n = sscanf(number, "%lg", &result);
    printf("result: %g\n", result);
    return result;
  }
  return 0;
}


void inputValues(MATRIX* m) {
  if(m != NULL) {
    for(int i = 0; i < m -> count; i++) {
      printf("inputting row %d\n", i + 1);
      inputRow(i, m -> rows[i]);
    }
  }
}

void freeBuffer(char** line) {
  if(*line != NULL && *line != NULL) {
    free(*line);
    *line = NULL;
  }
}

//put a printf after line 86 and call it vector.size
void inputRow(int i, VECTOR* v) {
  char* line = NULL;
  size_t count = 0; 
  if(getline(&line, &count, stdin) > 0) {
    //printf("line: %s\n", line);
    char* token = line;
    char* value = NULL;
    for(int j = 0; j < v -> size && (value = strtok(token, " \t\n")) != NULL; token = NULL, j++) {
      v -> items[j] = inputNumber(value);
      //printf("value: %g\n", v -> items[j]);  
    }
  }
  freeBuffer(&line);
}

bool setMatrixValue(const int index, const double value,  MATRIX* m){
  if(m->rows != NULL && m->count > 0){
    printf("index = %d\n", index);
    div_t rowColumn = div(index, m->rows[0]->size);
    if(rowColumn.quot < m->count) {
      m->rows[rowColumn.quot]->items[rowColumn.rem] = value;
      return true;
    }
  }
  return false;
}

bool setMatrixValues(double* values, size_t count, MATRIX* matrix) {
  if(matrix != NULL) {
    int i = 0;
    for(; i < count && setMatrixValue(i, values[i], matrix); i++);
    return i >= count;
  }
  return false;
}

void printMatrixRow(MATRIX* m, int row) {
  VECTOR* r = m->rows[row];
  for(int i = 0; i < r->size; i++) {
    printf("%g\t", r->items[i]);
  }
  printf("\n");
}

// segmentation fault in here, be scared
void printMatrix(MATRIX* m) {
  if(m != NULL) {
    for(int i = 0; i < m->count; i++) {
      printMatrixRow(m, i);
    }
  }
} 

int matrixItemCount(MATRIX* m) {
  return m != NULL ? m -> count * m -> rows[0]->size : 0;
}


double inputFactor(const char* msg) {
  printf("enter %s\n", msg);
  double n = 0.0;
  return scanf("%lg", &n) > 0 ? n : NAN;
}

double matrixItem(MATRIX* m, size_t r, size_t c) {
  return (m -> rows[r]) -> items[c];
}

bool doTranspose(MATRIX* m, MATRIX** result) {
  *result = initializeMatrix(m->count, m->rows[0]->size);
  if(result != NULL) {
    /*for(int row = 0; row < m -> count; row++) {
      VECTOR* r = m -> rows[row];
      for(int col = 0; col < r -> size; col++) {
        //r -> items[col] *= m->rows[row]->items[col];
        (*result)->
      }*/
    for(int row = 0; row < (*result)->count; row++) {
      VECTOR* r = (*result)->rows[row];
      for(int col = 0; col < r->size; col++) {
        r->items[col] = m->rows[col]->items[row];
      }  
      printMatrixRow(*result, row);
    }
    return true;
  }
  return false;
}

bool doScalarMultiplication(MATRIX* m, const double factor, MATRIX** result) {
  *result = NULL;
  printf("factor = %g\n", factor);
  if(!isnan(factor)) {
    for(int row = 0; row < m -> count; row++) {
      VECTOR* r = m -> rows[row];
      for(int col = 0; col < r -> size; col++) {
        r -> items[col] *= factor;
      }
    } 
    printf("output matrix: \n");
    printMatrix(m);  
    return true;
  }
  return false;
}

bool doScalarDivision(MATRIX* m, MATRIX** result) {
  
  return false;
}

size_t rowCount(const MATRIX* m) {
  return m != NULL ? m -> count: 0;
}

bool isSquareMatrix(const MATRIX* m) {
  size_t r = rowCount(m);
  return r > 0 && r == vectorItemCount(m -> rows[0]);
}

double cofactorTwo(MATRIX* m) {
  return matrixItem(m, 0, 0) * matrixItem(m, 1, 1) - matrixItem(m, 1, 0) * matrixItem(m, 0, 1);
}

double cofactor(MATRIX* m, const row, const column) {
  if(rowCount(m) == 2) {
    return cofactorTwo(m);
  }
}

bool doDeterminant(MATRIX* m, double* result) {
  if(isSquareMatrix(m) && result != NULL) {
    *result = 0;
    for(int i = 0; i < vectorItemCount(m -> rows[0]); i++) {
      *result += cofactor(m, 0, i);   
    }
    return true;
  }
  return false;
} 
 
bool doInverse(MATRIX* m, MATRIX** result) {

  return false;
}
