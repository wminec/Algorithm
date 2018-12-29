#include <stdlib.h>
#include "binaryheap.h"

void heapify(Heap *heap, int index);

Heap *create_heap( CompareFtnType f, int capacity )
{
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->data = (Run **)malloc(cap*sizeof(Run *));
    heap->capacity = capacity;
    heap->heapSize = 0;
    heap->compareFtn = f;
    return heap;
}

bool insert(Heap *heap, Item item)
{



}

Item extractMin(Heap *heap)
{



}

void heapify(Heap *heap, int index)
{



}