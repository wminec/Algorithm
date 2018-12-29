#include <stdlib.h>
#include "binaryheap.h"

void heapify(Heap *heap, int index);

Heap *create_heap( CompareFtnType f, int cap )
{
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->data = (Item *)malloc(cap * sizeof(Item));
    heap->capacity = cap;
    heap->heapSize = 0;
    heap->compareFtn = f;
    return heap;
}

bool insert(Heap *heap, Item item)
{
    heap->data[heap->heapSize++] = item;
    int i = heap->heapSize-1;
    while (i > 0 && heap->compareFtn(heap->data[i], heap->data[(i-1)/2]) < 0) {
        Item tmp = heap->data[i];
        heap->data[i] = heap->data[(i-1)/2];
        heap->data[(i-1)/2] = tmp;
        i = (i - 1) / 2;
    }
    return true;
}

Item extractMin(Heap *heap)
{
    Item returnValue = heap->data[0];
    heap->data[0] = heap->data[heap->heapSize-1];
    heap->heapSize--;
    heapify(heap, 0);
    return returnValue;
}

void heapify(Heap *heap, int index)
{
    if (index*2+1 >= heap->heapSize)
        return;
    int min = index*2+1;
    if (index*2+2 < heap->heapSize && heap->compareFtn(heap->data[min], heap->data[index * 2 + 2]) > 0)
        min = index*2+2;
    if (heap->compareFtn(heap->data[index], heap->data[min]) > 0) {
        Item tmp = heap->data[index];
        heap->data[index] = heap->data[min];
        heap->data[min] = tmp;
        heapify(heap, min);
    }
}
