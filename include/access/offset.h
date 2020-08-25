#ifndef _offset_h_
#define _offset_h_

typedef unsigned int OffsetNumber;

#define OffsetNumberPrev(num)   ( num - 1 )
#define OffsetNumberNext(num)   ( num + 1 )

#define InvalidOffsetNumber     ((OffsetNumber)0)
#define FirstOffsetNumber       ((OffsetNumber)1)

#endif // !_offset_h_
