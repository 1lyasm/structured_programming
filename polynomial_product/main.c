#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    int m;
    int i;
    int j;
    int productLen;
    int **poly1;
    int **poly2;
    int **product;
    int *power1, *power2, *coef1, *coef2;
    int *productCoefPtr;
    int *productPowerPtr;
    int printedFirst;

    printf("Enter term count for first polynomial: ");
    scanf(" %d", &n);

    poly1 = malloc(2 * sizeof(int*));
    poly1[0] = malloc(n * sizeof(int));
    poly1[1] = malloc(n * sizeof(int));

    for (i = 0; i < n; ++i) {
        printf("Enter power and coefficient: \n");
        scanf(" %d", &(poly1[0][i]));
        scanf(" %d", &(poly1[1][i]));
    }

    printf("Enter term count for second polynomial: ");
    scanf(" %d", &m);

    poly2 = malloc(2 * sizeof(int*));
    poly2[0] = malloc(m * sizeof(int));
    poly2[1] = malloc(m * sizeof(int));

    for (i = 0; i < m; ++i) {
        printf("Enter power and coefficient: \n");
        scanf(" %d", &(poly2[0][i]));
        scanf(" %d", &(poly2[1][i]));
    }

    product = malloc(2 * sizeof(int*));
    productLen = n * m + 1;
    product[0] = calloc(productLen, sizeof(int));
    product[1] = calloc(productLen, sizeof(int));

    for (i = 0; i < productLen; ++i) {
        product[0][i] = i;
    }

    power1 = poly1[0];
    coef1 = poly1[1];
    productCoefPtr = product[1];

    for (i = 0; i < n; ++i) {
        power2 = poly2[0];
        coef2 = poly2[1];
        for (j = 0; j < m; ++j) {
            int new_power = *power1 + *power2;
            *(productCoefPtr + new_power) += *coef1 * *coef2;

            ++power2;
            ++coef2;
        }
        ++power1;
        ++coef1;
    }

    productCoefPtr = product[1];
    productPowerPtr = product[0];
    printedFirst = 0;

    for (i = 0; i < productLen; ++i) {
        if (*productCoefPtr != 0) {
            if (printedFirst == 0) {
                if (*productPowerPtr < 0) {
                    printf("-");
                } else {
                    printf("+");
                }
                printf("(");
                printedFirst = 1;
            }
            if (i != 0) {
                printf("+(%d)*p^%d", *productCoefPtr, *productPowerPtr);
            } else {
                printf("(%d)*p^%d", *productCoefPtr, *productPowerPtr);
            }
            /* printf("%d %d\n", *productPowerPtr, *productCoefPtr); */
        }
        ++productCoefPtr;
        ++productPowerPtr;
    }
    printf(")\n");

    free(product[0]);
    free(product[1]);
    free(product);
    free(poly1[0]);
    free(poly1[1]);
    free(poly1);
    free(poly2[0]);
    free(poly2[1]);
    free(poly2);

    return 0;
}


