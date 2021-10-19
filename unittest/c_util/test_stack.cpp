#include "../g.hpp"

extern "C" {
#include "c_util/cstack.h"
#include "c_util/cstr.h"
#include "c_util/cvector.h"
}

TEST(c_util, cstack) {
    Stack* stack = stack_new();
    stack_push_int(stack, 1);
    stack_push_int(stack, 2);
    stack_push_int(stack, 3);
    stack_push_int(stack, 4);
    stack_push_int(stack, 5);

    EXPECT_EQ(5, stack_top_int(stack));
    stack_pop(stack);
    EXPECT_EQ(4, stack_top_int(stack));

    stack_free(stack);
}

TEST(c_util, cstack_ptr) {
    int* ptr     = (int*)std::malloc(sizeof(int));
    Stack* stack = stack_new();
    stack_push(stack, ptr);
    stack_push(stack, ptr);
    stack_push(stack, ptr);
    stack_push(stack, ptr);
    stack_push(stack, ptr);

    EXPECT_EQ(ptr, stack_top(stack));
    stack_pop(stack);
    EXPECT_EQ(ptr, stack_top(stack));

    stack_free(stack);

    std::free(ptr);
}

TEST(c_util, cstr) {
    Str* s = str_new("hello", 5);
    EXPECT_EQ(s->len, 5);
    EXPECT_STREQ(s->value, "hello");
    str_free(s);
}

TEST(c_util, cvector) {
    Vector* v = vector_new();
    vector_add_int(v, 1);
    vector_add_int(v, 2);
    vector_add_int(v, 3);
    vector_add_int(v, 4);

    EXPECT_EQ(1, vector_index_int(v, 0));
    EXPECT_EQ(2, vector_index_int(v, 1));
    EXPECT_EQ(3, vector_index_int(v, 2));
    EXPECT_EQ(4, vector_index_int(v, 3));

    vector_free(v);
}

TEST(a, b) {

    int* arr = new int[100];
    for (int i{ 0 }; i < 100; i++) {
        *(arr + i) = i;
    }

    int* q = arr + 50;
    int j  = q[-1];
    int q2 = q[-2];
}
