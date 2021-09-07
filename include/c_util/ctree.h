#ifndef _c_tree_h_
#define _c_tree_h_

struct TreeCell {
    union {
        int int_value;
        void* ptr_value;
    } data;

    struct TreeCell* left;
    struct TreeCell* right;
};

struct Tree {
    struct TreeCell* root;
};

#endif // _c_tree_h_
