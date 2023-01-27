#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1024
void simple_open(FILE *f);
void flag_n(FILE *f);
void flag_b(FILE *f);
void flag_e(FILE *f);
void flag_s(FILE *f);
void flag_t(FILE *f);
int main() {
  char str1[SIZE];
  char str2[SIZE];
  FILE *f;
  scanf("%s", str1);
  if (str1[0] == '-') {
    scanf("%s", str2);
    f = fopen(str2, "raw");
    if (!f) {
      printf("cat: %s:No such file or directory", str2);
      exit(1);
    } else {
      if (str1[1] == 'b') {
        flag_b(f);
      } else if (str1[1] == 'e') {
        flag_e(f);
      } else if (str1[1] == 'n') {
        flag_n(f);
      } else if (str1[1] == 's') {
        flag_s(f);
      } else if (str1[1] == 't') {
        flag_t(f);
      }
    }
    fclose(f);
  } else {
    f = fopen(str1, "raw");
    if (!f) {
      printf("cat: %s:No such file or directory", str2);
      exit(1);
    } else {
      simple_open(f);
    }
    fclose(f);
  }
  return 0;
}

void simple_open(FILE *f) {
  char c[SIZE];
  while (!feof(f)) {
    fgets(c, SIZE, f);
    printf("%s", c);
  }
}

void flag_n(FILE *f) {
  char c[SIZE];
  int k = 1;
  while (!feof(f)) {
    fgets(c, SIZE, f);
    printf("    %d %s", k, c);
    k += 1;
  }
}

void flag_b(FILE *f) {
  char c[SIZE];
  int k = 1;
  while (!feof(f)) {
    fgets(c, SIZE, f);
    if (c[0] == '\n') {
      printf("%s", c);
    } else {
      printf("    %d %s", k, c);
      k += 1;
    }
  }
}

void flag_t(FILE *f) {
  char c[SIZE];
  while (fgets(c, SIZE, f)) {
    int i = 0;
    while (c[i] != 0) {
      if (c[i] == ' ' && c[i + 1] == ' ' && c[i + 2] == ' ' &&
          c[i + 3] == ' ') {
        printf("^I");
        i += 4;
      } else {
        printf("%c", c[i]);
        i++;
      }
    }
  }
}

void flag_e(FILE *f) {
  char c[SIZE];
  while (fgets(c, SIZE, f)) {
    int i = 0;
    while (c[i] != 0) {
      if (c[i] == '\n') {
        printf("%s\n", "$");
        i++;
      } else {
        printf("%c", c[i]);
        i++;
      }
    }
  }
}

void flag_s(FILE *f) {
  char c[SIZE];
  int i = 0;
  while (fgets(c, SIZE, f)) {
    if (c[0] == '\n') {
      if (i == 0) {
        printf("%s", c);
        i = 1;
      }
    } else {
      printf("%s", c);
      i = 0;
    }
  }
}
