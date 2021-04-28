#ifndef _offset_hpp_
#define _offset_hpp_

typedef unsigned int OffsetNumber;

#define OffsetNumberPrev(num)   ( num - 1 )
#define OffsetNumberNext(num)   ( num + 1 )

#define InvalidOffsetNumber     ((OffsetNumber)0)
#define FirstOffsetNumber       ((OffsetNumber)1)

#define OffsetIsValid(offset)	((offset) != InvalidOffsetNumber)

#endif // !_offset_h_
