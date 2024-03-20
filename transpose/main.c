#include <stdio.h>
#include <stdlib.h>

static void *failMalloc(size_t nBytes) {
    void *buffer;

    buffer = malloc(nBytes);
    if (buffer == NULL) {
        fprintf(stderr, "failMalloc: malloc failed\n");
    }

    return buffer;
}

static void *fillMatrix(int *n, int *m) {
    int i;
    int j;
    int **matrix;

    printf("fillMatrix: called\n");

    printf("Enter n (number of rows): ");
    scanf(" %d", n);

    printf("Enter m (number of columns): ");
    scanf(" %d", m);

    matrix = failMalloc(*n * sizeof(int*));
    for (i = 0; i < *n; ++i) {
        matrix[i] = failMalloc(*m * sizeof(int));
    }

    for (i = 0; i < *n; ++i) {
        for (j = 0; j < *m; ++j) {
            printf("Enter matrix[%d][%d]: ", i, j);

            scanf(" %d", &(matrix[i][j]));
        }
    }

    return matrix;
}

static void printMatrix(int **matrix, int n, int m) {
    int i;
    int j;

    printf("printMatrix: Matrix:\n");

    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

static void freeMatrix(int **matrix, int n) {
    int i;

    for (i = 0; i < n; ++i) {
        free(matrix[i]);
    }

    free(matrix);
}

static void *createTranspose(int **matrix, int n, int m) {
    int **transpose = NULL;
    int newN = m;
    int newM = n;
    int i;
    int j;

    transpose = failMalloc(newN * sizeof(int*));
    for (i = 0; i < newN; ++i) {
        transpose[i] = failMalloc(newM * sizeof(int));
    }

    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            transpose[j][i] = matrix[i][j];
        }
    }

    return transpose;
}

int main(void) {
    int n;
    int m;
    int **matrix = NULL;
    int **transpose_matrix = NULL;

    matrix = fillMatrix(&n, &m);

    printMatrix(matrix, n, m);

    transpose_matrix = createTranspose(matrix, n, m);

    printMatrix(transpose_matrix, m, n);

    freeMatrix(matrix, n);
    freeMatrix(transpose_matrix, m);

    return 0;
}
