#ifndef STACK_H
#define STACK_H

#define INITIAL_BUFFER_SIZE 1024

typedef struct {
    int _startIndex;
    int _endIndex;
    void *_buffer;
} Stack;

Stack *constructStack(void);
void freeStack(Stack *);

#endif
