#include <stdio.h>
int main() {
  char *x[5] = {"Dandanakan1040", "Mercidabik1516", "Preveze1538",
                "Trablusgarp1911", "Kurtulus1919"};
  char *y[] = {x[0] , x[3]};
  char *p = y[0];
  printf("%s \n", y[1]);
  printf("%s \n", (p + 1));
  printf("%c \n", *(*(x + 2) + 3));
  /* printf("%c \n", *(*(y+1))[4]); */
  printf("%c\n", *(++y[1]));
}
