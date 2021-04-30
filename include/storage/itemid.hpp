#ifndef _item_id_hpp_
#define _item_id_hpp_

struct ItemIdData {
    unsigned lp_off : 15;
    unsigned lp_flags : 2;
    unsigned lp_len : 15;
};

typedef ItemIdData* ItemId;

enum LpFlag {
    LP_UNUSED = 0,
    LP_NORMAL = 1,
    LP_REDIRECT = 2,   /* heap of tuple 重定向标识 */
    LP_DEAD = 3,
};

typedef void* Item;

inline void ItemIdSetNormal(ItemId itemId, int offset, int len) {
    itemId->lp_flags = LP_NORMAL;
    itemId->lp_off = offset;
    itemId->lp_len = len;
}

inline void ItemIdSetDead(ItemId itemId) {
    itemId->lp_flags = LP_DEAD;
}

#endif