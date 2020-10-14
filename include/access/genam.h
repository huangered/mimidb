/*
 * general index api function
 */
#ifndef _GENAM_H_
#define _GENAM_H_

#include "access/heaptuple.h"

typedef struct A {
    int i;
};

extern struct A* systable_beginscan();
extern HeapTuple systable_getnext();
extern void systable_endscan();

#endif // !_GENAM_H_
