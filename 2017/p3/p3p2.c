#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Doing this in C since it looks like there's no decent closed-form equation
 * for part 2; you just have to construct the whole array by walking around
 * the spiral, and the order of evaluation matters. Such a stateful task is
 * obviously more suited for an imperative language...
 */

#define ARRSZ  1024
#define ARRSZH ARRSZ/2

#define MAX(x, y) (((x) < (y)) ? y : x)
#define MIN(x, y) (((x) < (y)) ? x : y)

int* valAt(int** arr, int x, int y) {
    assert(x < ARRSZH && x > -ARRSZH &&
           y < ARRSZH && y > -ARRSZH);
    return &arr[ARRSZH + x][ARRSZH + y];
}

void spiralNext(int* x, int* y) {
    static int dx = 0, dy = 0, rad = 0;

    // initial step
    if (rad == 0) {
        *x += 1;
        dx = 0;
        dy = 1;
        rad = 1;
        return;
    }

    if (*x == rad && *y == rad) { // tr
        dx = -1;
        dy = 0;
    } else if (*x == rad && *y == -rad+1) { // br
        dx = 0;
        dy = 1;
    } else if (*x == -rad && *y == -rad) { // bl
        dx = 1;
        dy = 0;
        rad += 1;
    } else if (*x == -rad && *y == rad) { // tl
        dx = 0;
        dy = -1;
    }

    *x += dx;
    *y += dy;
}

int main(int argc, char** argv) {
    assert(argc == 2);
    int input = atoi(argv[1]);

    int** arr = (int**) malloc(ARRSZ * sizeof(int*));
    for (int i = 0; i < ARRSZ; ++i) {
        arr[i] = (int*) malloc(ARRSZ * sizeof(int));
        memset(arr[i], 0, ARRSZ);
    }

    *valAt(arr, 0, 0) = 1;

    int x = 0, y = 0, sum = 0;
    for (int i = 0; sum < input; ++i) {
        spiralNext(&x, &y);
        sum = *valAt(arr, x, y) +=
            *valAt(arr, x-1, y-1) +
            *valAt(arr, x,   y-1) +
            *valAt(arr, x+1, y-1) +
            *valAt(arr, x-1, y) +
            *valAt(arr, x+1, y) +
            *valAt(arr, x-1, y+1) +
            *valAt(arr, x,   y+1) +
            *valAt(arr, x+1, y+1);
    }
    printf("%d\n", sum);
}
