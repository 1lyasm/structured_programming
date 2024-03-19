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
  printf("constructStack is called\n");

  return NULL;
}
