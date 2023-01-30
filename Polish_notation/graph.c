#include "read_string.h"
#include "struct_token.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define X 80
#define Y 25
#define PI 3.141592

void process_symbol(int *i, int n, char *str, struct Token *infix, int *count, int *flag);
int is_number(char c);
char *cut_number(const char *str, int start, int end);
void process_chars(int *i, char *str, struct Token *infix, int *count, int *flag);
void process_signs(int *i, char *str, struct Token *infix, int *count);
struct Token *transform_postfix(const struct Token *infix, int n, int *head);
double *calculate_array(struct Token *postfix, int n);
double calc(const struct Token *postfix, int n, int i);
void draw(double *array);
void fill(char **matrix);
void refill(char **matrix, double *array);
void paint(char **matrix);

int main() {
    // Read string from stdin
    int n;
    char *string = read_string(&n);

    // Initialization of tokens array (infix form)
    int tokens_counter = 0;  // Amount of tokens
    struct Token *tokens_infix = (struct Token *) malloc(n * sizeof(struct Token));

    int flag = 1;

    // Transform string into array of tokens
    int i = 0;
    while (i < n && flag) {
        process_symbol(&i, n, string, tokens_infix, &tokens_counter, &flag);
    }

    // If input was correct:
    if (flag) {
        // Transform infix into postfix notation
        int head;
        struct Token *tokens_postfix = transform_postfix(tokens_infix, tokens_counter, &head);

        if (tokens_postfix != NULL) {
            double *array = calculate_array(tokens_postfix, head);

            draw(array);
            free(tokens_postfix);
            free(array);
        } else {
            printf("Incorrect input\n");
        }
    } else {
        printf("Incorrect input\n");
    }

    free(string);
    free(tokens_infix);
    return 0;
}

void process_symbol(int *i, int n, char *str, struct Token *infix, int *count, int *flag) {
    if (is_number(*(str + *i))) {
        int start = *i;
        while (*i < n && is_number(*(str + *i)))
            *i += 1;
        char *number = cut_number(str, start, *i);

        // Check that number doesn`t start or end with "."
        if (number == NULL) {
            *flag = 0;
        }

        if (*flag) {
            double num = atof(number);
            infix[*count] = create_num(num);
            free(number);
            *count += 1;
        }
    } else if (*(str + *i) == '(' || *(str + *i) == ')') {
        infix[*count] = create_brackets(*(str + *i));
        *count += 1;
        *i += 1;
    } else if (*(str + *i) == 'x') {
        infix[*count] = create_var();
        *count += 1;
        *i += 1;
    } else if (*(str + *i) == ' ') {
        *i += 1;
    } else if (strchr("+-*/", *(str + *i)) != NULL) {
        process_signs(i, str, infix, count);
    } else {
        process_chars(i, str, infix, count, flag);
    }
}

// Check that character is a digit or a point
int is_number(char c) {
    int flag = 0;
    if (((int) c >= 48 && (int) c <= 57) || (int) c == 46) {
        flag = 1;
    }
    return flag;
}

// Cut number from string and return it
char *cut_number(const char *str, int start, int end) {
    char *number = (char *) calloc((end - start), sizeof(char));
    int points = 0;
    for (int i = 0; i < end - start; i++) {
        if (str[start + i] == '.') {
            points += 1;
        }
        number[i] = str[start + i];
    }
    if (number[end - start - 1] == '.' || number[0] == '.' || points > 1) {
        free(number);
        return NULL;
    }
    return number;
}

// Function for processing signs
void process_signs(int *i, char *str, struct Token *infix, int *count) {
    char c = *(str + *i);
    if (c == '-') {
        if (*i == 0 || str[*i - 1] == '(') {
            c = '~';
        }
    }
    infix[*count] = create_fun(c);
    *count += 1;
    *i += 1;
}

void process_chars(int *i, char *str, struct Token *infix, int *count, int *flag) {
    char *available = "sincotagsqrl";
    char *adress = str + *i;
    char c = *(str + *i);
    if (strchr(available, c) != NULL) {
        if (strstr(adress, "sin") == adress) {
            infix[*count] = create_fun('s');
            *count += 1;
            *i += 3;
        } else if (strstr(adress, "cos") == adress) {
            infix[*count] = create_fun('c');
            *count += 1;
            *i += 3;
        } else if (strstr(adress, "tan") == adress) {
            infix[*count] = create_fun('T');
            *count += 1;
            *i += 3;
        } else if (strstr(adress, "ctg") == adress) {
            infix[*count] = create_fun('C');
            *count += 1;
            *i += 3;
        } else if (strstr(adress, "sqrt") == adress) {
            infix[*count] = create_fun('S');
            *count += 1;
            *i += 4;
        } else if (strstr(adress, "ln") == adress) {
            infix[*count] = create_fun('l');
            *count += 1;
            *i += 2;
        } else {
            *flag = 0;
        }
    } else {
        *flag = 0;
    }
}

struct Token *transform_postfix(const struct Token *infix, int n, int *head) {
    struct Token *postfix = (struct Token *) malloc(n * sizeof(struct Token));
    *head = 0;

    int top = 0;
    struct Token *stack_post = (struct Token *) malloc(n * sizeof(struct Token));

    int flag = 1;
    for (int i = 0; i < n; i++) {
        struct Token token = infix[i];
        if (token.type == 0 || token.type == 3) {
            postfix[*head] = token;
            *head += 1;
        } else if (token.type == 2 && strchr("~scTCSl", token.code) != NULL) {
            stack_post[top] = token;
            top += 1;
        } else if (token.type == 1 && token.code == '(') {
            stack_post[top] = token;
            top += 1;
        } else if (token.type == 1 && token.code == ')') {
            while (top > 0 && stack_post[top - 1].code != '(') {
                postfix[*head] = stack_post[top - 1];
                top -= 1;
                *head += 1;
            }
            if (top == 0) {
                flag = 0;
            } else {
                top -= 1;
            }
        } else if (token.type == 2 && strchr("-+*/", token.code) != NULL) {
            while (top > 0 && (strchr("~scTCSl", stack_post[top - 1].code) != NULL ||
                               stack_post[top - 1].priority >= token.priority)) {
                postfix[*head] = stack_post[top - 1];
                top -= 1;
                *head += 1;
            }
            stack_post[top] = token;
            top += 1;
        }
        if (!flag) {
            break;
        }
    }

    while (top > 0 && flag) {
        struct Token token = stack_post[top - 1];
        if (token.type == 2 && strchr("+-*/scTC~Sl", token.code) !=  NULL) {
            postfix[*head] = stack_post[top - 1];
            top -= 1;
            *head += 1;
        } else {
            flag = 0;
            break;
        }
    }

    if (!flag) {
        free(stack_post);
        free(postfix);
        return NULL;
    }

    free(stack_post);
    return postfix;
}

double *calculate_array(struct Token *postfix, int n) {
    double *array = (double *) malloc (X * sizeof(double));

    for (int i = 0; i < X; i++) {
        array[i] = calc(postfix, n, i);
    }
    return array;
}

double calc(const struct Token *postfix, int n, int i) {
    double x = i * 4 * PI / (X - 1);
    int top = 0;
    double *res = (double *) malloc(n * sizeof(double));
    for (int j = 0; j < n; j++) {
        struct Token token = postfix[j];
        if (token.type == 0) {
            res[top] = token.number;
            top += 1;
        } else if (token.type == 3) {
            res[top] = x;
            top += 1;
        } else if (token.code == '~') {
            res[top - 1] = 0 - res[top - 1];
        } else if (token.code == 's') {
            res[top - 1] = sin(res[top - 1]);
        } else if (token.code == 'c') {
            res[top - 1] = cos(res[top - 1]);
        } else if (token.code == 'T') {
            res[top - 1] = tan(res[top - 1]);
        } else if (token.code == 'C') {
            res[top - 1] = 1 / tan(res[top - 1]);
        } else if (token.code == 'S') {
            res[top - 1] = sqrt(res[top - 1]);
        } else if (token.code == 'l') {
            res[top - 1] = log(res[top - 1]);
        } else if (token.code == '-') {
            double tmp = res[top - 2] - res[top - 1];
            top -= 1;
            res[top - 1] = tmp;
        } else if (token.code == '+') {
            double tmp = res[top - 2] + res[top - 1];
            top -= 1;
            res[top - 1] = tmp;
        } else if (token.code == '*') {
            double tmp = res[top - 2] * res[top - 1];
            top -= 1;
            res[top - 1] = tmp;
        } else if (token.code == '/') {
            double tmp = res[top - 2] / res[top - 1];
            top -= 1;
            res[top - 1] = tmp;
        }
    }
    double result = res[0];
    free(res);
    return result;
}

void draw(double *array) {
    char **matrix = (char **)malloc(Y * sizeof(char *));
    for (int i = 0; i < Y; i++) {
        matrix[i] = (char *)malloc(X * sizeof(char));
    }
    fill(matrix);

    for (int i = 0; i < X; i++) {
        array[i] = (array[i] + 1) * 12;
    }
    refill(matrix, array);
    paint(matrix);
    for (int i = 0; i < Y; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void fill(char **matrix) {
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            matrix[i][j] = '.';
        }
    }
}

void refill(char **matrix, double *array) {
    for (int i = 0; i < X; i++) {
        double tmp = round(array[i]);
        int y = (int) tmp;
        if ((y < 25) && (y >= 0)) {
            matrix[y][i] = '*';
        }
    }
}

void paint(char **matrix) {
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

