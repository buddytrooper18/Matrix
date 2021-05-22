#include <stdlib.h>
#include "vector.h"

 size_t vectorMemorySize(const size_t size){
  return sizeof(VECTOR) + sizeof(double) * size;
}

size_t vectorItemCount(VECTOR* v) {
  return v != NULL ? v->size : 0;
}

void setupVectorItemsSize(const size_t size, VECTOR* result) {
  result->items = (double*)(result + sizeof(VECTOR));
  result->size = size;
}

VECTOR* initializeVector(const size_t size) {
    VECTOR* result = (VECTOR*)malloc(vectorMemorySize(size));
    setupVectorItemsSize(size, result);
    return result;
}

void freeVector(VECTOR** v) {
  if(v != NULL && *v != NULL) {
    free(*v);
    *v = NULL;
  }
}

void logVector(VECTOR* vector) {
    for(int i = 0; i < vector->size; i++) {
        printf("%f\n", vector->items[i]);
    }
}

void copyItems(const int start, const int end, VECTOR* source, VECTOR* dst) {
  if(source != NULL && dst != NULL && start < end) {
    for(int i = start; i < end; i++) {
      dst -> items[i] = source -> items[i];
    }
  }
}

VECTOR* insert(const int index, double value, VECTOR** v) {
  VECTOR* vn = initializeVector((*v) -> size + 1);
  copyItems(0, index, *v, vn);
  vn -> items[index] = value;
  copyItems(index, (*v) -> size, *v, vn);
  freeVector(v);
  return vn;
}