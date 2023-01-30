#include "struct_token.h"
#include <string.h>

struct Token create_num(double number) {
    struct Token token;
    token.type = 0;
    token.number = number;
    token.code = '1';
    token.priority = -1;
    return token;
}

struct Token create_brackets(char c) {
    struct Token token;
    token.number = c;
    token.type = 1;
    token.code = c;
    token.priority = 0;
    return token;
}

struct Token create_var() {
    struct Token token;
    token.number = -2;
    token.priority = -1;
    token.type = 3;
    token.code = 'x';
    return token;
}

struct Token create_fun(char c) {
    struct Token token;
    token.number = -2;
    token.type = 2;
    token.code = c;
    if (strchr("*/", c) != NULL) {
        token.priority = 4;
    } else {
        token.priority = 3;
    }
    return token;
}
