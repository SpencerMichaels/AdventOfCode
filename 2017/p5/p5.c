#include <stdio.h>
#include <stdlib.h>

/*
 * Doing this problem in C because Haskell (in which recursion is idiomatic) is
 * slooooow for this kind of thing
 */

void doJumpP1(int* jumps, int* i) {
    const int loc = *i;
    const int jmp = jumps[*i];

    jumps[loc] += 1;
    *i += jmp;
}

void doJumpP2(int* jumps, int* i) {
    const int loc = *i;
    const int jmp = jumps[*i];

    jumps[loc] = (jmp >= 3) ? jmp-1 : jmp+1;
    *i += jmp;
}

int main(int argc, char** argv) {
    int numJumps = argc - 1;
    int* jumps = malloc(numJumps * sizeof(int));

    for (int i = 0; i < numJumps; ++i) {
        jumps[i] = atoi(argv[i+1]);
    }

    int i = 0;
    int count = 0;
    while (i >= 0 && i < numJumps) {
        doJumpP1(jumps, &i);
        ++count;
    }

    printf("P1: %d\n", count);

    for (int i = 0; i < numJumps; ++i) {
        jumps[i] = atoi(argv[i+1]);
    }

    i = 0;
    count = 0;
    while (i >= 0 && i < numJumps) {
        doJumpP2(jumps, &i);
        ++count;
    }

    printf("P2: %d\n", count);
}
