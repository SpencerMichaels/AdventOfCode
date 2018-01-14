#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BANKS_HIST_SIZE 12000

int mostBlocksIdx(const int* const bank, const int numBanks) {
    int max = 0, maxIdx = 0;
    for (int i = 0; i < numBanks; ++i) {
        if (bank[i] > max) {
            max = bank[i];
            maxIdx = i;
        }
    }
    return maxIdx;
}

int hasRepeated(int** const bank, const int lastIdx, const int numBanks) {
    for (int i = 0; i < lastIdx; ++i) {
        int repeated = 1;
        for (int j = 0; j < numBanks; ++j) {
            repeated &= (bank[lastIdx][j] == bank[i][j]);
        }
        if (repeated) return i;
    }
    return 0;
}

void redistribute(const int* oldBank, int* newBank, const int numBanks) {
    int start = mostBlocksIdx(oldBank, numBanks);
    int blocks = oldBank[start];

    for (int i = 0; i < numBanks; ++i) {
        newBank[i] = oldBank[i];
    }
    newBank[start] = 0;

    int i = (start + 1) % numBanks;
    while (blocks > 0) {
        newBank[i] += 1;
        blocks -= 1;
        i = (i + 1) % numBanks;
    }
}

void printBanks(const int* banks, const int numBanks) {
    for (int i = 0; i < numBanks; ++i) {
        printf("%d ", banks[i]);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    const int numBanks = argc-1;

    int** banksHist = (int**) malloc(BANKS_HIST_SIZE * sizeof(int*));
    for (int i = 0; i < BANKS_HIST_SIZE; ++i) {
        banksHist[i] = (int*) malloc(numBanks * sizeof(int*));
        for (int j = 0; j < numBanks; ++j) {
            banksHist[i][j] = atoi(argv[j+1]);
        }
    }

    //printBanks(banksHist[0], numBanks);

    int i = 0, repeatAt = 0;
    do {
        redistribute(banksHist[i], banksHist[i+1], numBanks);
        //printBanks(banksHist[i+1], numBanks);
        ++i;
    } while (!(repeatAt = hasRepeated(banksHist, i, numBanks)) && i < BANKS_HIST_SIZE);

    if (i == BANKS_HIST_SIZE) {
        puts("HIST SIZE EXCEEDED!");
        return 1;
    }

    printf("%d %d\n", i, i - repeatAt);
    return 0;
}
