#ifndef _item_id_h_
#define _item_id_h_

typedef struct ItemIdData {
    unsigned lp_off : 15;
    unsigned lp_flags : 2;
    unsigned lp_fen : 15;
} ItemIdData;

typedef ItemIdData* ItemId;

typedef void* Item;

#endif