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

  printf("constructStack is called\n");

  stack = failMalloc(sizeof(Stack));

  stack->_buffer = failMalloc(INITIAL_BUFFER_SIZE);
  stack->_startIndex = 0;
  stack->_endIndex = -1;

  return stack;
}

void freeStack(Stack *stack) {
    free(stack->_buffer);
    free(stack);
}
