#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotecaqueue.h"
#include "bibliotecaqueue.h"
#ifndef bibliotecaheap_h
#define bibliotecaheap_h

typedef struct Heapmax 
{
    Jucator **vec; 
    int size, capacity; 
} Heapmax;
Heapmax * create(int capacitate);
int resize(Heapmax *h);
void insertHeap(Heapmax *h,Jucator *j);
int leftChild(Heapmax *h, int i);
int rightChild(Heapmax *h, int i);
void heapifyDown(Heapmax *h, int i);
Jucator *maxVal(Heapmax *h);
void deleteHeap(Heapmax**h);
#endif