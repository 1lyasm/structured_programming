#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE 256

static void *fmalloc(unsigned long nByte) {
  void *buffer;

  buffer = malloc(nByte);
  if (buffer == NULL) {
    fprintf(stderr, "fmalloc: malloc failed\n");
    exit(EXIT_FAILURE);
  }

  return buffer;
}

typedef struct {
  int found;
  unsigned long foundIndex;
} SearchResult;

static SearchResult *constructSearchResult(void) {
  SearchResult *result;

  result = fmalloc(sizeof(SearchResult));

  result->found = 0;
  result->foundIndex = ULONG_MAX;

  return result;
}

static SearchResult *searchSubstring(char *string, char *substring) {
  SearchResult *result;
  char firstTarget;
  unsigned long stringLength, substringLength, i, j;

  result = constructSearchResult();

  firstTarget = substring[0];

  stringLength = strlen(string);
  substringLength = strlen(substring);

  result->found = 0;

  if (substringLength <= stringLength) {
    for (i = 0; i < stringLength - substringLength + 1 && result->found == 0;
         ++i) {
      if (string[i] == firstTarget) {
        printf("First character of the target is seen in %lu index of the "
               "string\n",
               i);

        result->found = 1;
        result->foundIndex = i;

        for (j = 1;
             i + j < stringLength && j < substringLength && result->found == 1;
             ++j) {
          if (string[i + j] != substring[j]) {
            result->found = 0;
          }
        }

        if (j < substringLength) {
          result->found = 0;
        }
      }
    }

    if (result->found == 0) {
      result->foundIndex = ULONG_MAX;
    }
  }

  return result;
}

static void printSearchResult(SearchResult *result) {
  if (result->found == 1) {
    printf("Target was found in index %lu\n", result->foundIndex);
  } else {
    printf("Target was not found\n");
  }
}

int main(void) {
  char *word1, *word2;
  SearchResult *result;

  word1 = fmalloc(MAX_WORD_SIZE * sizeof(char));
  word2 = fmalloc(MAX_WORD_SIZE * sizeof(char));

  printf("Enter first word: ");
  scanf(" %s", word1);
  printf("First word: %s\n", word1);

  printf("Enter second word: ");
  scanf(" %s", word2);
  printf("Second word: %s\n", word2);

  result = searchSubstring(word1, word2);
  printSearchResult(result);

  free(result);
  free(word2);
  free(word1);

  return 0;
}
