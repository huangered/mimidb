#ifndef _buildins_h_
#define _buildins_h_

#include "mimi.h"
#include "util/fmgr.h"

extern Datum int8cmp(FunctionCallInfo fcinfo);
extern Datum int16cmp(FunctionCallInfo fcinfo);
extern Datum int32cmp(FunctionCallInfo fcinfo);

#endif;
