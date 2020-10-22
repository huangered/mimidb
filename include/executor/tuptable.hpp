#ifndef _tuptable_h_
#define _tuptable_h_

typedef struct TupleSlotDesc {
    int tts_tid;    // tuple's tid
    int key;
    int value;
} TupleSlotDesc;


#endif