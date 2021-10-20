#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void help() {
    printf("Usage <./range [N]> or <./range [M] [N]> <./range [M] [N] [S]>\n");
    printf("    ./range [N]        : to print sequence from 0 to [N - 1]\n");
    printf("    ./range [M] [N]    : to print sequence from M to [N - 1]\n");
    printf("    ./range [M] [N] [S]: to print sequence from M to [N - 1] with step [S]\n");
    printf("    --help   print this message\n");
}

void range(int M, int N, int S) {
    for (int i = M; i < N; i += S)
        printf("%d\n", i);
}

int main(int argc, char *argv[]) {      
    if (argc == 1) {
        help();
        return 0;
    }

    int M = 0;
    int N;
    int S = 1;

    if (argc == 2) {
        if (strcmp(argv[1], "--help") == 0) {
            help();
            return 0;
        }

        N = atoi(argv[1]);
    }
    else if (argc == 3) {
        M = atoi(argv[1]);
        N = atoi(argv[2]);
    }
    else if (argc == 4) {
        M = atoi(argv[1]);
        N = atoi(argv[2]);
        S = atoi(argv[3]);
    }
    else {
        printf("Incorrent parameters count. Use [--help] flag to see correct usage\n");
        return -1;
    }

    range(M, N, S);
    return 0;
}