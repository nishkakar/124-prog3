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

int repeated_random_2(long long* input) {
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

int repeated_random_1(long long* input) {
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