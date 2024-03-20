#include <stdio.h>

#include "stack.h"

int main(void) {
  Stack *stack = constructStack();
  int number = 5;

  push(stack, &number, sizeof(number));

  freeStack(stack);

  return 0;
}
