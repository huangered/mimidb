#ifndef _buf_hpp_
#define _buf_hpp_

/*
zero is invalid, the index of shared buffer is [1..NBuffers]
*/
typedef int Buffer;

#define INVALID_BUFFER          0
#define BufferIsInvalid(buf)    ((buf) == INVALID_BUFFER)
#define BufferIsValid(buf)      ((buf) != INVALID_BUFFER)

#endif // !_BUFMGR_H_
