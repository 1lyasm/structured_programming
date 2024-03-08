#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE 256
#define MAX_FOUND_COUNT 256

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
  int nFound;
  unsigned long *foundIndices;
} SearchResult;

static SearchResult *constructSearchResult(void) {
  SearchResult *result;

  result = fmalloc(sizeof(SearchResult));

  result->nFound = 0;
  result->foundIndices = fmalloc(MAX_FOUND_COUNT * sizeof(unsigned long));

  return result;
}

static SearchResult *searchSubstring(char *string, char *substring) {
  SearchResult *result;
  char firstTarget;
  unsigned long stringLength, substringLength, i, j;
  int found;

  result = constructSearchResult();

  firstTarget = substring[0];

  stringLength = strlen(string);
  substringLength = strlen(substring);

  result->nFound = 0;
  found = 0;

  if (substringLength <= stringLength) {
    for (i = 0; i < stringLength - substringLength + 1; ++i) {
      if (string[i] == firstTarget) {
        printf("First character of the target is seen in %lu index of the "
               "string\n",
               i);

        found = 1;

        for (j = 1; i + j < stringLength && j < substringLength && found == 1;
             ++j) {
          if (string[i + j] != substring[j]) {
            found = 0;
          }
        }

        if (j < substringLength) {
          found = 0;
        } else if (found == 1) {
          result->foundIndices[result->nFound] = i;
          ++result->nFound;
        }
      }
    }
  }

  return result;
}

static void printSearchResult(SearchResult *result) {
  int i;
  if (result->nFound > 0) {
    for (i = 0; i < result->nFound; ++i) {
      printf("Target %d was found in index %lu\n", i, result->foundIndices[i]);
    }
  } else {
    printf("Target was not found\n");
  }
}

static void freeSearchResult(SearchResult *result) {
  free(result->foundIndices);
  free(result);
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

  freeSearchResult(result);
  free(word2);
  free(word1);

  return 0;
}
