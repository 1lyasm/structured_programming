#include <stdio.h>
#include <stdlib.h>

int Decompress(int *arr, int n, int **new);

int main() {
  int array[20], n, m, i;
  printf("Give the number of elements in the array\n");
  scanf("%d", &n);
  printf("Give the elements\n");
  for (i = 0; i < n; ++i) {
    scanf("%d", &array[i]);
  }
  int *newArray = NULL;
  m = Decompress(array, n, &newArray);
  for (i = 0; i < m; ++i) {
    printf("%d", newArray[i]);
  }
  free(newArray);
  return 0;
}

int Decompress(int *arr, int n, int **new) {
  int i, j, k;
  int len = 1;
  j = 0;
  *new = malloc(len * sizeof(int));
  for (i = 0; i < n; i += 2) {
    if (j + arr[i + 1] > len) {
      len = j + arr[i + 1];
      *new = realloc(*new, len * sizeof(int));
    }
    for (k = j; k < j + arr[i + 1]; ++k) {
      (*new)[k] = arr[i];
    }
    j = k;
  }

  return len;
}
