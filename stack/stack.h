#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#define INITIAL_BUFFER_SIZE 1024

typedef struct {
  int _startIndex;
  int _endIndex;
  void *_buffer;
} Stack;

Stack *constructStack(void);

size_t getStackItemCount(Stack *stack);
void push(Stack *stack, void *item, size_t item_size);

void freeStack(Stack *size);

#endif
