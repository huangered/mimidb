#ifndef _RELPATH_H_
#define _RELPATH_H_

typedef enum ForkNumber {
    MAIN_FORKNUM = 0,
    FSM_FORKNUM,
    INIT_FORKNUM,
} ForkNumber;

char* GetRelPath(int rnode, ForkNumber fn);

#endif // !_relpath_h_
