#ifndef _relpath_h_
#define _relpath_h_



typedef enum ForkNumber {
    MAIN_FORKNUMBER = 0,
    FSM_FORKNUM,
    INIT_FORKNUM,
} ForkNumber;

char* GetRelPath(int rnode, ForkNumber fn);


#endif // !_relpath_h_
