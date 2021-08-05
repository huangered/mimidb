#include "c_util/cstr.h"
#include <stdlib.h>
#include <string.h>

Str*
str_new(char* buf, int size) {
    Str* s = malloc(sizeof(Str));
    s->len = s->maxlen = strlen(buf);
    s->value           = malloc((s->len + 1) * sizeof(char));
    strncpy(s->value, buf, size);
    *(s->value + s->len) = '\0';
    return s;
}

void
str_free(Str* s) {
    free(s->value);
    free(s);
}