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

static void printIntArray(int *array, size_t length) {
  int i;

  for (i = 0; i < length; ++i) {
    printf("%d ", array[i]);
  }
  printf("\n");
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

  printf("fillPathIds: starting\n");

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

  printf("fillPathIds: idCount: %d\n", *idCount);
  printf("fillPathIds: pathIds: ");
  printIntArray(pathIds, *idCount);

  return pathIds;
}

static int findPathLength(int pathId, int **matrix, int n, int m) {
  int i;
  int j;
  int initialX;
  int initialY;
  int pathEnded;
  int pathLength;
  int foundInitial;

  printf("findPathLength: starting\n");
  printf("findPathLength: path id: %d\n", pathId);

  foundInitial = 0;
  for (i = 0; i < n && foundInitial == 0; ++i) {
    for (j = 0; j < m && foundInitial == 0; ++j) {
      if (matrix[j][i] == pathId) {
        initialX = j;
        initialY = i;

        foundInitial = 1;
      }
    }
  }

  printf("findPathLength: initial x: %d, initial y: %d\n", initialX, initialY);

  pathEnded = 0;
  pathLength = 1;
  i = initialX;
  j = initialY;

  while (pathEnded == 0 && i >= 0 && i < n && j >= 0 && j < m) {
    printf("findPathLength: at i: %d, j: %d\n", i, j);

    if (i > 0 && matrix[i - 1][j] == pathId) { // Up
      printf("findPathLength: going up\n");
      --i;
    } else if (i > 0 && j + 1 < m &&
               matrix[i - 1][j + 1] == pathId) { // Upper right
      printf("findPathLength: goidn upper right\n");
      --i;
      ++j;
    } else if (j + 1 < m && matrix[i][j + 1] == pathId) { // Right
      printf("findPathLength: going right\n");
      ++j;
    } else if (i + 1 < n && j + 1 < m &&
               matrix[i + 1][j + 1] == pathId) { // Bottom right
      printf("findPathLength: going bottom right\n");
      ++i;
      ++j;
    } else if (i + 1 < n && matrix[i + 1][j] == pathId) { // Bottom
      printf("findPathLength: going bottom\n");
      ++i;
    } else {
      pathEnded = 1;
    }

    if (pathEnded == 0) {
      ++pathLength;
    }
  }

  printf("findPathLength: path length: %d\n", pathLength);
  printf("\n");

  return pathLength;
}

static void findLongestPath(int **matrix, int n, int m, int *longestPathId,
                            int *longestPathLength) {
  int *pathIds = NULL;
  int idCount;
  int i;

  printf("findLongestPath: starting\n");

  *longestPathLength = -1;
  *longestPathId = -1;

  pathIds = fillPathIds(matrix, n, m, &idCount);

  for (i = 0; i < idCount; ++i) {
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

  printf("Longest path is the path with id %d and length %d\n", longestPathId,
         longestPathLength);

  freeMatrix(matrix, n);

  return 0;
}
