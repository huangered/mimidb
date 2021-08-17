#ifndef _global_h_
#define _global_h_

struct GlobalParams {
    int nsyms;   // 符号数
    int ntokens; // 终止符数
    int nvars;

    int nrules;
    int nstates;
};

static struct GlobalParams Params;

void ParamsInit(void);

#endif // !_global_h_
