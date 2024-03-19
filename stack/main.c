#include <stdio.h>

#include "stack.h"

int main(void) {
    Stack *stack = constructStack();

    printf("%p\n", (void*) stack);

    return 0;
}

