//
//  bitset.c
//  test
//
//  Created by peter on 2021/8/13.
//

#include "c_util/bitset.h"
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

const int Width = 8;

struct bitset *bitset_new(int size) {
  struct bitset *bset = malloc(sizeof(*bset));
  bset->len = size;
  int len = (size / 9 + 1);
  bset->arr = calloc(len, sizeof(unsigned char));
  return bset;
}

void bitset_free(bitset *ptr) {
  free(ptr->arr);
  free(ptr);
}

void bitset_set(bitset *bset, int index) {
  int i = index >> 3;
  byte j = index % 8;
  *(bset->arr + i) |= 1 << j;
}

void bitset_unset(bitset *bset, int index) {
  int i = index >> 3;
  byte j = index % 8;
  *(bset->arr + i) &= ~(1 << j);
}

bool bitset_get(bitset *bset, int index) {
  int i = index >> 3;
  byte j = index % 8;
  
  return *(bset->arr + i) & (1 << j);
}
