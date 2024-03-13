#include <stdio.h>

static void wrongIncrease(int a, int b) {
    a += b;

    printf("wrongIncrease exits with a = %d\n", a);
}

static void correctIncrease(int *a, int b) {
    *a += b;

    printf("correctIncrease exits with a = %d\n", *a);
}

int main(void) {
    int a = 3;
    int b = 5;

    wrongIncrease(a, b);
    printf("Value of a = %d in main after wrongIncrease\n", a);

    correctIncrease(&a, b);
    printf("Value of a = %d in main after correctIncrease\n", a);

    return 0;
}

