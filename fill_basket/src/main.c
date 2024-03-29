#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int i, j, k;
  int n;
  int *basket;
  int lenb = 2;
  int nfilled = 1;
  int isone = 0;
  int f;

  printf("Enter n: ");
  scanf(" %d", &n);

  basket = calloc(lenb, sizeof(int));

  basket[0] = n;

  while (isone == 0) {
    if (n % 2 == 0) {
      f = n / 2;
    } else {
      f = 3 * n + 1;
    }
    n = f;
    /* if (nfilled < lenb) { */
    /*   basket[nfilled] = f; */
    /*   ++nfilled; */
    /* } else { */
    /* } */
    if (nfilled >= lenb) {
      lenb *= 2;
      basket = realloc(basket, lenb * sizeof(int));
    }
    basket[nfilled] = f;
    ++nfilled;
    if (f == 1) {
      isone = 1;
    }
  }

  /* printf("Basket array takes %lu bytes of memory with %d elements: ", */
  /*        lenb * sizeof(int), nfilled); */
  printf("Array elements: ");
  for (i = 0; i < nfilled; ++i) {
    printf("%d ", basket[i]);
  }
  printf("\n");

  printf("Element count: %d\n", nfilled);
  printf("Memory usage of the array: %d\n", lenb);

  free(basket);

  return 0;
}
