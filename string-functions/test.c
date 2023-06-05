#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

// strerror
START_TEST(all_std_errors) {
  for (int i = -1000; i < 150; i++) {
    char *got = s21_strerror(i);
    char *expected = strerror(i);
    ck_assert_str_eq(got, expected);
  }
}
END_TEST

START_TEST(negative_err_code) {
  const char *got = s21_strerror(-1);
  char *expected = strerror(-1);
  ck_assert_str_eq(got, expected);
}
END_TEST

// strlen

START_TEST(test_strlen_empty_string) {
  const char *str = "";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(test_strlen_short_string) {
  const char *str = "Hello";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(test_strlen_long_string) {
  const char *str =
      "This is a really long string that should test the performance of the "
      "s21_strlen function.";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(test_strlen_string_with_null_character) {
  const char *str = "This string contains a null character: \0";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(test_strlen_string_with_newline_character) {
  const char *str = "This string contains a newline character: \n";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(test_strlen_string_with_tab_character) {
  const char *str = "This string contains a tab character: \t";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(test_strlen_string_with_multiple_spaces) {
  const char *str = "   This string has multiple spaces before the text.";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

// strcmp

START_TEST(test_s21_strcmp_equal_strings) {
  const char *str1 = "Hello world";
  const char *str2 = "Hello world";
  ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
}
END_TEST

START_TEST(test_s21_strcmp_different_strings) {
  const char *str1 = "Hello world";
  const char *str2 = "Goodbye";
  ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
}
END_TEST

START_TEST(test_s21_strcmp_one_empty_string) {
  const char *str1 = "";
  const char *str2 = "Hello";
  ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
}
END_TEST

START_TEST(test_s21_strcmp_both_empty_strings) {
  const char *str1 = "";
  const char *str2 = "";
  ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
}
END_TEST

START_TEST(test_s21_strcmp_case_sensitive) {
  const char *str1 = "hello";
  const char *str2 = "Hello";
  ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
}
END_TEST

START_TEST(test_s21_strcmp_special_characters) {
  const char *str1 = "\n\t\r";
  const char *str2 = "\n\t\r";
  ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
}
END_TEST

START_TEST(test_s21_strcmp_non_ascii_characters) {
  const char *str1 = "Привет";
  const char *str2 = "Пока";
  ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
}
END_TEST

// strcpy

START_TEST(test_strcpy) {
  char src[] = "Hello";
  char dest[6];

  strcpy(dest, src);
  ck_assert_str_eq(dest, "Hello");

  s21_strcpy(dest, src);
  ck_assert_str_eq(dest, "Hello");
}
END_TEST

START_TEST(test_strcpy_empty_src) {
  char src[] = "";
  char dest[6];

  strcpy(dest, src);
  ck_assert_str_eq(dest, "");

  s21_strcpy(dest, src);
  ck_assert_str_eq(dest, "");
}
END_TEST

START_TEST(test_strcpy_empty_string) {
  char src[] = "";
  char dest1[20];
  char dest2[20];

  strcpy(dest1, src);
  s21_strcpy(dest2, src);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strcpy_dest_larger_than_src) {
  char src[] = "Hello";
  char dest[10] = "Goodbye";

  strcpy(dest, src);
  ck_assert_str_eq(dest, "Hello");

  s21_strcpy(dest, src);
  ck_assert_str_eq(dest, "Hello");
}
END_TEST

START_TEST(test_strcpy_dest_same_as_src) {
  char src[] = "Hello";
  char dest[] = "Hello";

  strcpy(dest, src);
  ck_assert_str_eq(dest, "Hello");

  s21_strcpy(dest, src);
  ck_assert_str_eq(dest, "Hello");
}
END_TEST

START_TEST(test_strcpy_return_value) {
  char src[] = "Hello";
  char dest[6];

  char *ret1 = strcpy(dest, src);
  char *ret2 = s21_strcpy(dest, src);

  ck_assert_ptr_eq(ret1, dest);
  ck_assert_ptr_eq(ret2, dest);
}
END_TEST

START_TEST(test_strcpy_with_null) {
  char src[] = "Hello";
  char dest[6] = {'\0'};

  strcpy(dest, src);
  ck_assert_str_eq(dest, "Hello");

  s21_strcpy(dest, src);
  ck_assert_str_eq(dest, "Hello");
}
END_TEST

// strcat

START_TEST(test_strcat_empty_strings) {
  char dest[20] = "";
  const char *src = "";
  strcat(dest, src);

  char result[20] = "";
  s21_strcat(result, src);

  ck_assert_str_eq(dest, result);
}
END_TEST

START_TEST(test_strcat_src_empty) {
  char dest[20] = "Hello";
  const char *src = "";
  strcat(dest, src);

  char result[20] = "Hello";
  s21_strcat(result, src);

  ck_assert_str_eq(dest, result);
}
END_TEST

START_TEST(test_strcat_dest_empty) {
  char dest[20] = "";
  const char *src = "World!";
  strcat(dest, src);

  char result[20] = "";
  s21_strcat(result, src);

  ck_assert_str_eq(dest, result);
}
END_TEST

START_TEST(test_strcat_normal_strings) {
  char dest[20] = "Hello";
  const char *src = " World!";
  strcat(dest, src);

  char result[20] = "Hello";
  s21_strcat(result, src);

  ck_assert_str_eq(dest, result);
}
END_TEST

START_TEST(test_strcat_any_letters_with_register) {
  char src[] = "asdfj  asdf aisdfjaiushdfASD SAD asDSad ASDAsdwqqeAS";
  char res[5 + 53] = "Hello";
  char expected[5 + 53] = "Hello";

  s21_strcat(res, src);
  strcat(expected, src);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_strcat_dest_larger_than_src) {
  char dest[10] = "Hello";
  const char *src = "!";
  strcat(dest, src);

  char result[10] = "Hello";
  s21_strcat(result, src);

  ck_assert_str_eq(dest, result);
}
END_TEST

START_TEST(test_strcat_both_large_strings) {
  char dest[40] = "This is a";
  const char *src = " long string.";
  strcat(dest, src);

  char result[40] = "This is a";
  s21_strcat(result, src);

  ck_assert_str_eq(dest, result);
}
END_TEST

// memchr

START_TEST(test_s21_memchr_match) {
  char s[] = "Hello, world!";
  char *result1 = memchr(s, 'w', strlen(s));
  char *result2 = s21_memchr(s, 'w', strlen(s));
  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_memchr_no_match) {
  char s[] = "Hello, world!";
  char *result1 = memchr(s, 'z', strlen(s));
  char *result2 = s21_memchr(s, 'z', strlen(s));
  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_memchr_first_char) {
  char s[] = "Hello, world!";
  char *result1 = memchr(s, 'H', strlen(s));
  char *result2 = s21_memchr(s, 'H', strlen(s));
  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_memchr_last_char) {
  char s[] = "Hello, world!";
  char *result1 = memchr(s, '!', strlen(s));
  char *result2 = s21_memchr(s, '!', strlen(s));
  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_memchr_zero_length) {
  char s[] = "Hello, world!";
  char *result1 = memchr(s, 'H', 0);
  char *result2 = s21_memchr(s, 'H', 0);
  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_memchr_null_pointer) {
  char *s = NULL;
  char *result1 = memchr(s, 'H', 0);
  char *result2 = s21_memchr(s, 'H', 0);
  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_memchr_match_part_of_string) {
  char s[] = "Hello, world!";
  char *result1 = memchr(s, 'o', 5);
  char *result2 = s21_memchr(s, 'o', 5);
  ck_assert_ptr_eq(result1, result2);
}
END_TEST

// memcmp

START_TEST(test_memcmp_empty_arrays) {
  int expected = memcmp("", "", 0);
  int result = s21_memcmp("", "", 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_memcmp_equal_arrays) {
  int expected = memcmp("abcd", "abcd", 4);
  int result = s21_memcmp("abcd", "abcd", 4);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_memcmp_different_arrays) {
  int expected = memcmp("abcd", "abce", 4);
  int result = s21_memcmp("abcd", "abce", 4);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_memcmp_different_lengths_1) {
  int expected = memcmp("abc", "abcd", 3);
  int result = s21_memcmp("abc", "abcd", 3);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_memcmp_different_lengths_2) {
  int expected = memcmp("abcd", "abc", 3);
  int result = s21_memcmp("abcd", "abc", 3);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_memcmp_compare_digits) {
  int expected = memcmp("1234", "1244", 4);
  int result = s21_memcmp("1234", "1244", 4);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_memcmp_compare_digits_and_letters) {
  int expected = memcmp("a12", "b11", 3);
  int result = s21_memcmp("a12", "b11", 3);
  ck_assert_int_eq(result, expected);
}
END_TEST

// memcpy

START_TEST(test_aligned_copy) {
  int src[] = {1, 2, 3, 4, 5};
  int dest[5];
  size_t n = 5 * sizeof(int);

  memcpy(dest, src, n);
  s21_memcpy(dest, src, n);

  ck_assert_mem_eq(dest, src, n);
}
END_TEST

START_TEST(empty_array_test) {
  char src[] = "";
  s21_size_t kByte = 0;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(single_char_test) {
  char src[] = "x";
  s21_size_t kByte = 1;
  char res[kByte + 8];
  char expected[kByte + 8];
  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

// тестирование копирования нескольких блоков памяти
START_TEST(buffer_size_test) {
  char src[] = "this is a test";
  s21_size_t kByte = sizeof(src);
  char res[kByte + 8];
  char expected[kByte + 8];
  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

// тестирование копирования из одной области памяти в другую
START_TEST(large_array_test) {
  char src[] = "this is a very large array";
  s21_size_t kByte = 10;
  char res[kByte + 8];
  char expected[kByte + 8];
  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

// тестирование копирования в область памяти, не достаточную для хранения данных
START_TEST(null_char_test) {
  char src[] = "this\0is\0a\0test";
  s21_size_t kByte = sizeof(src);
  char res[kByte + 8];
  char expected[kByte + 8];
  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(zero_test_string_with_register) {
  char src[] = "I hate memcmp";
  s21_size_t kByte = 0;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

// memmove

START_TEST(empty_dest_and_src) {
  char src[] = "abc";
  char src2[] = "abc";
  s21_size_t copy_kByte = 0;
  char *res = src;
  char *expected = src2;
  s21_size_t check_kByte = 0;

  s21_memmove(res, src, copy_kByte);
  memmove(expected, src2, copy_kByte);

  ck_assert_mem_eq(res, expected, check_kByte);
}
END_TEST

START_TEST(empty_dest) {
  char src[] = "1234567890";
  char src2[] = "1234567890";
  s21_size_t copy_kByte = 6;
  char res[11] = "";
  char expected[11] = "";
  s21_size_t check_kByte = 6;

  s21_memmove(res, src, copy_kByte);
  memmove(expected, src2, copy_kByte);

  ck_assert_mem_eq(res, expected, check_kByte);
}
END_TEST

START_TEST(empty_src) {
  char src[] = "";
  char src2[] = "";
  s21_size_t copy_kByte = 0;
  char res[] = "this is a test";
  char expected[] = "this is a test";
  s21_size_t check_kByte = 0;

  s21_memmove(res, src, copy_kByte);
  memmove(expected, src2, copy_kByte);

  ck_assert_mem_eq(res, expected, check_kByte);
}
END_TEST

START_TEST(write_in_left) {
  char src[200] = "Hate";
  char src2[200] = "Hate";
  s21_size_t copy_kByte = 4;

  char res[200] = "i hate memcmp";
  char expected[200] = "i hate memcmp";
  s21_size_t check_kByte = 17;

  s21_memmove(res, src, copy_kByte);
  memmove(expected, src2, copy_kByte);

  ck_assert_mem_eq(res, expected, check_kByte);
}
END_TEST

START_TEST(write_in_right) {
  char src[200] = "Hate";
  char src2[200] = "Hate";
  s21_size_t copy_kByte = 4;

  char res[200] = "i hate memcmp";
  char expected[200] = "i hate memcmp";
  s21_size_t check_kByte = 17;

  s21_memmove(res + 13, src, copy_kByte);
  memmove(expected + 13, src2, copy_kByte);

  ck_assert_mem_eq(res, expected, check_kByte);
}
END_TEST

START_TEST(write_in_mid) {
  char src[200] = "Hate";
  char src2[200] = "Hate";
  s21_size_t copy_kByte = 4;

  char res[200] = "i hate memcmp";
  char expected[200] = "i hate memcmp";
  s21_size_t check_kByte = 17;

  s21_memmove(res + 5, src, copy_kByte);
  memmove(expected + 5, src2, copy_kByte);

  ck_assert_mem_eq(res, expected, check_kByte);
}
END_TEST

START_TEST(overlap_write_in_left) {
  char src[200] = "I HATE memmove!!!";
  char src2[200] = "I HATE memmove!!!";
  s21_size_t copy_kByte = 17;

  char *res = src;
  char *expected = src2;
  s21_size_t check_kByte = 34;

  s21_memmove(res, src, copy_kByte);
  memmove(expected, src2, copy_kByte);

  ck_assert_mem_eq(res, expected, check_kByte);
}
END_TEST

START_TEST(overlap_write_in_right) {
  char src[200] = "I HATE memmove!!!";
  char src2[200] = "I HATE memmove!!!";
  s21_size_t copy_kByte = 17;

  char *res = src + 17;
  char *expected = src2 + 17;
  s21_size_t check_kByte = 34;

  s21_memmove(res, src, copy_kByte);
  memmove(expected, src2, copy_kByte);

  ck_assert_mem_eq(res, expected, check_kByte);
}
END_TEST

START_TEST(overlap_write_in_mid) {
  char src[200] = "I HATE memmove!!!";
  char src2[200] = "I HATE memmove!!!";
  s21_size_t copy_kByte = 17;

  char *res = src + 5;
  char *expected = src2 + 5;
  s21_size_t check_kByte = 34;

  s21_memmove(res, src, copy_kByte);
  memmove(expected, src2, copy_kByte);

  ck_assert_mem_eq(res, expected, check_kByte);
}
END_TEST

START_TEST(zero_test_string) {
  char src[] = "aboba";
  s21_size_t kByte = 0;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(any_empty) {
  char src[] = "";
  s21_size_t kByte = 0;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(zero_test_string_with_register_memmove) {
  char src[] = "I hate memcmp";
  s21_size_t kByte = 0;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(zero_test_num) {
  char src[] = "123";
  s21_size_t kByte = 1;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(one_byte_string) {
  char src[] = "aboba";
  s21_size_t kByte = 1;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(one_byte_string_with_register) {
  char src[] = "Zboba";
  s21_size_t kByte = 1;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(one_byte_num) {
  char src[] = "09";
  s21_size_t kByte = 1;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(basic_long_string) {
  char src[] = "abobasdafoijasdofjas asdopij";
  s21_size_t kByte = 28;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(long_string_with_register) {
  char src[] = "aposkd AOSIjFasodijpaoisdjf poisdjfg";
  s21_size_t kByte = 36;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(long_string_with_register_and_num) {
  char src[] =
      "This is a long string with capital letters and numbers: 1234567890";
  s21_size_t kByte = 50;
  char res[kByte + 8];
  char expected[kByte + 8];
  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(long_string_with_register_and_num_and_simbol) {
  char src[] =
      "()()(((())):!,....This is another long string with capital letters and "
      "numbers: 1234567890";
  s21_size_t kByte = 75;
  char res[kByte + 8];
  char expected[kByte + 8];
  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(ints) {
  int src[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  s21_size_t kByte = 20;
  char res[kByte + 8];
  char expected[kByte + 8];
  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(floats) {
  float src[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.1};
  s21_size_t kByte = 40;
  char res[kByte + 8];
  char expected[kByte + 8];
  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(long_doubles) {
  long double src[] = {1.1111, 2.2222, 3.3333, 4.4444, 5.5555,
                       6.6666, 7.7777, 8.8888, 9.9999, 10.1010};
  s21_size_t kByte = 80;
  char res[kByte + 8];
  char expected[kByte + 8];
  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

// memset

START_TEST(equal_byte) {
  char res[] = "Hello, world!";
  char expected[] = "Hello, world!";
  char replace = 'g';
  s21_size_t n_byte = strlen(res);
  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(set_lolkek) {
  char b1[50] = "lolkek";
  char b2[50] = "lolkek";
  ck_assert_str_eq(memset(b1, '*', 8), s21_memset(b2, '*', 8));
}
END_TEST

START_TEST(large_byte) {
  char res[1024] = {0};
  char expected[1024] = {0};
  char replace = 'g';
  s21_size_t n_byte = sizeof(res);
  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);

  ck_assert_mem_eq(res, expected, n_byte);
}
END_TEST

START_TEST(multi_byte) {
  int res[] = {1, 2, 3, 4, 5};
  int expected[] = {1, 2, 7, 7, 7};
  int replace = 7;
  s21_size_t n_byte = sizeof(int) * 3;
  s21_memset(res + 2, replace, n_byte);
  memset(expected + 2, replace, n_byte);

  ck_assert_mem_eq(res, expected, sizeof(res));
}
END_TEST

START_TEST(set_lolkek_cheburek) {
  char b1[50] = "lolkek_cheburek";
  char b2[50] = "lolkek_cheburek";
  ck_assert_str_eq(memset(b1, '#', 3), s21_memset(b2, '#', 3));
  ck_assert_str_eq(memset(b1, '|', 1), s21_memset(b2, '|', 1));
}
END_TEST

START_TEST(cast_byte) {
  short res[] = {1, 2, 3, 4, 5};
  short expected[] = {1, 2, 7, 7, 5};
  char replace = 7;
  s21_size_t n_byte = sizeof(short) * 2;
  s21_memset((char *)res + 4, replace, n_byte);
  memset((char *)expected + 4, replace, n_byte);

  ck_assert_mem_eq(res, expected, sizeof(res));
}
END_TEST

START_TEST(all_byte) {
  char res[] =
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAA";
  char expected[] =
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAA";
  char replace = 'A';
  s21_size_t n_byte = sizeof(res);
  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);

  ck_assert_mem_eq(res, expected, n_byte);
}
END_TEST

// strncat

START_TEST(zero_byte) {
  char src[] = "abosal";
  char res[10] = "";
  char expected[10] = "";
  s21_size_t n_byte = 0;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(empty_src_strncat) {
  char src[] = "";
  char res[10] = "cd";
  char expected[10] = "cd";
  s21_size_t n_byte = 0;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(append_to_empty_dest) {
  char src[] = "test";
  char res[10] = "";
  char expected[10] = "";
  s21_size_t n_byte = 4;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_eq(res, expected, n_byte);
}
END_TEST

START_TEST(append_to_nonempty_dest) {
  char src[] = " is working";
  char res[20] = "Function";
  char expected[20] = "Function";
  s21_size_t n_byte = 7;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_eq(res, expected, strlen(expected));
}
END_TEST

START_TEST(append_more_than_src_size) {
  char src[] = "test";
  char res[10] = "123";
  char expected[10] = "123";
  s21_size_t n_byte = 10;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_eq(res, expected, strlen(expected));
}
END_TEST

START_TEST(append_fewer_than_src_size) {
  char src[] = "test";
  char res[10] = "123";
  char expected[10] = "123";
  s21_size_t n_byte = 2;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_eq(res, expected, strlen(expected));
}
END_TEST

START_TEST(src_bigger_than_n) {
  char src[] = "test";
  char res[10] = "123";
  char expected[10] = "123";
  s21_size_t n_byte = 2;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_eq(res, expected, strlen(expected));
}
END_TEST

// strchr

START_TEST(test_strchr_basic) {
  const char *str = "Hello World!";
  int c = 'o';

  char *expected = strchr(str, c);
  char *result = s21_strchr(str, c);

  ck_assert_ptr_eq(expected, result);
}

START_TEST(test_strchr_not_found) {
  const char *str = "Hello World!";
  int c = 'z';

  char *expected = strchr(str, c);
  char *result = s21_strchr(str, c);

  ck_assert_ptr_eq(expected, result);
}

START_TEST(test_strchr_null_terminator) {
  const char *str = "Hello World!";
  int c = '\0';

  char *expected = strchr(str, c);
  char *result = s21_strchr(str, c);

  ck_assert_ptr_eq(expected, result);
}

START_TEST(test_strchr_first_char) {
  const char *str = "Hello World!";
  int c = 'H';

  char *expected = strchr(str, c);
  char *result = s21_strchr(str, c);

  ck_assert_ptr_eq(expected, result);
}

START_TEST(test_strchr_last_char) {
  const char *str = "Hello World!";
  int c = '!';

  char *expected = strchr(str, c);
  char *result = s21_strchr(str, c);

  ck_assert_ptr_eq(expected, result);
}

START_TEST(test_strchr_same_chars) {
  const char *str = "aaaaaa";
  int c = 'a';

  char *expected = strchr(str, c);
  char *result = s21_strchr(str, c);

  ck_assert_ptr_eq(expected, result);
}

START_TEST(test_strchr_empty_str) {
  const char *str = "";
  int c = 'a';

  char *expected = strchr(str, c);
  char *result = s21_strchr(str, c);

  ck_assert_ptr_eq(expected, result);
}

// strncmp

START_TEST(test_equal_strings) {
  const char *str1 = "hello";
  const char *str2 = "hello";
  const int n = 5;
  const int expected = strncmp(str1, str2, n);
  const int result = s21_strncmp(str1, str2, n);
  ck_assert_int_eq(expected, result);
}
END_TEST

START_TEST(test_different_strings) {
  const char *str1 = "hello";
  const char *str2 = "world";
  const int n = 5;
  const int expected = strncmp(str1, str2, n);
  const int result = s21_strncmp(str1, str2, n);
  ck_assert_int_eq(expected, result);
}
END_TEST

START_TEST(test_first_string_shorter) {
  const char *str1 = "hi";
  const char *str2 = "world";
  const int n = 5;
  const int expected = strncmp(str1, str2, n);
  const int result = s21_strncmp(str1, str2, n);
  ck_assert_int_eq(expected, result);
}
END_TEST

START_TEST(test_second_string_shorter) {
  const char *str1 = "hello";
  const char *str2 = "hi";
  const int n = 5;
  const int expected = strncmp(str1, str2, n);
  const int result = s21_strncmp(str1, str2, n);
  ck_assert_int_eq(expected, result);
}
END_TEST

START_TEST(test_first_string_empty) {
  const char *str1 = "";
  const char *str2 = "hello";
  const int n = 5;
  const int expected = strncmp(str1, str2, n);
  const int result = s21_strncmp(str1, str2, n);
  ck_assert_int_eq(expected, result);
}
END_TEST

START_TEST(test_second_string_empty) {
  const char *str1 = "hello";
  const char *str2 = "";
  const int n = 5;
  const int expected = strncmp(str1, str2, n);
  const int result = s21_strncmp(str1, str2, n);
  ck_assert_int_eq(expected, result);
}
END_TEST

START_TEST(test_n_larger_than_strings) {
  const char *str1 = "hello";
  const char *str2 = "world";
  const int n = 10;
  const int expected = strncmp(str1, str2, n);
  const int result = s21_strncmp(str1, str2, n);
  ck_assert_int_eq(expected, result);
}
END_TEST

// strncpy

START_TEST(test_s21_strncpy_basic) {
  char src[] = "source string";
  char dest[20] = {0};
  char expected[20] = {0};

  s21_strncpy(dest, src, 6);
  strncpy(expected, src, 6);

  ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(test_s21_strncpy_dest_larger_than_src) {
  char src[] = "source";
  char dest[10] = {0};
  char expected[10] = {0};

  s21_strncpy(dest, src, 10);
  strncpy(expected, src, 10);

  ck_assert_str_eq(dest, expected);
}
END_TEST

// START_TEST(test_s21_strncpy_src_larger_than_dest) {
//     char src[] = "source string";
//     char dest[5] = {0};
//     char expected[5] = {0};

//     s21_strncpy(dest, src, 5);
//     strncpy(expected, src, 5);

//     ck_assert_str_eq(dest, expected);
// }
// END_TEST

START_TEST(test_s21_strncpy_empty_src) {
  char src[] = "";
  char dest[5] = {0};
  char expected[5] = {0};

  s21_strncpy(dest, src, 5);
  strncpy(expected, src, 5);

  ck_assert_str_eq(dest, expected);
}
END_TEST

// START_TEST(test_s21_strncpy_empty_dest) {
//     char src[] = "source string";
//     char dest[1] = {0};
//     char expected[1] = {0};

//     s21_strncpy(dest, src, 1);
//     strncpy(expected, src, 1);

//     ck_assert_str_eq(dest, expected);
// }
// END_TEST

START_TEST(test_s21_strncpy_n_equal_to_src_len) {
  char src[] = "source string";
  char dest[20] = {0};
  char expected[20] = {0};

  s21_strncpy(dest, src, strlen(src));
  strncpy(expected, src, strlen(src));

  ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(test_s21_strncpy_n_greater_than_src_len) {
  char src[] = "source string";
  char dest[20] = {0};
  char expected[20] = {0};

  s21_strncpy(dest, src, strlen(src) + 5);
  strncpy(expected, src, strlen(src) + 5);

  ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(string_strncpy) {
  char src[] = "Str1ng";
  char res[7 + 7] = "Str1ng";
  char exp[7 + 7] = "Str1ng";
  s21_size_t n_byte = 7;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(two_byte_strncpy) {
  char src[] = "123";
  char res[7] = "123";
  char exp[7] = "123";
  s21_size_t n_byte = 2;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

// strcspn

START_TEST(test_s21_strcspn_empty_str1) {
  const char *str1 = "";
  const char *str2 = "abc";
  s21_size_t expected = strcspn(str1, str2);

  s21_size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strcspn_empty_str2) {
  const char *str1 = "abc";
  const char *str2 = "";
  s21_size_t expected = strcspn(str1, str2);

  s21_size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strcspn_same_chars) {
  const char *str1 = "aaaaaaa";
  const char *str2 = "a";
  s21_size_t expected = strcspn(str1, str2);

  s21_size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strcspn_no_match) {
  const char *str1 = "abcdefg";
  const char *str2 = "hijklmn";
  s21_size_t expected = strcspn(str1, str2);

  s21_size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strcspn_partial_match) {
  const char *str1 = "abcdefg";
  const char *str2 = "cdefgh";
  s21_size_t expected = strcspn(str1, str2);

  s21_size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strcspn_full_match) {
  const char *str1 = "abcde";
  const char *str2 = "cba";
  s21_size_t expected = strcspn(str1, str2);

  s21_size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strcspn_match_first_char) {
  const char *str1 = "abcde";
  const char *str2 = "axyz";
  s21_size_t expected = s21_strcspn(str1, str2);
  ;

  s21_size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, expected);
}

// strpbrk

START_TEST(test_strpbrk_match) {
  const char *str1 = "hello";
  const char *str2 = "lo";
  char *res1 = s21_strpbrk(str1, str2);
  char *res2 = strpbrk(str1, str2);
  ck_assert_int_eq(*res1, *res2);
}
END_TEST

START_TEST(test_strpbrk_no_match) {
  const char *str1 = "hello";
  const char *str2 = "x";
  char *res1 = s21_strpbrk(str1, str2);
  char *res2 = strpbrk(str1, str2);
  ck_assert_ptr_eq(res1, res2);
  ck_assert_ptr_eq(res1, S21_NULL);
}
END_TEST

START_TEST(test_strpbrk_empty_string) {
  const char *str1 = "";
  const char *str2 = "";
  char *res1 = s21_strpbrk(str1, str2);
  char *res2 = strpbrk(str1, str2);
  ck_assert_ptr_eq(res1, res2);
  ck_assert_ptr_eq(res1, S21_NULL);
}
END_TEST

START_TEST(test_strpbrk_match_start) {
  const char *str1 = "hello";
  const char *str2 = "he";
  char *res1 = s21_strpbrk(str1, str2);
  char *res2 = strpbrk(str1, str2);
  ck_assert_int_eq(*res1, *res2);
}
END_TEST

START_TEST(test_strpbrk_match_end) {
  const char *str1 = "hello";
  const char *str2 = "o";
  char *res1 = s21_strpbrk(str1, str2);
  char *res2 = strpbrk(str1, str2);
  ck_assert_int_eq(*res1, *res2);
}
END_TEST

START_TEST(test_strpbrk_match_middle) {
  const char *str1 = "hello";
  const char *str2 = "ll";
  char *res1 = s21_strpbrk(str1, str2);
  char *res2 = strpbrk(str1, str2);
  ck_assert_int_eq(*res1, *res2);
}
END_TEST

START_TEST(find_zero) {
  char str1[] = "ppppppppppppP";
  char str2[] = "\0";

  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

// strrchr

START_TEST(test_strrchr_found) {
  const char *str = "hello world";
  int c = 'o';
  char *res1 = s21_strrchr(str, c);
  char *res2 = strrchr(str, c);
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strrchr_not_found) {
  const char *str = "hello world";
  int c = 'z';
  char *res1 = s21_strrchr(str, c);
  char *res2 = strrchr(str, c);
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strrchr_empty_string) {
  const char *str = "";
  int c = 'o';
  char *res1 = s21_strrchr(str, c);
  char *res2 = strrchr(str, c);
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(empty_strrchr) {
  char str1[] = "";
  char str2 = '\0';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(test_strrchr_zero_byte) {
  const char *str = "hello\0world";
  int c = '\0';
  char *res1 = s21_strrchr(str, c);
  char *res2 = strrchr(str, c);
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(find_big_P) {
  char str1[] = "ppPpppppppppP";
  char str2 = 'P';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(find_zero_strrchr) {
  char str1[] = "123456789";
  char str2 = '0';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

// strspn

START_TEST(test_s21_strspn_empty_str1) {
  const char *str1 = "";
  const char *str2 = "abc";
  s21_size_t expected = 0;
  s21_size_t result = s21_strspn(str1, str2);
  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strspn_empty_str2) {
  const char *str1 = "abc";
  const char *str2 = "";
  s21_size_t expected = 0;
  s21_size_t result = s21_strspn(str1, str2);
  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strspn_equal_str) {
  const char *str1 = "abc";
  const char *str2 = "abc";
  s21_size_t expected = 3;
  s21_size_t result = s21_strspn(str1, str2);
  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strspn_no_match) {
  const char *str1 = "abc";
  const char *str2 = "def";
  s21_size_t expected = 0;
  s21_size_t result = s21_strspn(str1, str2);
  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strspn_full_match) {
  const char *str1 = "abc";
  const char *str2 = "aabbcc";
  s21_size_t expected = 3;
  s21_size_t result = s21_strspn(str1, str2);
  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strspn_multiple_match) {
  const char *str1 = "abc";
  const char *str2 = "aabbcc";
  s21_size_t expected = 3;
  s21_size_t result = s21_strspn(str1, str2);
  ck_assert_int_eq(result, expected);
}

START_TEST(empty) {
  char src[] = "";
  char res[] = "";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(any_register) {
  char src[] = "gora";
  char res[] = "gOra";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(num_num) {
  char src[] = "123";
  char res[] = "123";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(long_num_num) {
  char src[] = "12345";
  char res[] = "123";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(num_long_num) {
  char src[] = "123";
  char res[] = "12345";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(any_num) {
  char src[] = "1234567890";
  char res[] = "0987654321";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(num_with_letter) {
  char src[] = "1A2A3A4A5A";
  char res[] = "123";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(num_with_letter2) {
  char src[] = "a1aaa23aaa41235";
  char res[] = "123";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(basic_test) {
  char src[] = "absD";
  char res[] = "aD";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(any_sim) {
  char src[] = "32ASDASDPare[0g9jf m07y271234567890";
  char res[] = "0987654321";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(upper_letter) {
  char src[] = "32ASDASDPare[0g9jf m07y271234567890";
  char res[] = "1234567890QWERTYUIOPASDFGHJKLZXCVBNM";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(lower_letter) {
  char src[] = "32jersASDASDPare[0g9jf m07y271234567890";
  char res[] = "1234567890qwertyuiopasdfghjklczxcvbnm";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(not_uniq_sim) {
  char src[] =
      "333333333333333333333333333333333333333333333333333333333333333333333333"
      "33333333333333";
  char res[] =
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "11111111111113";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

// strstr

START_TEST(test_empty_needle) {
  const char *haystack = "Hello, world!";
  const char *needle = "";
  const char *expected = strstr(haystack, needle);
  const char *result = s21_strstr(haystack, needle);
  ck_assert_ptr_eq(expected, result);
}
END_TEST

START_TEST(test_needle_at_start) {
  const char *haystack = "Hello, world!";
  const char *needle = "Hello";
  const char *expected = strstr(haystack, needle);
  const char *result = s21_strstr(haystack, needle);
  ck_assert_ptr_eq(expected, result);
}
END_TEST

START_TEST(test_needle_at_end) {
  const char *haystack = "Hello, world!";
  const char *needle = "world!";
  const char *expected = strstr(haystack, needle);
  const char *result = s21_strstr(haystack, needle);
  ck_assert_ptr_eq(expected, result);
}
END_TEST

START_TEST(test_needle_in_middle) {
  const char *haystack = "Hello, world!";
  const char *needle = ",";
  const char *expected = strstr(haystack, needle);
  const char *result = s21_strstr(haystack, needle);
  ck_assert_ptr_eq(expected, result);
}
END_TEST

START_TEST(test_needle_not_found) {
  const char *haystack = "Hello, world!";
  const char *needle = "foo";
  const char *expected = strstr(haystack, needle);
  const char *result = s21_strstr(haystack, needle);
  ck_assert_ptr_eq(expected, result);
}
END_TEST

START_TEST(test_prefix_needle) {
  const char *haystack = "Hello, world!";
  const char *needle = "Hell";
  const char *expected = strstr(haystack, needle);
  const char *result = s21_strstr(haystack, needle);
  ck_assert_ptr_eq(expected, result);
}
END_TEST

START_TEST(test_suffix_needle) {
  const char *haystack = "Hello, world!";
  const char *needle = "rld!";
  const char *expected = strstr(haystack, needle);
  const char *result = s21_strstr(haystack, needle);
  ck_assert_ptr_eq(expected, result);
}
END_TEST

// strtok

START_TEST(test_empty_string) {
  char str[] = "";
  char delim[] = " ,.";
  char *token1, *token2;

  token1 = strtok(str, delim);
  token2 = s21_strtok(str, delim);

  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_only_delimiters) {
  char str[] = " ,.";
  char delim[] = " ,.";
  char *token1, *token2;

  token1 = strtok(str, delim);
  token2 = s21_strtok(str, delim);

  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_one_token) {
  char str[] = "token";
  char delim[] = " ,.";
  char *token1, *token2;

  token1 = strtok(str, delim);
  token2 = s21_strtok(str, delim);

  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_multiple_tokens) {
  char str[] = "This is a string, with some commas.";
  char delim[] = " ,.";
  char *token1, *token2;

  token1 = strtok(str, delim);
  token2 = s21_strtok(str, delim);

  while (token1 != NULL && token2 != NULL) {
    ck_assert_str_eq(token1, token2);
    token2 = s21_strtok(NULL, delim);
    token1 = strtok(NULL, delim);
  }

  ck_assert_ptr_eq(token2, NULL);
}
END_TEST

START_TEST(test_only_delimiters_2) {
  char str[] = " ,,., ";
  char delim[] = " ,.";
  char *token1, *token2;
  token1 = strtok(str, delim);
  token2 = s21_strtok(str, delim);

  ck_assert_ptr_eq(token1, token2);

  while (token1 != NULL && token2 != NULL) {
    token1 = strtok(NULL, delim);
    token2 = s21_strtok(NULL, delim);
  }

  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_one_delimiter) {
  char str[] = ",";
  char delim[] = " ,.";
  char *token1, *token2;
  token1 = strtok(str, delim);
  token2 = s21_strtok(str, delim);

  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_same_tokens) {
  char str[] = "aaa bbb aaa ccc aaa";
  char delim[] = " ,.";
  char *token1, *token2;

  // копируем строку str для использования с s21_strtok
  char str_copy[sizeof(str)];
  strcpy(str_copy, str);

  token1 = strtok(str, delim);
  token2 = s21_strtok(str_copy, delim);

  while (token1 != NULL && token2 != NULL) {
    ck_assert_str_eq(token1, token2);
    token1 = strtok(NULL, delim);
    token2 = s21_strtok(NULL, delim);
  }

  ck_assert_ptr_eq(token1, token2);
}
END_TEST

// sprintf

// START_TEST(test_s21_sprintf_simple_int)
// {
//     char s21_str[MAX_BUF_SIZE];
//     char stdio_str[MAX_BUF_SIZE];

//     int value = 42;
//     const char* format = "The answer is %d";

//     int s21_sprintf_result = s21_sprintf(s21_str, format, value);
//     int stdio_sprintf_result = sprintf(stdio_str, format, value);

//     ck_assert_int_eq(s21_sprintf_result, stdio_sprintf_result);
//     ck_assert_str_eq(s21_str, stdio_str);
// }
// END_TEST

// START_TEST(test_s21_sprintf_char)
// {
//     char s21_str[MAX_BUF_SIZE];
//     char stdio_str[MAX_BUF_SIZE];

//     char value = 'a';
//     const char* format = "The letter is %c";

//     int s21_sprintf_result = s21_sprintf(s21_str, format, value);
//     int stdio_sprintf_result = sprintf(stdio_str, format, value);

//     ck_assert_int_eq(s21_sprintf_result, stdio_sprintf_result);
//     ck_assert_str_eq(s21_str, stdio_str);
// }
// END_TEST

// START_TEST(test_s21_sprintf_string)
// {
//     char s21_str[MAX_BUF_SIZE];
//     char stdio_str[MAX_BUF_SIZE];

//     const char* value = "Hello, world!";
//     const char* format = "The string is \"%s\"";

//     int s21_sprintf_result = s21_sprintf(s21_str, format, value);
//     int stdio_sprintf_result = sprintf(stdio_str, format, value);

//     ck_assert_int_eq(s21_sprintf_result, stdio_sprintf_result);
//     ck_assert_str_eq(s21_str, stdio_str);
// }
// END_TEST

// START_TEST(test_s21_sprintf_multiple_args)
// {
//     char s21_str[MAX_BUF_SIZE];
//     char stdio_str[MAX_BUF_SIZE];

//     const char* name = "Alice";
//     int age = 25;
//     float height = 1.75f;
//     const char* format = "%s is %d years old and is %.2f meters tall";

//     int s21_sprintf_result = s21_sprintf(s21_str, format, name, age, height);
//     int stdio_sprintf_result = sprintf(stdio_str, format, name, age, height);

//     ck_assert_int_eq(s21_sprintf_result, stdio_sprintf_result);
//     ck_assert_str_eq(s21_str, stdio_str);
// }
// END_TEST

// START_TEST(char_formatting) {
//     char str1[MAX_BUF_SIZE];
//     char str2[MAX_BUF_SIZE];

//     char *format = "The first letter of the alphabet is %c";
//     char c = 'a';
//     ck_assert_int_eq(s21_sprintf(str1, format, c),
//                      sprintf(str2, format, c));

//     ck_assert_str_eq(str1, str2);
// }
// END_TEST

// START_TEST(string_formatting) {
//     char str1[MAX_BUF_SIZE];
//     char str2[MAX_BUF_SIZE];

//     char *format = "My favorite color is %s";
//     char *color = "blue";
//     ck_assert_int_eq(s21_sprintf(str1, format, color),
//                      sprintf(str2, format, color));

//     ck_assert_str_eq(str1, str2);
// }
// END_TEST

// START_TEST(float_formatting) {
//     char str1[MAX_BUF_SIZE];
//     char str2[MAX_BUF_SIZE];

//     char *format = "The value of pi is approximately %f";
//     double pi = 3.14159;
//     ck_assert_int_eq(s21_sprintf(str1, format, pi),
//                      sprintf(str2, format, pi));

//     ck_assert_str_eq(str1, str2);
// }
// END_TEST

// START_TEST(test_s21_sprintf_multiple_values)
// {
//     char s21_str[MAX_BUF_SIZE];
//     char stdio_str[MAX_BUF_SIZE];

//     int a = 10, b = 20, c = 30;
//     const char* format = "Values: %d %d %d";

//     int s21_sprintf_result = s21_sprintf(s21_str, format, a, b, c);
//     int stdio_sprintf_result = sprintf(stdio_str, format, a, b, c);

//     ck_assert_int_eq(s21_sprintf_result, stdio_sprintf_result);
//     ck_assert_str_eq(s21_str, stdio_str);
// }
// END_TEST

// START_TEST(test_s21_sprintf_string_1)
// {
//     char s21_str[MAX_BUF_SIZE];
//     char stdio_str[MAX_BUF_SIZE];

//     const char* str = "Hello, world!";
//     const char* format = "String: %s";

//     int s21_sprintf_result = s21_sprintf(s21_str, format, str);
//     int stdio_sprintf_result = sprintf(stdio_str, format, str);

//     ck_assert_int_eq(s21_sprintf_result, stdio_sprintf_result);
//     ck_assert_str_eq(s21_str, stdio_str);
// }
// END_TEST

// START_TEST(test_s21_sprintf_char_1)
// {
//     char s21_str[MAX_BUF_SIZE];
//     char stdio_str[MAX_BUF_SIZE];

//     char value = 'X';
//     const char* format = "Character: %c";

//     int s21_sprintf_result = s21_sprintf(s21_str, format, value);
//     int stdio_sprintf_result = sprintf(stdio_str, format, value);

//     ck_assert_int_eq(s21_sprintf_result, stdio_sprintf_result);
//     ck_assert_str_eq(s21_str, stdio_str);
// }
// END_TEST

// START_TEST(test_s21_sprintf_percent)
// {
//     char s21_str[MAX_BUF_SIZE];
//     char stdio_str[MAX_BUF_SIZE];

//     const char* format = "Percent: %%";

//     int s21_sprintf_result = s21_sprintf(s21_str, format);
//     int stdio_sprintf_result = sprintf(stdio_str, format);

//     ck_assert_int_eq(s21_sprintf_result, stdio_sprintf_result);
//     ck_assert_str_eq(s21_str, stdio_str);
// }
// END_TEST

// START_TEST(test_s21_sprintf_strings)
// {
//     char s21_str[MAX_BUF_SIZE];
//     char stdio_str[MAX_BUF_SIZE];

//     const char* str1 = "Hello";
//     const char* str2 = "world!";
//     const char* format = "%s, %s";

//     int s21_sprintf_result = s21_sprintf(s21_str, format, str1, str2);
//     int stdio_sprintf_result = sprintf(stdio_str, format, str1, str2);

//     ck_assert_int_eq(s21_sprintf_result, stdio_sprintf_result);
//     ck_assert_str_eq(s21_str, stdio_str);
// }
// END_TEST

// START_TEST(precise_int) {
//     char str1[MAX_BUF_SIZE];
//     char str2[MAX_BUF_SIZE];

//     char *format = "%.5i";
//     int val = 69;
//     ck_assert_int_eq(s21_sprintf(str1, format, val),
//                      sprintf(str2, format, val));

//     ck_assert_str_eq(str1, str2);
// }
// END_TEST

// START_TEST(width_int) {
//     char str1[MAX_BUF_SIZE];
//     char str2[MAX_BUF_SIZE];

//     char *format = "%5d";
//     int val = 69;
//     ck_assert_int_eq(s21_sprintf(str1, format, val),
//                      sprintf(str2, format, val));

//     ck_assert_str_eq(str1, str2);
// }
// END_TEST

START_TEST(simple_int) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "This is a simple value %d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(precise_int) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%.5i";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(width_int) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%5d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(minus_width_int) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%-5i";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(plus_width_int) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%+12d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(padding_int) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%012i";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(star_width_int) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%0*d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, 5, val),
                   sprintf(str2, format, 5, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(star_precision_int) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%0.*i";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, 5, val),
                   sprintf(str2, format, 5, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(many_flags_many_ints) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char format[] = "%0.*i %d %4.*i %013d %d";
  int val = 69;
  ck_assert_int_eq(
      s21_sprintf(str1, format, 5, val, -10431, 13, 5311, 0, -581813581),
      sprintf(str2, format, 5, val, -10431, 13, 5311, 0, -581813581));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(flags_long_int) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%+5.31li";
  long int val = 698518581899;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(flags_short_int) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%-16.9hi";
  short int val = 6958;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(flags_another_long_int) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%0.*ld";
  long val = 8581385185;
  ck_assert_int_eq(s21_sprintf(str1, format, 5, val),
                   sprintf(str2, format, 5, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(zero_precision_zero_int) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%.0d";
  int val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(space_flag_int) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "% d";
  int val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val_width) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%15u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val_flags) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%-16u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val_precision) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%.51u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(unsigned_val_many_flags) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "% 5.51u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(unsigned_val_short) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%hu";
  unsigned short int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val_long) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%lu";
  unsigned long int val = 949149114140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val_many) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%lu, %u, %hu, %.5u, %5.u";
  unsigned long int val = 949149114140;
  ck_assert_int_eq(
      s21_sprintf(str1, format, val, 14, 1441, 14414, 9681),
      sprintf(str2, format, val, (unsigned)14, (unsigned short)1441,
              (unsigned)14414, (unsigned)9681));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_zero) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%u";
  ck_assert_int_eq(s21_sprintf(str1, format, 0),
                   sprintf(str2, format, (unsigned)0));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(one_char) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%c";
  char val = 'X';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(one_precision) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%.5c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(one_flags) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "% -5c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(one_width) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%15c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(one_many) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%-5.3c%c%c%c%c Hello! ABOBA";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val, 'c', 'a', 'b', 'b'),
                   sprintf(str2, format, val, 'c', 'a', 'b', 'b'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(one_many_flags) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%-5.3c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(string) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%s";
  char *val = "I LOVE STRINGS AND TESTS AND SCHOOL21 NO JOKE";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(string_precision) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%.15s";
  char *val = "I LOVE STRINGS AND TESTS AND SCHOOL21 NO JOKE";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(string_width) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%15s";
  char *val = "69 IS MY FAVORITE NUMBER";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(string_flags) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%-15.9s";
  char *val = "69 IS MY FAVORITE NUMBER";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(string_long) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%s";
  char *val =
      "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG STRING";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(string_many) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif

  char *format = "%s%s%s%s";
  char *val =
      "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG STRING";
  char *s1 = "";
  char *s2 = "87418347813748913749871389480913";
  char *s3 = "HAHAABOBASUCKER";
  ck_assert_int_eq(s21_sprintf(str1, format, val, s1, s2, s3),
                   sprintf(str2, format, val, s1, s2, s3));

  ck_assert_str_eq(str1, str2);
}

// START_TEST(null_ptr) {
//     char str1[BUFF_SIZE];
//     char str2[BUFF_SIZE];

//     char *format = "%p";
//     char *ptr = NULL;
//     ck_assert_int_eq(s21_sprintf(str1, format, ptr),
//                      sprintf(str2, format, ptr));

//     ck_assert_str_eq(str1, str2);
// }
// END_TEST

START_TEST(string_width_huge) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif
  char *val = "kjafdiuhfjahfjdahf";
  char *format = "%120s";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(n_specifier) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif
  int ret = 0;
  char *format = "Hello, my sexy little aboba abobushka abobina %n";
  ck_assert_int_eq(s21_sprintf(str1, format, &ret),
                   sprintf(str2, format, &ret));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(float_precision) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif
  char *format = "%lf";
  long double val = 513515.131513515151351;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(float_width) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif
  char *format = "%10lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(float_precision_zero) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif
  char *format = "%.0lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(float_precision_empty) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif
  char *format = "%.lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(float_precision_huge) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif
  char *format = "%.15lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(float_precision_huge_negative) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif
  char *format = "%.15lf";
  long double val = -15.35581134;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(float_huge) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif
  char *format = "%lf";
  long double val = 72537572375.1431341;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(float_flags) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif
  char *format = "% f";
  float val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(float_many) {
#ifdef __APPLE__
  char *str1[BUFF_SIZE];
  char *str2[BUFF_SIZE];
#elif __linux__
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
#endif
  char *format = "% .0f %.lf %f %lf";
  float val = 0;
  double val1 = 0;
  long double val2 = 3515315.153151;
  float val3 = 5.5;
  double val4 = 9851.51351;
  long double val5 = 95919539159.53151351131;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val1, val2, val3, val4, val5),
                   sprintf(str2, format, val, val1, val2, val3, val4, val5));

  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite *test_suite(void) {
  Suite *s = suite_create("Library tests");

  // strerror
  TCase *tc1 = tcase_create("manhuntc, strerror");
  suite_add_tcase(s, tc1);
  tcase_add_test(tc1, all_std_errors);
  tcase_add_test(tc1, negative_err_code);

  // strlen
  TCase *tc2 = tcase_create("manhuntc, strlen");
  suite_add_tcase(s, tc2);
  tcase_add_test(tc2, test_strlen_empty_string);
  tcase_add_test(tc2, test_strlen_short_string);
  tcase_add_test(tc2, test_strlen_long_string);
  tcase_add_test(tc2, test_strlen_string_with_null_character);
  tcase_add_test(tc2, test_strlen_string_with_newline_character);
  tcase_add_test(tc2, test_strlen_string_with_tab_character);
  tcase_add_test(tc2, test_strlen_string_with_multiple_spaces);

  // strcmp
  TCase *tc3 = tcase_create("manhuntc, strcmp");
  suite_add_tcase(s, tc3);
  tcase_add_test(tc3, test_s21_strcmp_equal_strings);
  tcase_add_test(tc3, test_s21_strcmp_different_strings);
  tcase_add_test(tc3, test_s21_strcmp_one_empty_string);
  tcase_add_test(tc3, test_s21_strcmp_both_empty_strings);
  tcase_add_test(tc3, test_s21_strcmp_case_sensitive);
  tcase_add_test(tc3, test_s21_strcmp_special_characters);
  tcase_add_test(tc3, test_s21_strcmp_non_ascii_characters);

  // strcpy
  TCase *tc4 = tcase_create("eckhardy, strcpy");
  suite_add_tcase(s, tc4);
  tcase_add_test(tc4, test_strcpy);
  tcase_add_test(tc4, test_strcpy_empty_src);
  tcase_add_test(tc4, test_strcpy_empty_string);
  tcase_add_test(tc4, test_strcpy_dest_larger_than_src);
  tcase_add_test(tc4, test_strcpy_dest_same_as_src);
  tcase_add_test(tc4, test_strcpy_return_value);
  tcase_add_test(tc4, test_strcpy_with_null);

  // strcat
  TCase *tc5 = tcase_create("manhuntc, strcat");
  suite_add_tcase(s, tc5);
  tcase_add_test(tc5, test_strcat_empty_strings);
  tcase_add_test(tc5, test_strcat_src_empty);
  tcase_add_test(tc5, test_strcat_dest_empty);
  tcase_add_test(tc5, test_strcat_normal_strings);
  tcase_add_test(tc5, test_strcat_any_letters_with_register);
  tcase_add_test(tc5, test_strcat_dest_larger_than_src);
  tcase_add_test(tc5, test_strcat_both_large_strings);

  // memchr
  TCase *tc6 = tcase_create("achenara, memchr");
  suite_add_tcase(s, tc6);
  tcase_add_test(tc6, test_s21_memchr_match);
  tcase_add_test(tc6, test_s21_memchr_no_match);
  tcase_add_test(tc6, test_s21_memchr_first_char);
  tcase_add_test(tc6, test_s21_memchr_last_char);
  tcase_add_test(tc6, test_s21_memchr_zero_length);
  tcase_add_test(tc6, test_s21_memchr_null_pointer);
  tcase_add_test(tc6, test_s21_memchr_match_part_of_string);

  // memcmp
  TCase *tc7 = tcase_create("achenara, memcmp");
  suite_add_tcase(s, tc7);
  tcase_add_test(tc7, test_memcmp_empty_arrays);
  tcase_add_test(tc7, test_memcmp_equal_arrays);
  tcase_add_test(tc7, test_memcmp_different_arrays);
  tcase_add_test(tc7, test_memcmp_different_lengths_1);
  tcase_add_test(tc7, test_memcmp_different_lengths_2);
  tcase_add_test(tc7, test_memcmp_compare_digits);
  tcase_add_test(tc7, test_memcmp_compare_digits_and_letters);

  // memcpy
  TCase *tc8 = tcase_create("achenara, memcpy");
  suite_add_tcase(s, tc8);
  tcase_add_test(tc8, test_aligned_copy);
  tcase_add_test(tc8, empty_array_test);
  tcase_add_test(tc8, single_char_test);
  tcase_add_test(tc8, single_char_test);
  tcase_add_test(tc8, large_array_test);
  tcase_add_test(tc8, null_char_test);
  tcase_add_test(tc8, zero_test_string_with_register);

  // memmove
  TCase *tc9 = tcase_create("achenara, memmove");
  suite_add_tcase(s, tc9);
  tcase_add_test(tc9, empty_dest_and_src);
  tcase_add_test(tc9, empty_dest);
  tcase_add_test(tc9, empty_src);
  tcase_add_test(tc9, write_in_left);
  tcase_add_test(tc9, write_in_right);
  tcase_add_test(tc9, write_in_mid);
  tcase_add_test(tc9, overlap_write_in_left);
  tcase_add_test(tc9, overlap_write_in_right);
  tcase_add_test(tc9, overlap_write_in_mid);
  tcase_add_test(tc9, zero_test_string);
  tcase_add_test(tc9, any_empty);
  tcase_add_test(tc9, zero_test_string_with_register_memmove);
  tcase_add_test(tc9, zero_test_num);
  tcase_add_test(tc9, one_byte_string);
  tcase_add_test(tc9, one_byte_string_with_register);
  tcase_add_test(tc9, one_byte_num);
  tcase_add_test(tc9, basic_long_string);
  tcase_add_test(tc9, long_string_with_register);
  tcase_add_test(tc9, long_string_with_register_and_num);
  tcase_add_test(tc9, long_string_with_register_and_num_and_simbol);
  tcase_add_test(tc9, ints);
  tcase_add_test(tc9, floats);
  tcase_add_test(tc9, long_doubles);

  // memset
  TCase *tc10 = tcase_create("achenara, memset");
  suite_add_tcase(s, tc10);
  tcase_add_test(tc10, equal_byte);
  tcase_add_test(tc10, set_lolkek);
  tcase_add_test(tc10, large_byte);
  tcase_add_test(tc10, multi_byte);
  tcase_add_test(tc10, set_lolkek_cheburek);
  tcase_add_test(tc10, cast_byte);
  tcase_add_test(tc10, all_byte);

  // strncat
  TCase *tc11 = tcase_create("achenara, strncat");
  suite_add_tcase(s, tc11);
  tcase_add_test(tc11, zero_byte);
  tcase_add_test(tc11, empty_src_strncat);
  tcase_add_test(tc11, append_to_empty_dest);
  tcase_add_test(tc11, append_to_nonempty_dest);
  tcase_add_test(tc11, append_more_than_src_size);
  tcase_add_test(tc11, append_fewer_than_src_size);
  tcase_add_test(tc11, src_bigger_than_n);

  // strchr
  TCase *tc12 = tcase_create("achenara, strchr");
  suite_add_tcase(s, tc12);
  tcase_add_test(tc12, test_strchr_basic);
  tcase_add_test(tc12, test_strchr_not_found);
  tcase_add_test(tc12, test_strchr_null_terminator);
  tcase_add_test(tc12, test_strchr_first_char);
  tcase_add_test(tc12, test_strchr_last_char);
  tcase_add_test(tc12, test_strchr_same_chars);
  tcase_add_test(tc12, test_strchr_empty_str);

  // strncmp
  TCase *tc13 = tcase_create("eckhardy, strncmp");
  suite_add_tcase(s, tc13);
  tcase_add_test(tc13, test_equal_strings);
  tcase_add_test(tc13, test_different_strings);
  tcase_add_test(tc13, test_first_string_shorter);
  tcase_add_test(tc13, test_second_string_shorter);
  tcase_add_test(tc13, test_first_string_empty);
  tcase_add_test(tc13, test_second_string_empty);
  tcase_add_test(tc13, test_n_larger_than_strings);

  // strncpy
  TCase *tc14 = tcase_create("eckhardy, strncpy");
  suite_add_tcase(s, tc14);
  tcase_add_test(tc14, test_s21_strncpy_basic);
  tcase_add_test(tc14, test_s21_strncpy_dest_larger_than_src);
  tcase_add_test(tc14, string_strncpy);
  tcase_add_test(tc14, test_s21_strncpy_empty_src);
  tcase_add_test(tc14, two_byte_strncpy);
  tcase_add_test(tc14, test_s21_strncpy_n_equal_to_src_len);
  tcase_add_test(tc14, test_s21_strncpy_n_greater_than_src_len);

  // strcspn
  TCase *tc15 = tcase_create("eckhardy, strcspn");
  suite_add_tcase(s, tc15);
  tcase_add_test(tc15, test_s21_strcspn_empty_str1);
  tcase_add_test(tc15, test_s21_strcspn_empty_str2);
  tcase_add_test(tc15, test_s21_strcspn_same_chars);
  tcase_add_test(tc15, test_s21_strcspn_no_match);
  tcase_add_test(tc15, test_s21_strcspn_partial_match);
  tcase_add_test(tc15, test_s21_strcspn_full_match);
  tcase_add_test(tc15, test_s21_strcspn_match_first_char);

  // strpbrk
  TCase *tc16 = tcase_create("eckhardy, strpbrk");
  suite_add_tcase(s, tc16);
  tcase_add_test(tc16, test_strpbrk_match);
  tcase_add_test(tc16, test_strpbrk_no_match);
  tcase_add_test(tc16, test_strpbrk_empty_string);
  tcase_add_test(tc16, test_strpbrk_match_start);
  tcase_add_test(tc16, test_strpbrk_match_end);
  tcase_add_test(tc16, test_strpbrk_match_middle);
  tcase_add_test(tc16, find_zero);

  // strrchr
  TCase *tc17 = tcase_create("eckhardy, strrchr");
  suite_add_tcase(s, tc17);
  tcase_add_test(tc17, test_strrchr_found);
  tcase_add_test(tc17, test_strrchr_not_found);
  tcase_add_test(tc17, test_strrchr_empty_string);
  tcase_add_test(tc17, empty_strrchr);
  tcase_add_test(tc17, test_strrchr_zero_byte);
  tcase_add_test(tc17, find_big_P);
  tcase_add_test(tc17, find_zero_strrchr);

  // strspn
  TCase *tc18 = tcase_create("jeremiam, strspn");
  suite_add_tcase(s, tc18);
  tcase_add_test(tc18, test_s21_strspn_empty_str1);
  tcase_add_test(tc18, test_s21_strspn_empty_str2);
  tcase_add_test(tc18, test_s21_strspn_equal_str);
  tcase_add_test(tc18, test_s21_strspn_no_match);
  tcase_add_test(tc18, test_s21_strspn_full_match);
  tcase_add_test(tc18, test_s21_strspn_multiple_match);
  tcase_add_test(tc18, empty);
  tcase_add_test(tc18, any_register);
  tcase_add_test(tc18, num_num);
  tcase_add_test(tc18, long_num_num);
  tcase_add_test(tc18, num_long_num);
  tcase_add_test(tc18, any_num);
  tcase_add_test(tc18, num_with_letter);
  tcase_add_test(tc18, num_with_letter2);
  tcase_add_test(tc18, basic_test);
  tcase_add_test(tc18, any_sim);
  tcase_add_test(tc18, upper_letter);
  tcase_add_test(tc18, lower_letter);
  tcase_add_test(tc18, not_uniq_sim);

  // strstr
  TCase *tc19 = tcase_create("jeremiam, strstr");
  suite_add_tcase(s, tc19);
  tcase_add_test(tc19, test_empty_needle);
  tcase_add_test(tc19, test_needle_at_start);
  tcase_add_test(tc19, test_needle_at_end);
  tcase_add_test(tc19, test_needle_in_middle);
  tcase_add_test(tc19, test_needle_not_found);
  tcase_add_test(tc19, test_prefix_needle);
  tcase_add_test(tc19, test_suffix_needle);

  // strtok
  TCase *tc20 = tcase_create("jeremiam, strtok");
  suite_add_tcase(s, tc20);
  tcase_add_test(tc20, test_empty_string);
  tcase_add_test(tc20, test_only_delimiters);
  tcase_add_test(tc20, test_one_token);
  tcase_add_test(tc20, test_multiple_tokens);
  tcase_add_test(tc20, test_only_delimiters_2);
  tcase_add_test(tc20, test_one_delimiter);
  tcase_add_test(tc20, test_same_tokens);

  // sprintf
  TCase *tc21 = tcase_create("jeremiam, sprintf");
  suite_add_tcase(s, tc21);
  tcase_add_test(tc21, simple_int);
  tcase_add_test(tc21, precise_int);
  tcase_add_test(tc21, width_int);
  tcase_add_test(tc21, minus_width_int);
  tcase_add_test(tc21, plus_width_int);
  tcase_add_test(tc21, padding_int);
  tcase_add_test(tc21, star_width_int);
  tcase_add_test(tc21, star_precision_int);
  tcase_add_test(tc21, many_flags_many_ints);
  tcase_add_test(tc21, flags_long_int);
  tcase_add_test(tc21, flags_short_int);
  tcase_add_test(tc21, flags_another_long_int);
  tcase_add_test(tc21, zero_precision_zero_int);
  tcase_add_test(tc21, space_flag_int);
  tcase_add_test(tc21, unsigned_val);
  tcase_add_test(tc21, unsigned_val_width);
  tcase_add_test(tc21, unsigned_val_flags);
  tcase_add_test(tc21, unsigned_val_precision);
  tcase_add_test(tc21, unsigned_val_many_flags);
  tcase_add_test(tc21, unsigned_val_short);
  tcase_add_test(tc21, unsigned_val_long);
  tcase_add_test(tc21, unsigned_val_many);
  tcase_add_test(tc21, unsigned_zero);
  tcase_add_test(tc21, one_char);
  tcase_add_test(tc21, one_precision);
  tcase_add_test(tc21, one_flags);
  tcase_add_test(tc21, one_width);
  tcase_add_test(tc21, one_many);
  tcase_add_test(tc21, one_many_flags);
  tcase_add_test(tc21, string);
  tcase_add_test(tc21, string_precision);
  tcase_add_test(tc21, string_width);
  tcase_add_test(tc21, string_flags);
  tcase_add_test(tc21, string_long);
  tcase_add_test(tc21, string_many);
  tcase_add_test(tc21, n_specifier);
  tcase_add_test(tc21, string_width_huge);
  tcase_add_test(tc21, float_precision);
  tcase_add_test(tc21, float_width);
  tcase_add_test(tc21, float_precision_zero);
  tcase_add_test(tc21, float_precision_empty);
  tcase_add_test(tc21, float_precision_huge);
  tcase_add_test(tc21, float_precision_huge_negative);
  tcase_add_test(tc21, float_huge);
  tcase_add_test(tc21, float_flags);
  tcase_add_test(tc21, float_many);

  return s;
}

int main() {
  int success = 0;
  Suite *s;
  SRunner *runner;
  s = test_suite();
  runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  success = srunner_ntests_failed(runner);
  srunner_free(runner);
  if (success == 0) {
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}
