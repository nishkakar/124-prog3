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

    FILE* fp;
    fp = fopen(inputfile, "r");

    char buf[100];

    for (int i = 0; i < 100; i++) {
        fgets(buf, sizeof(buf), fp);
    }

    // test to see if loading buf worked
    for (int i = 0; i < 100; i++) {
        printf("%s\n", buf[i])
    }
}