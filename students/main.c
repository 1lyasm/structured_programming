#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int id;
  char *name;
  int age;
  double avg;
} Stud;

void sortAvg(Stud **studs, int n) {
  int i, j;

  for (i = 0; i < n; ++i) {
    for (j = 0; j < n - 1; ++j) {
      if (studs[j]->avg > studs[j + 1]->avg) {
        Stud *tmp = studs[j + 1];
        studs[j + 1] = studs[j];
        studs[j] = tmp;
      }
    }
  }
}

void sortName(Stud **studs, int n) {
  int i, j;

  for (i = 0; i < n; ++i) {
    for (j = 0; j < n - 1; ++j) {
      if (strcmp(studs[j]->name, studs[j + 1]->name) > 0) {
        Stud *tmp = studs[j + 1];
        studs[j + 1] = studs[j];
        studs[j] = tmp;
      }
    }
  }
}

void print(Stud **studs, int n) {
  int i, j;

  for (i = 0; i < n; ++i) {
    printf("%d - %s - %d - %lf\n", studs[i]->id, studs[i]->name, studs[i]->age,
           studs[i]->avg);
  }
}

int main() {
  Stud **studs;
  int n, i;

  printf("n: ");
  scanf(" %d", &n);

  studs = malloc(n * sizeof(Stud));

  for (i = 0; i < n; ++i) {
      int slen = 256;
    studs[i] = malloc(sizeof(Stud));
    studs[i]->name = malloc(slen * sizeof(char));
    printf("%d. id: ", i);
    scanf(" %d", &(studs[i]->id));
    printf("%d. name: ", i);
    scanf(" %s", studs[i]->name);
    printf("%d. age: ", i);
    scanf(" %d", &(studs[i]->age));
    printf("%d. avg: ", i);
    scanf(" %lf", &(studs[i]->avg));
  }

  print(studs, n);
  sortAvg(studs, n);
  printf("\n");
  print(studs, n);
  sortName(studs, n);
  printf("\n");
  print(studs, n);

  for (i = 0; i < n; ++i) {
    free(studs[i]->name);
    free(studs[i]);
  }

  free(studs);

  return 0;
}
