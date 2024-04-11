#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int biggest(int **mtx, int n) {
    int i, j, max_ = INT_MIN;
    for (i = 0; i < n; ++i) {
        int val = mtx[i][0] * mtx[i][0] + mtx[i][1] * mtx[i][1];
        if (val > max_) {
            max_ = val;
            j = i;
        }
    }
    return j;
}

void print(int **mtx, int n) {
    int i;
    for (i = 0; i < n; ++i) {
        if (mtx[i][1] >= 0) {
            printf("%d + %di\n", mtx[i][0], mtx[i][1]);
        } else {
            printf("%d - %di\n", mtx[i][0], -mtx[i][1]);
        }
    }
}

int main() {
    int n, i;
    int **mtx;
    int row;

    printf("n: ");
    scanf(" %d", &n);

    mtx = malloc(n * sizeof(int*));

    for (i = 0; i < n; ++i) {
        mtx[i] = malloc(2 * sizeof(int));
    }

    for (i = 0; i < n; ++i) {
        printf("%d. real: ", i);
        scanf(" %d", &(mtx[i][0]));

        printf("%d. complex: ", i);
        scanf(" %d", &(mtx[i][1]));
    }


    row = biggest(mtx, n);
    printf("biggest row: %d\n", row);

    print(mtx, n);


    for (i = 0; i < n; ++i) {
        free(mtx[i]);
    }
    free(mtx);
}
