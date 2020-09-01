#ifndef _BUF_H_
#define _BUF_H_

/*
zero is invalid
*/
typedef int Buffer;

#define INVALID_BUFFER  -1
#define BufferIsInvalid(buf)    ((buf) == INVALID_BUFFER)

#endif // !_BUFMGR_H_
