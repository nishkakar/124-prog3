// ===============================
// CS124 Programming Assignment 3
// Kunal Mehta & Nishant Kakar
// ===============================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char* argv[]) {
    char* inputfile = argv[1];

    long long* input = malloc(100 * sizeof(int));

    FILE* fp;
    fp = fopen(inputfile, "r");

    for (int i = 0; i < 100; i++) {
        printf("allocates # %d\n", i);
        fscanf(fp, "%lld", &input[i]);
    }

    // test to see if loading input worked
    for (int i = 0; i < 100; i++) {
        printf("%lld\n", input[i]);
    }
}