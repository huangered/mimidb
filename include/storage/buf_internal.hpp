#ifndef _buf_internal_hpp_
#define _buf_internal_hpp_

#include "mimi.hpp"
#include "access/relcache.hpp"
#include "storage/block.hpp"
#include "storage/page.hpp"
#include "storage/buf.hpp"
#include "util/hashmap.hpp"

typedef struct buftag {
    RelFileNode rnode;
    ForkNumber forkNum;
    BlockNumber blockNum;

    int
    hash() const {
        return rnode.relNode * 17 * 17 + forkNum * 17 + blockNum;
    }

    friend bool
    operator==(const buftag& l, const buftag& r) {
        return l.rnode == r.rnode && l.forkNum == r.forkNum && l.blockNum == r.blockNum;
    }

    friend bool
    operator!=(const buftag& l, const buftag& r) {
        return !(l == r);
    }

} BufferTag;

#define BUFFERTAG_EQUAL(a, b) ((a).rnode == (b).rnode && (a).forkNum == (b).forkNum && (a).blockNum == (b).blockNum)

struct BufferDesc {
    BufferTag tag;
    int buf_id;
    // the buf state, include ref_count;
    int refcnt;
    // the buf is updated.
    bool dirty;
    int freeNext;
};

#endif
