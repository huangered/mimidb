#ifndef _offset_hpp_
#define _offset_hpp_

typedef unsigned int OffsetNumber;

const OffsetNumber InvalidOffsetNumber{ 0 };
const OffsetNumber FirstOffsetNumber{ 1 };

inline OffsetNumber OffsetNumberPrev(OffsetNumber num) {
	return  num - 1;
}

inline OffsetNumber  OffsetNumberNext(OffsetNumber num) {
	return  num + 1;
}

inline bool OffsetIsValid(OffsetNumber offset) {
	return 	offset != InvalidOffsetNumber;
}

#endif // !_offset_h_
