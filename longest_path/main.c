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

static int search(int target, int *array, int arrayLength) {
    int i;
    int searchResult = -1;

    for (i = 0; i < arrayLength && searchResult < 0; ++i) {
        if (array[i] == target) {
            searchResult = i;
        }
    }

    return searchResult;
}

static int *fillPathIds(int **matrix, int n, int m, int *idCount) {
    int *pathIds = NULL;
    int i;
    int j;

    pathIds = failMalloc(n * m * sizeof(int));

    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            if (matrix[i][j] != 0) {
                int searchResult;

                searchResult = search(matrix[i][j], pathIds, *idCount);
                if (searchResult == -1) {
                    pathIds[*idCount] = matrix[i][j];
                    ++(*idCount);
                }
            }
        }
    }

    return pathIds;
}

static int findPathLength(int pathId, int **matrix, int n, int m) {
    int i;
    int j;
    int initialX;
    int initialY;

    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            if (matrix[i][j] == pathId) {
                initialX = i;
                initialY = j;
            }
        }
    }

    while () {
        if (i > 0 && matrix[i - 1][j] == pathId) { // up

        }  else if (i > 0 && j + 1 < m && matrix[i - 1][j + 1] == pathId) { // upper right

        } else if (j + 1 < m && matrix[i][j + 1] == pathId) { // right
                                                              //
        } else if (i + 1 < n && j + 1 < m && matrix[i + 1][j + 1] == pathId) {}
    }

}

static void findLongestPath(int **matrix, int n, int m, int *longestPathId,
                            int *longestPathLength) {
    int *pathIds = NULL;
    int idCount;
    int i;

    *longestPathLength = -1;
    *longestPathId = -1;

    pathIds = fillPathIds(matrix, n, m, &idCount);

    for (i = 0; i < pathIds; ++i) {
        int pathId;
        int pathLength;

        pathId = pathIds[i];
        pathLength = findPathLength(pathId, matrix, n, m);

        if (pathLength > *longestPathLength) {
            *longestPathLength = pathLength;
            *longestPathId = pathId;
        }
    }

    free(pathIds);
}

int main(void) {
  int **matrix;
  int n;
  int m;
  int longestPathId;
  int longestPathLength;

  matrix = fillMatrix(&n, &m);

  printMatrix(matrix, n, m);

  findLongestPath(matrix, n, m, &longestPathId, &longestPathLength);

  freeMatrix(matrix, n);

  return 0;
}
