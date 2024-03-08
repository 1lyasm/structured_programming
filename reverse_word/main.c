#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE 256

static void swap(char *a, char *b) {
  char temp = *a;
  *a = *b;
  *b = temp;
}

static void reverseWord(char *word) {
  unsigned long n = strlen(word);
  unsigned long i;

  for (i = 0; i < n / 2; ++i) {
    swap(&word[i], &word[n - i - 1]);
    printf("Word after reversing %lu and %lu indices: %s\n", i,
           n - i, word);
  }
}

int main(void) {
  char *word = malloc(MAX_WORD_SIZE * sizeof(char));

  if (word == NULL) {
    fprintf(stderr, "main: malloc failed");
    exit(EXIT_FAILURE);
  }

  printf("Enter a word to be reversed: ");
  scanf(" %s", word);

  printf("Input: %s\n", word);

  reverseWord(word);

  printf("Word after reversal: %s\n", word);

  free(word);

  return 0;
}
