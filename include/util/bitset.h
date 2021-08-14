//
//  bitset.h
//  test
//
//  Created by peter on 2021/8/13.
//

#ifndef bitset_h
#define bitset_h

#include <stdbool.h>

typedef struct bitset {
    int len;
    unsigned char *arr;
} bitset;

bitset* bitset_new(int size);
void bitset_free(bitset* ptr);

void bitset_set(bitset* bset, int index);
void bitset_unset(bitset* bset, int index);
bool bitset_get(bitset* bset, int index);

#endif /* bitset_h */
