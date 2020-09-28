#ifndef _item_id_h_
#define _item_id_h_

typedef struct ItemIdData {
    unsigned lp_off : 15;
    unsigned lp_flags : 2;
    unsigned lp_len : 15;
} ItemIdData;

typedef ItemIdData* ItemId;

#define LP_UNUSED   0
#define LP_NORMAL   1
#define LP_REDIRECT 2   /* heap of tuple 重定向标识 */
#define LP_DEAD     3

typedef void* Item;

#endif