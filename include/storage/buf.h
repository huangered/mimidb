#ifndef _buf_hpp_
#define _buf_hpp_

#include "access/relpath.h"
#include "storage/block.h"
#include "storage/relfilenode.h"

/*
 * zero is invalid, the index of shared buffer is [1..NBuffers]
 */
typedef int Buffer;

#define INVALID_BUFFER 0
/*
 * true if buf is invalie
 */
#define BufferIsInvalid(buf) ((buf) == INVALID_BUFFER)

/*
 * true if buf is local
 */
#define BufferIsLocal(buf) ((buf) < 0)

#endif // !_BUFMGR_H_
