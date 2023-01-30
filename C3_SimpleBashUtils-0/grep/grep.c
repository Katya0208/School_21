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
void flag_l(FILE *f, char *arr, char *file_name);
void flag_n(FILE *f, char *arr);
int find(char *arr1, char *arr2);
void poisk(char *arr1, char *arr2);
int have_mask(char *arr1, char *arr2);

int main(int argc, char **argv) {
  int a = 0;
  while (argv[a + 1][0] == '-') {
    a++;
  }

  if (argv[1][1] == 'e') {
    int i;
    int search_i;
    int search_count = 0;

    int file_count = 0;
    char *search_list[argc];
    char *file_list[argc];
    char buffer[1024];
    FILE *fp;

    for (i = 1; i < argc; i++) {
      if (!strcmp(argv[i], "-e")) {
        search_list[search_count++] = argv[++i];
      } else {
        file_list[file_count++] = argv[i];
      }
    }

    if (search_count == 0) {
      printf("No search string provided.\n");
      return 1;
    }

    if (file_count == 0) {
      printf("No file provided.\n");
      return 1;
    }

    for (search_i = 0; search_i < search_count; search_i++) {
      for (i = 0; i < file_count; i++) {
        fp = fopen(file_list[i], "r");
        if (fp == NULL) {
          printf("Cannot open file %s\n", file_list[i]);
          continue;
        }

        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
          if (have_mask(search_list[search_i], buffer)) {
            printf("%s: ", file_list[i]);
          }
          poisk(search_list[search_i], buffer);
        }
        fclose(fp);
      }
    }
  } else {
    for (int i = 2 + a; i < argc; i++) {
      FILE *f;

      f = fopen(argv[i], "raw");
      if (!f) {
        printf("cat: %s:No such file or directory", argv[i]);
        continue;
      } else {
        if (a == 0) {
          simple_grep(f, argv[1 + a]);
        }
        if (argv[1][1] == 'l') {
          flag_l(f, argv[1 + a], argv[i]);
        } else if (argv[1][1] == 'i') {
          flag_i(f, argv[1 + a]);
        } else if (argv[1][1] == 'v') {
          flag_v(f, argv[1 + a]);
        } else if (argv[1][1] == 'c') {
          flag_c(f, argv[1 + a]);
        } else if (argv[1][1] == 'n') {
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
  while (fgets(c, SIZE, f)) {
    poisk(arr, c);
  }
}

void flag_i(FILE *f, char *arr) {
  char c[SIZE];

  while (fgets(c, SIZE, f)) {
    int i = 0;
    int n_c = strlen(c);
    for (i = 0; i < n_c; i++) {
      if (c[i] != 0) {
        c[i] = tolower(c[i]);
      }
    }
    int n_arr = strlen(arr);
    for (i = 0; i < n_arr; i++) {
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
  while (fgets(c, SIZE, f)) {
    k += have_mask(arr, c);
  }
  printf("%d\n", k);
  return k;
}

void flag_n(FILE *f, char *arr) {
  int n = 1;
  char c[SIZE];
  while (fgets(c, SIZE, f)) {
    if (have_mask(arr, c)) {
      printf("%d: ", n);
      poisk(arr, c);
    }
    n += 1;
  }
}

void flag_v(FILE *f, char *arr) {
  char c[SIZE];
  while (fgets(c, SIZE, f)) {
    if (have_mask(arr, c) == 0) {
      printf("%s", c);
    }
  }
}

void flag_l(FILE *f, char *arr, char *file_name) {
  char c[SIZE];
  while (fgets(c, SIZE, f)) {
    if (have_mask(arr, c)) {
      printf("%s\n", file_name);
      break;
    }
  }
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
      break;
    } else {
      startoffsed = ovector[1];

      for (int i = 0; i < rc; i++) {
        pcre_get_substring(arr2, ovector, rc, i, &substring);
        n += 1;
        pcre_free_substring(substring);
      }
    }
  }

  pcre_free(re);
  return n;
}