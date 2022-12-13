#include "mimi.h"
#include "util/memutils.h"

#define ALLOC_MINBITS          3
#define ALLOCSET_NUM_FREELISTS 11

#define ALLOC_BLOCKHDRSZ MAXALIGN(sizeof(AllocBlockData))
#define ALLOC_CHUNKHDRSZ MAXALIGN(sizeof(AllocChunkData))

typedef struct AllocSetContext* AllocSet;
typedef struct AllocBlockData* AllocBlock;
typedef struct AllocChunkData* AllocChunk;

typedef void* AllocPointer;

typedef struct AllocBlockData {
    AllocSet aset;
    AllocBlock prev;
    AllocBlock next;
    char* freeptr;
    char* endptr;
} AllocBlockData;

typedef struct AllocChunkData {
    void* aset;
    Size size;
} AllocChunkData;

typedef struct AllocSetContext {
    MemoryContextData header;
    AllocBlock blocks;
    AllocChunk freelist[ALLOCSET_NUM_FREELISTS];

    Size initBlockSize;
    Size maxBlockSize;
    Size nextBlockSize;
    Size allocChunkLimit;
} AllocSetContext;

#define AllocPointerGetChunk(ptr) ((AllocChunk)(((char*)(ptr)) - ALLOC_CHUNKHDRSZ))
#define AllocChunkGetPointer(chk) ((AllocPointer)(((char*)(chk)) + ALLOC_CHUNKHDRSZ))

static void* AllocSetAlloc(MemoryContext context, Size size);
static void AllocSetFree(MemoryContext context, void* pointer);
static void AllocSetDelete(MemoryContext context);
static MemoryContextMethods AllocSetMethods = { AllocSetAlloc, AllocSetFree, AllocSetDelete };

/* ----------
 * Debug macros
 * ----------
 */
#ifdef HAVE_ALLOCINFO
#define AllocFreeInfo(_cxt, _chunk)                                                                                    \
    fprintf(stderr, "AllocFree: %s: %p, %d\n", (_cxt)->header.name, (_chunk), (_chunk)->size)
#define AllocAllocInfo(_cxt, _chunk)                                                                                   \
    fprintf(stderr, "AllocAlloc: %s: %p, %d\n", (_cxt)->header.name, (_chunk), (_chunk)->size)
#else
#define AllocFreeInfo(_cxt, _chunk)
#define AllocAllocInfo(_cxt, _chunk)
#endif

static inline int
AllocSetFreeIndex(Size size) {
    int idx;
    if (size <= 8) {
        idx = 0;
    } else if (size <= 16) {
        idx = 1;
    } else if (size <= 32) {
        idx = 2;
    } else if (size <= 64) {
        idx = 3;
    } else if (size <= 128) {
        idx = 4;
    } else if (size <= 256) {
        idx = 5;
    } else if (size <= 512) {
        idx = 6;
    } else if (size <= 1024) {
        idx = 7;
    } else if (size <= 2048) {
        idx = 8;
    } else if (size <= 4096) {
        idx = 9;
    } else if (size <= 8192) {
        idx = 10;
    } else if (size <= 16384) {
        idx = 11;
    }

    return idx;
}

MemoryContext
AllocSetContextCreate(MemoryContext parent, const char* name, Size minContextSize, Size initBlockSize,
                      Size maxBlockSize) {
    AllocSet set;

    set = (AllocSet)MemoryContextCreate(1, sizeof(AllocSetContext), &AllocSetMethods, parent, name);

    // initBlockSize = MAXALIGN(initBlockSize);
    if (initBlockSize < 1024)
        initBlockSize = 1024;
    // maxBlockSize = MAXALIGN(maxBlockSize);
    if (maxBlockSize < initBlockSize)
        maxBlockSize = initBlockSize;
    set->initBlockSize = initBlockSize;
    set->maxBlockSize  = maxBlockSize;
    set->nextBlockSize = initBlockSize;

    set->allocChunkLimit = 1024;

    if (minContextSize > ALLOC_BLOCKHDRSZ + ALLOC_CHUNKHDRSZ) {
        Size blksize = minContextSize;
        AllocBlock block;

        block = (AllocBlock)malloc(blksize);
        if (block == NULL) {
            // error他
        }
        block->aset    = set;
        block->freeptr = ((char*)block) + ALLOC_BLOCKHDRSZ;
        block->endptr  = ((char*)block) + blksize;
        block->prev    = NULL;
        block->next    = set->blocks;
        if (block->next)
            block->next->prev = block;
        set->blocks = block;
        // set->keeper = block;
    }

    return (MemoryContext)set;
}

void*
AllocSetAlloc(MemoryContext context, Size size) {
    AllocSet set = (AllocSet)context;
    AllocBlock block;
    AllocChunk chunk;
    int fidx;
    Size chunk_size;
    Size blksize;

    /*
     * 如果超过了最大值，申请一个完整的块
     */
    if (size > set->allocChunkLimit) {
        chunk_size = MAXALIGN(size);
        blksize    = chunk_size + ALLOC_BLOCKHDRSZ + ALLOC_CHUNKHDRSZ;
        block      = (AllocBlock)malloc(blksize);
        if (block == NULL)
            return NULL;
        block->aset    = set;
        block->freeptr = block->endptr = ((char*)block) + blksize;

        chunk       = (AllocChunk)(((char*)block) + ALLOC_BLOCKHDRSZ);
        chunk->aset = set;
        chunk->size = chunk_size;

        if (set->blocks != NULL) {
            block->prev = set->blocks;
            block->next = set->blocks->next;
            if (block->next)
                block->next->prev = block;
            set->blocks->next = block;
        } else {
            block->prev = NULL;
            block->next = NULL;
            set->blocks = block;
        }

        AllocAllocInfo(set, chunk);

        return AllocChunkGetPointer(chunk);
    }

    /*
     * Request is small, and find in the freelist, remove it from freelist
     */
    fidx  = AllocSetFreeIndex(size);
    chunk = set->freelist[fidx];
    if (chunk != NULL) {
        assert(chunk->size >= size);

        set->freelist[fidx] = (AllocChunk)chunk->aset;

        chunk->aset = (void*)set;

        return AllocChunkGetPointer(chunk);
    }

    chunk_size = (1 << ALLOC_MINBITS) << fidx;
    assert(chunk_size >= size);
    if ((block = set->blocks) != NULL) {
        Size availspace = block->endptr - block->freeptr;

        if (availspace < (chunk_size + ALLOC_CHUNKHDRSZ)) {
            /*
             * 现存的block里空间不足，把它放到freelist里
             */
            while (availspace >= ((1 << ALLOC_MINBITS) + ALLOC_CHUNKHDRSZ)) {
                Size availchunk = availspace - ALLOC_CHUNKHDRSZ;
                int a_fidx      = AllocSetFreeIndex(availchunk);

                if (availchunk != ((Size)1 << (a_fidx + ALLOC_MINBITS))) {
                    a_fidx--;

                    assert(a_fidx >= 0);
                    availchunk = ((Size)1 << (a_fidx + ALLOC_MINBITS));
                }

                chunk = (AllocChunk)(block->freeptr);

                block->freeptr += (availchunk + ALLOC_CHUNKHDRSZ);
                availspace -= (availchunk + ALLOC_CHUNKHDRSZ);

                chunk->size = availchunk;

                chunk->aset           = (void*)set->freelist[a_fidx];
                set->freelist[a_fidx] = chunk;
            }
            /* 表明我们要建一个新block */
            block = NULL;
        }
    }
    /*
     * time to create a new regular block?
     */
    if (block == NULL) {
        Size required_size;

        blksize = set->nextBlockSize;
        set->nextBlockSize <<= 1;
        if (set->nextBlockSize > set->maxBlockSize)
            set->nextBlockSize = set->maxBlockSize;

        required_size = chunk_size + ALLOC_BLOCKHDRSZ + ALLOC_CHUNKHDRSZ;
        while (blksize < required_size)
            blksize <<= 1;

        block = (AllocBlock)malloc(blksize);

        while (block == NULL) {
            block = (AllocBlock)malloc(blksize);
        }

        if (block == NULL)
            return NULL;

        block->aset    = set;
        block->freeptr = ((char*)block) + ALLOC_BLOCKHDRSZ;
        block->endptr  = ((char*)block) + blksize;

        // keeper

        block->prev = NULL;
        block->next = set->blocks;
        if (block->next)
            block->next->prev = block;
        set->blocks = block;
    }

    /*
     * OK, do the allocation
     */
    chunk = (AllocChunk)(block->freeptr);
    block->freeptr += (chunk_size + ALLOC_CHUNKHDRSZ);
    assert(block->freeptr <= block->endptr);

    chunk->aset = (void*)set;
    chunk->size = chunk_size;

    return AllocChunkGetPointer(chunk);
}

void
AllocSetFree(MemoryContext context, void* pointer) {
    AllocSet set     = (AllocSet)context;
    AllocChunk chunk = AllocPointerGetChunk(pointer);

    AllocFreeInfo(set, chunk);

    if (chunk->size > set->allocChunkLimit) {
        // todo: don't know now
    } else {
        int fidx    = AllocSetFreeIndex(chunk->size);
        chunk->aset = (void*)set->freelist[fidx];

        set->freelist[fidx] = chunk;
    }
}

void
AllocSetDelete(MemoryContext context) {
    AllocSet set     = (AllocSet)context;
    AllocBlock block = set->blocks;

    set->blocks = NULL;
    // set->keeper =NULL;

    while (block != NULL) {
        AllocBlock next = block->next;

        free(block);
        block = next;
    }
}