// ===============================
// CS124 Programming Assignment 3
// Kunal Mehta & Nishant Kakar
// ===============================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//priority heap (heap is an array)
//inspired by http://robin-thomas.github.io/min-heap/
typedef struct MaxHeap {
    long long *data;
    int size;
} MaxHeap;

////////////////HEAP FUNCTIONS///////////////////////
//inspired by http://robin-thomas.github.io/min-heap/

void enqueue(MaxHeap *h, long long elem) {
    if(h->size > 0) {
        h->data = realloc(h->data,((h->size)+1)*sizeof(long long));
    }
    else {
        h->data = malloc(sizeof(long long));
    }
    int i = h->size;
    h->size++;
    while(i !=0 && elem > h->data[(i-1)/2]) {
        h->data[i] = h->data[(i-1)/2];
        i = (i-1)/2;
    }
    h->data[i] = elem;
}

void swap(long long *n, long long *m) {
    long long tmp = *n;
    *n = *m;
    *m = tmp;
}

void heapify(MaxHeap *h, int i) {
    int maxElt;
    if((2*i+1)<h->size && h->data[2*i+1] > h->data[i]) {
        maxElt = 2*i+1;
    }
    else {
        maxElt = i;
    }
    if((2*i+2) < h->size && h->data[2*i+2] > h->data[maxElt]) {
        maxElt = 2*i+2;
    }
    if(maxElt != i) {
        swap(&(h->data[i]), &(h->data[maxElt]));
        heapify(h, maxElt);
    }
}

long long returnmax(MaxHeap *h) {
    long long maxElt;
    maxElt = h->data[0];
    h->size = h->size - 1;
    h->data[0] = h->data[(h->size)];
    h->data = realloc(h->data, h->size*sizeof(long long));
    heapify(h, 0);
    return maxElt;
}

///////KK ALGORITHM//////////////////////////////////////
long long kk(long long *A) {
    MaxHeap heap;
    heap.size = 0;

    for (int i = 0; i < 5; i++) {
        enqueue(&heap, A[i]);
    }

    while(heap.size > 1) {
        long long max1 = returnmax(&heap);
        long long max2 = returnmax(&heap);
        enqueue(&heap, max1 - max2);
    }
    return heap.data[0];
}



int main(int argc, char* argv[]) {
    char* inputfile = argv[1];
    int num_ints = 5;

    long long* input = malloc(10 * sizeof(long long));

    FILE* fp;
    fp = fopen(inputfile, "r");

    for (int i = 0; i < num_ints; i++) {
        fscanf(fp, "%lld", &input[i]);
    }

    long long residue = kk(input);
    printf("Residue:%lld\n", residue);
}