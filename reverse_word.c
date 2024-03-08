#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_SIZE 256

int main(void) {
    char *word = malloc(MAX_WORD_SIZE * sizeof(char));

    if (word == NULL) {
        fprintf(stderr, "main: malloc failed");
        exit(EXIT_FAILURE);
    }

    scanf(" %s", word);
    printf("%s\n", word);

    free(word);

    return 0;
}

