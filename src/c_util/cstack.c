#include "c_util/cstack.h"
#include <stdlib.h>

Stack*
stack_new() {
    Stack* stack  = malloc(sizeof(Stack));
    stack->length = 0;
    stack->head   = NULL;
    return stack;
}

void
stack_free(Stack* stack) {
    while (stack->head != NULL) {
        stack_pop(stack);
    }
    free(stack);
}

Stack*
stack_push(Stack* stack, void* value) {
    StackCell* cell      = malloc(sizeof(StackCell));
    cell->data.ptr_value = value;
    cell->next           = stack->head;
    stack->head          = cell;

    return stack;
}

Stack*
stack_push_int(Stack* stack, int value) {
    StackCell* cell      = malloc(sizeof(StackCell));
    cell->data.int_value = value;
    cell->next           = stack->head;
    stack->head          = cell;

    return stack;
}

Stack*
stack_pop(Stack* stack) {
    if (stack->head != NULL) {
        StackCell* cell = stack->head;
        stack->head     = cell->next;
        stack->length -= 1;
        free(cell);
    }
    return stack;
}