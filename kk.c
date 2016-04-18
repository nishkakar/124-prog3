// ===============================
// CS124 Programming Assignment 3
// Kunal Mehta & Nishant Kakar
// ===============================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// void print_sequence(long long* sequence) {
//     for (int i = 0; i < 100; i++) {
//         printf("%lld\n", sequence[i]);
//     }
// }



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

long long repeated_random_2(long long* input) {
    long long prepartition[100];
    time_t t;
    srand((unsigned) time(&t));
    long long best_residue = 10E12;
    for (int j = 0; j < 25000; j++) {
        for (int i = 0; i < 100; i++)
            prepartition[i] = (long long) rand() % 100;

        long long new_sequence[100];
        for (int i = 0; i < 100; i++)
            new_sequence[i] = 0;

        for (int i = 0; i < 100; i++)
            new_sequence[prepartition[i]] += input[i];

        long long residue = kk(new_sequence);
        if (residue < best_residue) 
            best_residue = residue;
    }

    return best_residue;
}

long long repeated_random_1(long long* input) {
    long long group1[100];
    long long group2[100];
    long long best_residue = 10E12;
    time_t t;
    srand((unsigned) time(&t));
    for (int i = 0; i < 25000; i++) {
        for (int j = 0; j < 100; j++) {
            double r = (double) rand()/(double) RAND_MAX;
            if (r <= 0.5) {
                group1[j] = input[j];
                group2[j] = 0; 
            }
            else {
                group1[j] = 0;
                group2[j] = input[j];
            }
        }

        long long sum1 = 0;
        long long sum2 = 0;
        for (int j = 0; j < 100; j++) {
            sum1 += group1[j];
            sum2 += group2[j];
        }
        long long residue = llabs(sum1 - sum2);
        // printf("residue: %lld\n", residue);
        if (residue < best_residue) 
            best_residue = residue;
    }

    return best_residue;
}

int main(int argc, char* argv[]) {
    char* inputfile = argv[1];

    long long* input = malloc(100 * sizeof(int));

    FILE* fp;
    fp = fopen(inputfile, "r");

    for (int i = 0; i < 100; i++) {
        fscanf(fp, "%lld", &input[i]);
    }

    printf("%lld\n", repeated_random_1(input));
    printf("%lld\n", repeated_random_2(input));

    // test to see if loading input worked
    // for (int i = 0; i < 100; i++) {
    //     printf("%lld\n", input[i]);
    // }
}