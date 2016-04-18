// ===============================
// CS124 Programming Assignment 3
// Kunal Mehta & Nishant Kakar
// ===============================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int random_solutions(long long* input) {
    long long group1[100];
    long long group2[100];
    long long best_residue = 0;
    for (int i = 0; i < 25000; i++) {
        for (int j = 0; j < 100; j++) {
            srand(time(NULL));
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

    long long residue = random_solutions(input);
    printf("%lld", residue);

    // test to see if loading input worked
    // for (int i = 0; i < 100; i++) {
    //     printf("%lld\n", input[i]);
    // }
}