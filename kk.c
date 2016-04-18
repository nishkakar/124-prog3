// ===============================
// CS124 Programming Assignment 3
// Kunal Mehta & Nishant Kakar
// ===============================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char* argv[]) {
    char* inputfile = argv[2];

    int* input = malloc(100 * sizeof(int));

    FILE* fp;
    fp = fopen(inputfile, "r");

    char buf[256];
    for (int i = 0; i < 100; i++) {
        printf("allocates # %d\n", i);
        fgets(buf, sizeof(buf), fp);
        printf("reads\n");
        input[i] = atoi(buf);
    }

    // test to see if loading input worked
    // for (int i = 0; i < 100; i++) {
    //     printf("%c\n", input[i]);
    // }
}