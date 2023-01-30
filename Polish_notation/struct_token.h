#ifndef SRC_STRUCT_TOKEN_H_
#define SRC_STRUCT_TOKEN_H_

/* Struct Token */
/* types: numbers(0), brackets(1), functions(2), variables(3) */
/* rang for signs: unary(1), binary(2) */

/*
   "-" - "-" - binary
   "+" - "+" - binary
   "*" - "*" - binary
   "/" - "/" - binary
   "-" - "~" - unary
   "sin" - "s" - unary
   "cos" - "c" - unary
   "tan" - "T" - unary
   "ctg" - "C" - unary
   "sqrt" - "S" - unary
   "ln" - "l" - unary
 */
struct Token {
    int type;
    double number;
    char code;
    int priority;
};

struct Token create_num(double number);
struct Token create_brackets(char c);
struct Token create_var();
struct Token create_fun(char c);

#endif  // SRC_STRUCT_TOKEN_H_
