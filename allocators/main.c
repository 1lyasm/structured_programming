#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 5
#define LAST_LONG 2

int main() {
  int n = 5;
  int *arr, *arr2;
  arr = malloc(n * sizeof(int));
  printf("arr: %p\n", arr);
  free(arr);
  arr = calloc(n, sizeof(int));
  arr[0] = 5;
  printf("arr: %p\n", arr);
  arr2 = realloc(arr, (n + 3) * sizeof(int));
  free(arr2);
  return 0;
}
