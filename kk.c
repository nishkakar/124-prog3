// ===============================
// CS124 Programming Assignment 3
// Kunal Mehta & Nishant Kakar
// ===============================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

////HELPER FUNCTIONS//////

// duplicates array
void intdup(int* src, int* dest)
{
    for (int i = 0; i < 100; i++) {
        dest[i] = src[i];
    }
}

// debugging function
void print_int_sequence(int* sequence) {
    for (int i = 0; i < 100; i++) {
        printf("%d\n", sequence[i]);
    }
    printf("\n\n\n");
}

// debugging function
void print_sequence(long long* sequence) {
    for (int i = 0; i < 100; i++) {
        printf("%lld\n", sequence[i]);
    }
    printf("\n\n\n");
}

// generates random solution for the random move interpretation
void generate_random_solution(int* solution) {
    time_t t;
    for (int i = 0; i < 100; i++) {
        double r = (double) rand()/(double) RAND_MAX;
        if (r <= 0.5)
            solution[i] = -1;
        else
            solution[i] = 1;
    }
}

// generates neighbor solution for hill climbing and simulated annealing algorithms in the random move interpretation
void generate_neighbor_solution(int* solution) {
    time_t t;
    int index_1 = (int) rand() % 100;
    int index_2 = 0;
    while (index_2 == index_1)
        index_2 = (int) rand() % 100;
    solution[index_1] *= -1;
    double probablity = (double) rand()/(double) RAND_MAX;
    if (probablity <= 0.5)
        solution[index_2] *= -1;
}

// calculates the residue given the input array of random numbers and a solution array for the random move interpretation
long long residue(long long* input, int* solution) {
    int sum_1 = 0;
    int sum_2 = 0;
    for (int i = 0; i < 100; i++) {
        if (solution[i] == 1)
            sum_1 += input[i];
        else
            sum_2 += input[i];
    }
    return llabs(sum_1 - sum_2);
}

// given a partition, generates a new sequence that enforces the prepartition 
void sequence_from_partition(long long* new_sequence, int* partition, long long * input) {
    for (int i = 0; i < 100; i++)
        new_sequence[i] = 0;

    for (int i = 0; i < 100; i++)
        new_sequence[partition[i]] += input[i];
}

// generates a random prepartition
void generate_random_partition(int* partition) {
    for (int i = 0; i < 100; i++)
        partition[i] = (int) rand() % 100;
}

//MAX HEAP (heap is an array)
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

// KK Algorithm
long long kk(long long *A) {
    MaxHeap heap;
    heap.size = 0;

    for (int i = 0; i < 100; i++) {
        enqueue(&heap, A[i]);
    }

    while(heap.size > 1) {
        long long max1 = returnmax(&heap);
        long long max2 = returnmax(&heap);
        if(max2 == 0) {
            return max1;
        }
        enqueue(&heap, max1 - max2);
    }
    long long residue = heap.data[0];
    free(heap.data);
    return residue;
}

// implements prepartition interpretation for hill climbing algorithm
long long hill_climb_2(long long* input) {
    int prepartition[100];
    int new_partition[100];
    long long new_sequence[100];
    long long neighbor[100];
    time_t t;
    srand((unsigned) time(&t));

    generate_random_partition(prepartition);
    sequence_from_partition(new_sequence, prepartition, input);
    long long best_residue = kk(new_sequence);

    for (int i = 0; i < 25000; ++i)
    {
        intdup(prepartition, new_partition);

        int rand_index_i = (int) rand() % 100;
        int rand_index_j = (int) rand() % 100;
        int old_index = prepartition[rand_index_i];
        while(old_index == rand_index_j)
            rand_index_j = (int) rand() % 100;

        new_partition[rand_index_i] = rand_index_j;
        sequence_from_partition(neighbor, new_partition, input);

        long long residue = kk(neighbor);
        if(residue < best_residue) {
            best_residue = residue;
            sequence_from_partition(new_sequence, new_partition, input);
            intdup(new_partition, prepartition);
        }
    }
    return best_residue;

}

// implements prepartition interpretation for simulated annealing algorithm
long long simulated_annealing_2(long long* input) {
    int prepartition[100];
    int new_partition[100];
    long long new_sequence[100];
    long long neighbor[100];
    time_t t;
    srand((unsigned) time(&t));

    generate_random_partition(prepartition);
    sequence_from_partition(new_sequence, prepartition, input);
    long long best_residue = kk(new_sequence);
    long long global_best_residue = best_residue;

    for (int i = 0; i < 2500f0; ++i)
    {
        intdup(prepartition, new_partition);

        int rand_index_i = (int) rand() % 100;
        int rand_index_j = (int) rand() % 100;
        int old_index = prepartition[rand_index_i];
        while(old_index == rand_index_j)
            rand_index_j = (int) rand() % 100;

        new_partition[rand_index_i] = rand_index_j;
        sequence_from_partition(neighbor, new_partition, input);

        long long residue = kk(neighbor);
        if(residue < best_residue) {
            best_residue = residue;
            sequence_from_partition(new_sequence, new_partition, input);
            intdup(new_partition, prepartition);
        }
        else {
            double T = pow(10., 10.) * pow(.8, (double) (i/300));
            double probability = exp(-(best_residue - global_best_residue)/T);
            if (((double) rand()/(double) RAND_MAX) <= probability) {
                best_residue = residue;
                sequence_from_partition(new_sequence, new_partition, input);
                intdup(new_partition, prepartition);
            }
        }
        if(best_residue < global_best_residue)
            global_best_residue = best_residue;
    }
    return global_best_residue;
}

// implements prepartition interpretation for repeated random algorithm
long long repeated_random_2(long long* input) {
    int prepartition[100];
    long long new_sequence[100];
    time_t t;
    srand((unsigned) time(&t));
    long long best_residue = 10E12;

    for (int j = 0; j < 25000; j++) {
        generate_random_partition(prepartition);
        sequence_from_partition(new_sequence, prepartition, input);
        long long residue = kk(new_sequence);
        if (residue < best_residue) 
            best_residue = residue;
    }

    return best_residue;
}

// logic for which prepartition algorithm will be called
long long partition(long long* input, char* algorithm) {
    long long answer;
    if(strcmp(algorithm, "repeated_random") == 0) {
        answer = repeated_random_2(input);
    }
    else if(strcmp(algorithm, "hill_climbing") == 0) {
        answer = hill_climb_2(input);
    }
    else {
        answer = simulated_annealing_2(input);
    }
    return answer;
}

// implements random move interpretation for repeated random, hill climbing, and simulated annealing algorithms
long long random_move(long long* input, char* algorithm) {
    int solution[100];
    int new_solution[100];
    generate_random_solution(solution);
    long long best_residue = residue(input, solution);
    long long new_residue;
    long long global_best_residue = best_residue;

    time_t t;
    srand((unsigned) time(&t));
    for (int i = 0; i < 25000; i++) {
        if (strcmp(algorithm, "repeated_random") == 0) {
            generate_random_solution(new_solution);
            new_residue = residue(input, new_solution);
            if (new_residue < best_residue) {
                best_residue = new_residue;
            }
        }
        else if (strcmp(algorithm, "hill_climbing") == 0) {
            intdup(solution, new_solution);
            generate_neighbor_solution(new_solution);
            new_residue = residue(input, new_solution);
            if (new_residue < best_residue) {
                best_residue = new_residue;
                intdup(new_solution, solution);
            }
        }
        else{
            intdup(solution, new_solution);
            generate_neighbor_solution(new_solution);
            new_residue = residue(input, new_solution);
            if (new_residue < best_residue) {
                best_residue = new_residue;
                intdup(new_solution, solution);
            }
            else {
                double T = pow(10., 10.) * pow(.8, (double) (i/300));
                double probablity = exp(-(new_residue - best_residue)/T);
                if (((double) rand()/(double) RAND_MAX) <= probablity) {
                    intdup(new_solution, solution);
                    best_residue = new_residue;
                }
            }
            if(best_residue < global_best_residue) {
                global_best_residue = best_residue;
            }
        }
    }
    if(strcmp(algorithm, "simulated_annealing") == 0)
        return global_best_residue;
    else
        return best_residue;
}

int main(int argc, char* argv[]) {
    MaxHeap heap1;
    heap1.size = 0;

    char* inputfile = argv[1];

    long long input[100];

    // loads numbers from file into array
    FILE* fp;
    fp = fopen(inputfile, "r");
    for (int i = 0; i < 100; i++) {
        fscanf(fp, "%lld", &input[i]);
    }

    char* RR = "repeated_random";
    char* HC = "hill_climbing";
    char* SA = "simulated_annealing";

    printf("KK Residue:%lld\n", kk(input));

    printf("RR1 Residue:%lld\n", random_move(input, RR));
    printf("HC1 Residue:%lld\n", random_move(input, HC));
    printf("SA1 Residue:%lld\n", random_move(input, SA));

    printf("RR2 Residue:%lld\n", partition(input, RR));
    printf("HC2 Residue:%lld\n", partition(input, HC));
    printf("SA2 Residue:%lld\n", partition(input, SA));

    printf("\n");
    printf("\n");
}