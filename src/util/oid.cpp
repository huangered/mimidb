/*
* oid 相关函数
*/
#include "util/builtins.hpp"
#include "mimi.hpp"
Datum
oidcmp(FunctionCallInfo fcinfo) {
    Oid a = (Oid)fcinfo->args[0];
    Oid b = (Oid)fcinfo->args[1];

    return a - b;
}