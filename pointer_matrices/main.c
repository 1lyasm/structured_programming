#include <stdio.h>
#include <string.h>

#define MAX_WORDS 5
#define LAST_LONG 2

int main() {
  char *dict[LAST_LONG][MAX_WORDS] = {
      {"abhar", "able", "abort", "about", NULL},
      {"abswde", "acceptor", "accord", "achat", NULL}};
  char str[10];
  int diff = -1, language, j = 0;
  printf("Language: ");
  scanf("%d", &language);
  printf("String: ");
  scanf("%s", str);
  while (dict[language][j] != NULL && diff < 0) {
    diff = strcmp(dict[language][j], str);
    ++j;
  }
  if (diff == 0) {
    printf("match\n");
  } else {
    --j;
    printf("best match %s\n", dict[language][j]);
  }
  return 0;
}
