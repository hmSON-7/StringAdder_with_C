#include "char_stack.h"
#include <stdio.h>
#include <stdlib.h>

void initStack(CharStack *stack) {
    stack->top = -1;
    stack->negative = 0;
}

void checkNegative(CharStack *stack, int negative) {
    stack->negative = negative;
}

int isEmpty(CharStack *stack) {
    return stack->top == -1;
}

int isFull(CharStack *stack) {
    return stack->top == MAX_STACK_SIZE - 1;
}

void push(CharStack *stack, char value) {
    if (isFull(stack)) {
        printf("Stack is full!\n");
        return;
    }
    stack->data[++stack->top] = value;
}

char pop(CharStack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        exit(1);
    }
    return stack->data[stack->top--];
}

char peek(CharStack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        exit(1);
    }
    return stack->data[stack->top];
}

int getSize(CharStack *stack) {
    return stack->top + 1;
}

void clear(CharStack *stack) {
    stack->top = -1;
}

char *showList(CharStack *stack) {
    if (isEmpty(stack)) {
        return "";
    }

    char *list = (char *)malloc((stack->top + 2) * sizeof(char));
    if (list == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i <= stack->top; i++) {
        list[i] = stack->data[i];
    }
    list[stack->top + 1] = '\0';

    return list;
}
