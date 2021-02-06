#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
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
    //printf("result: %g\n", result);
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