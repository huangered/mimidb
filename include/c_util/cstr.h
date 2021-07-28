#ifndef _c_str_h_

typedef struct str {
    int len;
    int maxlen;
    char* value;
} Str;

Str* str_new(char* buf, int size);
void str_free(Str* s);

#define _c_str_h_
#endif // !_c_str_h_
