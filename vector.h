/* This defines the vector struct
vector struct is an array of doubles*/

#if !defined __vector_h__
#define __vector_h__ 1
#include <stdio.h>
struct Vector {
    double* items;
    size_t size;
};
typedef struct Vector VECTOR;
VECTOR* initializeVector(const size_t);
size_t vectorItemCount(VECTOR*);
void freeVector(VECTOR**);
size_t vectorMemorySize(const size_t);
void setupVectorItemsSize(size_t, VECTOR*);
VECTOR* insert(const int, double, VECTOR**);
#endif //__vector_h__//