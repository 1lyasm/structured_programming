#include <stdio.h>
#include <stdlib.h>


#define COMPRESSED_COLUMN_COUNT 3

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

  matrix = failMalloc(*n * sizeof(int *));
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

int countNonZero(int **matrix, int n, int m) {
    int i;
    int j;
    int nonZeroCount = 0;

    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            if (matrix[i][j] != 0) {
                ++nonZeroCount;
            }
        }
    }

    return nonZeroCount;
}

int **compressMatrix(int **matrix, int n, int m,
                     int *compressedRowCount) {
    int **compressed;
    int i;
    int j;
    int compressedIndex = 0;

    *compressedRowCount = countNonZero(matrix, n, m);

    compressed = failMalloc(*compressedRowCount * sizeof(int *));
    for (i = 0; i < *compressedRowCount; ++i) {
        compressed[i] = failMalloc(COMPRESSED_COLUMN_COUNT * sizeof(int));
    }

    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            if (matrix[i][j] != 0) {
                compressed[compressedIndex][0] = i;
                compressed[compressedIndex][1] = j;
                compressed[compressedIndex][2] = matrix[i][j];

                ++compressedIndex;
            }
        }
    }

    return compressed;
}

int main(void) {

    int n;
    int m;
    int **matrix = NULL;
    int **compressed = NULL;
    int compressedRowCount;

    matrix = fillMatrix(&n, &m);

    printMatrix(matrix, n, m);

    compressed = compressMatrix(matrix, n, m, &compressedRowCount);

    printMatrix(compressed, compressedRowCount, COMPRESSED_COLUMN_COUNT);

    freeMatrix(matrix, n);
    freeMatrix(compressed, compressedRowCount);

    return 0;
}
