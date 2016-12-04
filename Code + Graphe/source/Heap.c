#include <stdlib.h>
#include <stdio.h>
#include "Heap.h"

Data * data_init(int x_ ,int y_,int c,int h){
    Data * d = malloc(sizeof(Data));
    d->x = x_;
    d->y = y_;
    d->heuristique = h;
    d->cout = c;

    return d;
}

#define CMP(a, b) ((a) >= (b))

// Prepares the heap for use
Heap * heap_init(int size)
{

    Heap * h = malloc(sizeof(Heap));

    h->size = size;
    h->count = 0;
    h->data = malloc(sizeof(Data) * size);

    return h;
}

// Inserts element to the heap
void heap_push(Heap * h, Data * value)
{

    int index = h->count;
    h->data[index] = value;

    int parentIndex = (index-1)/2;


    while (parentIndex >= 0) {
        Data * parent = h->data[parentIndex];
        if (value->heuristique < parent->heuristique) {
            h->data[index] = parent;
            h->data[parentIndex] = value;
            index = parentIndex;
    	}
   		else {
        	break;
    	}

    	parentIndex = (index-1)/2;
	}
    h->count++;

}

// Removes the biggest element from the heap
Data * heap_pop(Heap * h)
{
    Data * firstItem = h->data[0];
	h->count--;
	h->data[0] = h->data[h->count];

    int index = 0;

    while(1) {
		int childIndexLeft = index * 2 + 1;
		int childIndexRight = index * 2 + 2;
		int swapIndex = 0;

		if (childIndexLeft < h->count) {
			swapIndex = childIndexLeft;

			if (childIndexRight < h->count) {
				if (h->data[childIndexRight]->heuristique < h->data[childIndexLeft]->heuristique ) {
					swapIndex = childIndexRight;
				}
			}

			if (h->data[swapIndex]->heuristique < h->data[index]->heuristique ) {
                Data * parent = h->data[index];
                Data * swap = h->data[swapIndex];
                h->data[index] = swap;
                h->data[swapIndex] = parent;
                index = swapIndex;
			}
			else {
				break;
			}

		}
		else {
			break;
		}

    }

    return firstItem;
}

int HeapEstVide(Heap * h){
    return h->count == 0;
}

void HeapFree(Heap * h){
    int i = h->count;
    for(;i>0;){
         free(h->data[--i]);
    }
    free(h);
}
