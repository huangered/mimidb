#ifndef _c_stack_h_
#define _c_stack_h_

typedef struct StackCell {
    union {
        int int_value;
        void* ptr_value;
    } data;
    struct StackCell* next;
} StackCell;

typedef struct Stack {
    int length;
    StackCell* head;
} Stack;

#define stack_len(l)     (l->length)
#define stack_top(l)     (l->head->data.ptr_value)
#define stack_top_int(l) (l->head->data.int_value)

Stack* stack_new();
void stack_free(Stack* stack);
Stack* stack_push(Stack* stack, void* value);
Stack* stack_push_int(Stack* stack, int value);
Stack* stack_pop(Stack* stack);

#endif // !_c_stack_h_
