#include <stdio.h>

int main(void) {
    int number = 65;
    float floatNumber = 700.555;
    int subtractionResult = 10u - 15;
    unsigned int unsignedSubtractionResult = 10u - 15;

    printf("Number as long int: %li\n", number);
    printf("Number as unsigned int: %u\n", number);
    printf("Number as character: %c\n", number);
    printf("010 as octal: %o\n", 010);
    printf("010 as decimal: %d\n", 010);
    printf("123 in scientific notation: %e\n", 123.);
    printf("Float number as double: %.2f\n", floatNumber);
    printf("Float number in exponential form: %e\n", floatNumber);

    printf("Subtraction result: %d\n", subtractionResult);
    printf("Unsigned subtraction result: %u\n", unsignedSubtractionResult);

    return 0;
}
