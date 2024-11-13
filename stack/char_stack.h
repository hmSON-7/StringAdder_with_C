#ifndef CHAR_STACK_H
#define CHAR_STACK_H

#define MAX_STACK_SIZE 150

typedef struct {
    char data[MAX_STACK_SIZE];
    int top;
} CharStack;

void initStack(CharStack *stack);
int isEmpty(CharStack *stack);
int isFull(CharStack *stack);
void push(CharStack *stack, char value);
char pop(CharStack *stack);
char peek(CharStack *stack);
int getSize(CharStack *stack);
void clear(CharStack *stack);
char *showList(CharStack *stack);

#endif
