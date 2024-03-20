#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

/*
 * failMalloc is a wrapper for malloc that fails (exits process) if malloc call
 * returns error code
 */
static void *failMalloc(size_t nBytes) {
  void *buffer;

  buffer = malloc(nBytes);
  if (buffer == NULL) {
    fprintf(stderr, "failMalloc: malloc failed\n");
  }

  return buffer;
}

Stack *constructStack(void) {
  Stack *stack;

  printf("constructStack: starting\n");

  stack = failMalloc(sizeof(Stack));

  stack->_buffer = failMalloc(INITIAL_BUFFER_SIZE);
  stack->_startIndex = 0;
  stack->_endIndex = -1;

  return stack;
}

size_t getStackItemCount(Stack *stack) {
  size_t nItems;

  nItems = (size_t)(stack->_endIndex - stack->_startIndex + 1);

  return nItems;
}

void push(Stack *stack, void *item, size_t item_size) {
  size_t nItems;

  nItems = getStackItemCount(stack);

  printf("push: nItems: %lu\n", nItems);
}

void freeStack(Stack *stack) {
  free(stack->_buffer);
  free(stack);
}
