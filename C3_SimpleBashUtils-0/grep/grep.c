#include <ctype.h>
#include <dirent.h>
#include <pcre.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1024
void simple_grep(FILE *f, char *arr);
void flag_e(FILE *f, char *arr);
void flag_i(FILE *f, char *arr);
void flag_v(FILE *f, char *arr);
int flag_c(FILE *f, char *arr);
void flag_l(char *r, char *arr);
void flag_n(FILE *f, char *arr);
int find(char *arr1, char *arr2);
void poisk(char *arr1, char *arr2);
int have_mask(char *arr1, char *arr2);

int main(int argc, char **argv) {
  // ./a.out -n ololo file1 file2 ...
  int a = 0;
  while (argv[a + 1][0] == '-') {
    a++;
  }
  if (argv[1][1] == 'l') {
    flag_l(argv[3], argv[2]);
  } else {
    for (int i = 2 + a; i < argc; i++) {
      FILE *f;

      f = fopen(argv[i], "raw");
      if (!f) {
        printf("cat: %s:No such file or directory", argv[i]);
        continue;
      } else {
        if (a == 0) {
          simple_grep(f, argv[1 + a]);  // f - файл, argv[1 + a] - строка,
                                        // которую нужно найти
        }
        if (argv[1][1] == 'e') {
          // flag_e(f);
        } else if (argv[1][1] == 'i') {
          flag_i(f, argv[1 + a]);  // готов
        } else if (argv[1][1] == 'v') {
          flag_v(f, argv[1 + a]);  // готов
        } else if (argv[1][1] == 'c') {
          flag_c(f, argv[1 + a]);  // готов
        }
        // else if (argv[1][1] == 'l') {
        //   flag_l(argv[3 + a], argv[2 + a]);
        // }
        else if (argv[1][1] == 'n') {  // готов
          flag_n(f, argv[1 + a]);
        }
      }
      fclose(f);
    }
  }
  return 0;
}

void simple_grep(FILE *f, char *arr) {
  char c[SIZE];
  while (!feof(f)) {
    fgets(c, SIZE, f);
    poisk(arr, c);
  }
}

void flag_i(FILE *f, char *arr) {
  char c[SIZE];

  while (fgets(c, SIZE, f)) {
    int i = 0;
    for (i = 0; i < strlen(c); i++) {
      if (c[i] != 0) {
        c[i] = tolower(c[i]);
      }
    }
    for (i = 0; i < strlen(arr); i++) {
      if (arr[i] != 0) {
        arr[i] = tolower(arr[i]);
      }
    }
    poisk(arr, c);
  }
}

int flag_c(FILE *f, char *arr) {
  int k = 0;
  char c[SIZE];
  while (!feof(f)) {
    fgets(c, SIZE, f);
    k += have_mask(arr, c);
  }
  printf("%d", k);
}

void flag_n(FILE *f, char *arr) {
  int n = 1;
  char c[SIZE];
  while (!feof(f)) {
    fgets(c, SIZE, f);
    if (have_mask(arr, c)) {
      printf("%d: ", n);
      poisk(arr, c);
    }
    n += 1;
  }
}

void flag_v(FILE *f, char *arr) {
  char c[SIZE];
  while (!feof(f)) {
    fgets(c, SIZE, f);
    if (have_mask(arr, c) == 0) {
      printf("%s", c);
    }
  }
}

void flag_l(char *r, char *arr) {  // не файл, а строка с расширением

  DIR *dir = opendir(".");
  if (dir == NULL) {
    printf("ERROR");
  }
  struct dirent *entity;
  entity = readdir(dir);
  while (entity != NULL) {
    if (have_mask(r, entity->d_name)) {
      FILE *f;
      f = fopen(entity->d_name, "raw");
      char c[SIZE];
      while (!feof(f)) {
        fgets(c, SIZE, f);
        if (have_mask(arr, c) == 1) {
          printf("%s\n", entity->d_name);
        }
      }
    }
    // printf("\n");
    entity = readdir(dir);
  }
  closedir(dir);
}

void poisk(char *arr1, char *arr2) {
  pcre *re;
  const char *error;
  int erroffset;
  int rc;
  int ovector[30];
  re = pcre_compile(arr1, 0, &error, &erroffset, NULL);
  int startoffsed = 0;

  rc = pcre_exec(re, NULL, arr2, strlen(arr2), startoffsed, 0, ovector, 30);

  startoffsed = ovector[1];

  for (int i = 0; i < rc; i++) {
    printf("%s", arr2);
  }

  pcre_free(re);
}

int have_mask(char *arr1, char *arr2) {
  pcre *re;
  const char *error;
  int erroffset;
  int rc;
  int ovector[30];
  const char *substring;

  re = pcre_compile(arr1, 0, &error, &erroffset, NULL);
  int startoffsed = 0;
  int n = 0;

  while (1) {
    rc = pcre_exec(re, NULL, arr2, strlen(arr2), startoffsed, 0, ovector, 30);

    if (rc == PCRE_ERROR_NOMATCH) {
      break;
    } else if (rc < -1) {
      // fprintf(stderr, "error %d from regex\n", rc);
      break;
    } else {
      startoffsed = ovector[1];

      for (int i = 0; i < rc; i++) {
        pcre_get_substring(arr2, ovector, rc, i, &substring);
        // printf("%d: %s\n", i, substring);
        n += 1;
        pcre_free_substring(substring);
      }
    }
  }

  pcre_free(re);
  return n;
}