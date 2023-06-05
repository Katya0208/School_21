#include "s21_string.h"

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// strerror

char *s21_strerror(int errnum) {
  static char buf[32];

#if defined(__APPLE__)
  const char *const *errors = mac_errors;
  if (errnum < 0 || errnum >= ERR_COUNT) {
    snprintf(buf, sizeof(buf), "Unknown error: %d", errnum);
    return buf;
  }
#elif defined(__linux__)
  const char *const *errors = linux_errors;
  if (errnum < 0 || errnum >= ERR_COUNT) {
    snprintf(buf, sizeof(buf), "Unknown error %d", errnum);
    return buf;
  }
#else
  //неподдерживаемая платформа
  return "Unknown error";
#endif

  return (char *)errors[errnum];
}

// strlen
// eckhardy
s21_size_t s21_strlen(const char *str) {
  const char *ptr = str;
  while (*ptr) {
    ptr++;
  }
  return (ptr - str);
}

// strcmp

int s21_strcmp(const char *str1, const char *str2) {
  while (*str1 && (*str1 == *str2)) {
    str1++;
    str2++;
  }
  return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}

// strcpy
// eckhardy
char *s21_strcpy(char *dest, const char *src) {
  char *temp = dest;
  while (*src) {
    *temp++ = *src++;
  }
  *temp = '\0';  // добавляем в конец символ окончания строки
  return dest;
}

// ctrcat

char *s21_strcat(char *dest, const char *src) {
  char *p = dest;
  while (*p) { /* Найти конец dest */
    p++;
  }
  while (*src) { /* Копировать src в конец dest */
    *p++ = *src++;
  }
  *p = '\0'; /* Установить нулевой символ в конце строки */
  return dest;
}

// memchr

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *p = (const unsigned char *)
      str;  // приведение типов исходной строки к беззнаковому типу
  unsigned char ch =
      (unsigned char)c;  // приведение типа искомого символа к беззнаковому типу

  for (size_t i = 0; i < n; i++) {
    if (*p == ch) {
      return (void *)
          p;  // символ найден, возвращаем указатель на его позицию в строке
    }
    p++;
  }

  return S21_NULL;  // символ не найден, возвращаем S21_NULL
}

// memcmp

int s21_memcmp(const void *s1, const void *s2, s21_size_t n) {
  const unsigned char *c1 = s1, *c2 = s2;
  int res = 0;
  size_t i = 0;

  while (i < n && res == 0) {
    if (isdigit(c1[i]) &&
        s21_isdigit(
            c2[i])) {  // для проверки, являются ли сравниваемые символы цифрами
      int num1 = c1[i] - '0';
      int num2 = c2[i] - '0';
      if (num1 != num2) {
        res = (num1 > num2) ? 1 : -1;
      }
    } else {
      res = c1[i] - c2[i];
    }
    ++i;
  }

  return res;
}

// memcpy

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *d = (unsigned char *)dest;
  unsigned char *s = (unsigned char *)src;

  for (s21_size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }

  return dest;
}

// memmove

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *d = dest;
  const char *s = src;

  if (d < s) {
    for (s21_size_t i = 0; i < n; i++) {
      d[i] = s[i];
    }
  } else {
    for (s21_size_t i = n; i != 0; i--) {
      d[i - 1] = s[i - 1];
    }
  }

  return dest;
}

// memset

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *p = (unsigned char *)str;  // приведение типа
  unsigned char uc = (unsigned char)c;      // приведение типа

  for (s21_size_t i = 0; i < n; i++) {
    *(p + i) = uc;  // установка значения
  }

  return str;  // возвращаем указатель на начало области памяти
}

// strncat

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *ptr = dest + s21_strlen(dest);
  s21_size_t i = 0;
  while (*src != '\0' && i < n) {
    *ptr++ = *src++;
    i++;
  }
  *ptr = '\0';
  return dest;
}

// strchr

char *s21_strchr(const char *str, int c) {
  char *s = S21_NULL;

  for (s21_size_t i = 0; i <= s21_strlen(str); i++) {
    if (str[i] == c) {
      s = ((char *)str) + i;
      break;
    }
  }

  return s;
}

// strncmp

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    if (*str1 == '\0' || *str1 != *str2) {
      return (int)(*str1 - *str2);
    }
    str1++;
    str2++;
  }
  return 0;
}

// strncpy
// eckhardy
char *s21_strncpy(char *dest, const char *src, size_t n) {
  s21_memcpy(dest, src, n);
  return dest;
}

// strcspn
// eckhardy
s21_size_t s21_strcspn(const char *str, const char *keys) {
  s21_size_t c = 0;
  for (; *str && (s21_strchr(keys, *str) == S21_NULL); str++, c++)
    ;
  return c;
}

// strpbrk
// eckhardy
char *s21_strpbrk(const char *str, const char *sym) {
  s21_size_t i = s21_strcspn(str, sym);
  return i != s21_strlen(str) ? (char *)str + i : S21_NULL;
}

// strrchar
// eckhardy

char *s21_strrchr(const char *str, int source) {
  char *curr = ((char *)str) + s21_strlen(str);
  while (curr >= str && *curr != source) {
    curr--;
  }

  if (curr < str) {
    curr = S21_NULL;
  }

  return curr;
}

// strspn
// eckhardy
s21_size_t s21_strspn(const char *str, const char *keys) {
  s21_size_t c = 0;
  for (; (*str != '\0') && (s21_strchr(keys, *str) != S21_NULL); str++, c++)
    ;

  return c;
}

// strstr
// eckhardy
char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t nl = s21_strlen(needle), hl = s21_strlen(haystack);
  char *curr = S21_NULL;

  if (hl >= nl) {
    int found = 0;
    curr = (char *)haystack;
    for (; *curr && !found; curr++) {
      found = s21_strncmp(curr, needle, nl) == 0;
    }

    curr = found ? curr - 1 : S21_NULL;
  }

  return curr;
}

// strtok
// eckhardy
char *s21_strtok(char *str, const char *delim) {
  static char *next_token = NULL;
  char *token;

  if (str != NULL) {
    next_token = str;
  } else if (next_token == NULL) {
    return NULL;
  }

  while (*next_token && s21_strchr(delim, *next_token)) {
    next_token++;
  }

  if (!*next_token) {
    next_token = NULL;
    return NULL;
  }

  token = next_token;

  while (*next_token && !s21_strchr(delim, *next_token)) {
    next_token++;
  }

  if (!*next_token) {
    next_token = NULL;
  } else {
    *next_token++ = '\0';
  }

  return token;
}

// sprinf

int s21_atoi(const char *str) {
  int i = 0;
  int res = 0;
  int sign = 1;
  while (str[i] == '0' || str[i] == ' ') i++;
  if (str[i] == '-') {
    sign = -1;
    i++;
  }
  while (48 <= str[i] && str[i] <= 57) {
    res = res * 10 + ((int)str[i] - 48);
    i++;
  }
  return res * sign;
}

int s21_sprintf(char *str, const char *format, ...) {
  flags f = {0};
  va_list va;
  va_start(va, format);
  char *str_beginning = str;
  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
      continue;
    } else {
      format++;
      s21_memset(&f, 0, sizeof(flags));
    }

    format = get_flags(format, &f);
    format = get_width(format, &f, va);
    format = get_precision(format, &f, va);
    format = get_length(format, &f);

    f.specifier = *format;
    format++;

    char buff[BUFF_SIZE] = {'\0'};
    handle_value(f, buff, va);
    for (int i = 0; buff[i]; i++, str++) *str = buff[i];

    if (f.specifier == 'n') {
      int *ret = va_arg(va, int *);
      *ret = str - str_beginning;
    }
  }

  *str = '\0';
  va_end(va);
  return str - str_beginning;
}

const char *get_flags(const char *format, flags *f) {
  while (*format == '-' || *format == '+' || *format == ' ' || *format == '0') {
    switch (*format) {
      case '0':
        f->zero = true;
        break;
      case '-':
        f->minus = true;
        break;
      case '+':
        f->plus = true;
        break;
      case ' ':
        f->space = true;
        break;
    }
    format++;
  }
  return format;
}

const char *get_width(const char *format, flags *f, va_list va) {
  if (*format == '*') {
    format++;
    f->width = va_arg(va, int);
  } else if (s21_isdigit(*format)) {
    char tmp[BUFF_SIZE] = {'\0'};
    for (int i = 0; s21_isdigit(*format); i++, format++) tmp[i] = *format;
    f->width = s21_atoi(tmp);
  }
  return format;
}

const char *get_precision(const char *format, flags *f, va_list va) {
  if (*format == '.') {
    f->is_precision_set = true;
    format++;
  }

  if (*format == '*') {
    format++;
    f->precision = va_arg(va, int);
  }
  if (s21_isdigit(*format)) {
    char tmp[BUFF_SIZE] = {'\0'};
    for (int i = 0; s21_isdigit(*format); i++, format++) tmp[i] = *format;
    f->precision = s21_atoi(tmp);
  }
  return format;
}

const char *get_length(const char *format, flags *f) {
  switch (*format) {
    case 'h':
      f->length = 'h';
      format++;
      break;
    case 'l':
      f->length = 'l';
      format++;
  }
  return format;
}

void handle_value(flags f, char *buff, va_list va) {
  if (f.specifier == 'd' || f.specifier == 'i')
    parse_int(f, buff, va);
  else if (f.specifier == 'u')
    parse_unsigned(f, buff, va);
  else if (f.specifier == '%')
    buff[0] = '%';
  else if (f.specifier == 'c')
    parse_char(f, buff, va);
  else if (f.specifier == 's')
    parse_string(f, buff, va);
  else if (f.specifier == 'f')
    parse_float(f, buff, va);
}

void parse_int(flags f, char *buff, va_list va) {
  int64_t val = va_arg(va, int64_t);

  switch (f.length) {
    case 0:
      val = (int32_t)val;
      break;
    case 'h':
      val = (int16_t)val;
  }
  whole_num_to_string(val, buff, 10);
  format_precision(buff, f);
  format_flags(buff, f);
}

void whole_num_to_string(int64_t val, char *ret, int base) {
  char tmp[BUFF_SIZE] = {'\0'};
  int idx = BUFF_SIZE - 2;

  bool neg = val < 0 ? 1 : 0;
  val = neg ? -val : val;

  if (val == 0) tmp[idx] = '0';

  while (val > 0) {
    idx--;
    tmp[idx] = "0123456789abcdef"[val % base];
    val /= base;
  }
  for (int j = 0; tmp[idx]; idx++, j++) {
    if (neg && j == 0) {
      ret[j++] = '-';
    }

    ret[j] = tmp[idx];
  }
}

void format_precision(char *buff, flags f) {
  char tmp[BUFF_SIZE] = {'\0'};

  int sign = 0;
  int len = s21_strlen(buff);

  if (buff[0] == '-') {
    tmp[0] = '-';
    len--;
    sign = 1;
  }

  if (f.precision > len) {
    int idx;
    for (idx = sign; idx < f.precision - len + sign; idx++) tmp[idx] = '0';

    for (int i = sign; buff[i]; i++, idx++) tmp[idx] = buff[i];

    s21_strcpy(buff, tmp);
  }

  if (f.is_precision_set && f.precision == 0 &&
      check_integer_specifier(f.specifier) && buff[0] == '0')
    buff[0] = '\0';
}

bool check_integer_specifier(char c) {
  char specs[] = {'d', 'i', 'u'};
  bool res = false;
  for (s21_size_t i = 0; i < sizeof(specs); i++) {
    if (specs[i] == c) {
      res = true;
      break;
    }
  }
  return res;
}

void format_flags(char *buff, flags f) {
  char tmp[BUFF_SIZE + 1] = {'\0'};
  if (f.plus && f.specifier != 'u') {
    tmp[0] = buff[0] == '-' ? buff[0] : '+';
    s21_strcpy(tmp + 1, buff[0] == '-' ? buff + 1 : buff);
    s21_strcpy(buff, tmp);
  } else if (f.space && buff[0] != '-' && f.specifier != 'u') {
    tmp[0] = ' ';
    s21_strcpy(tmp + 1, buff);
    s21_strcpy(buff, tmp);
  }
  if (f.width > (int)s21_strlen(buff)) {
    int idx = f.width - s21_strlen(buff);
    if (!f.minus) {
      s21_memset(tmp, f.zero ? '0' : ' ', idx);
      s21_strcpy(tmp + idx, buff);
    } else {
      s21_strcpy(tmp, buff);
      s21_memset(tmp + s21_strlen(tmp), ' ', idx);
    }
    s21_strcpy(buff, tmp);
  }
}

void unsigned_num_to_string(uint64_t val, char *ret, int base) {
  char buf[BUFF_SIZE + 1] = {'\0'};
  int idx = BUFF_SIZE - 1;
  if (val == 0) {
    buf[idx] = '0';
    idx--;
  }

  for (; val && idx; --idx, val /= base)
    buf[idx] = "0123456789abcdef"[val % base];
  for (int j = 0; buf[idx + 1]; idx++, j++) ret[j] = buf[idx + 1];
}

void parse_unsigned(flags f, char *buff, va_list va) {
  uint64_t val = va_arg(va, uint64_t);
  switch (f.length) {
    case 'h':
      val = (uint16_t)val;
      break;
    case 'l':
      val = (uint64_t)val;
      break;
    case 0:
      val = (uint32_t)val;
  }
  unsigned_num_to_string(val, buff, 10);
  format_precision(buff, f);
  format_flags(buff, f);
}

void format_wchar(flags f, char *buff, wchar_t w_c) {
  if (!f.minus && f.width) {
    for (int i = 0; i < f.width; i++) {
      buff[i] = ' ';
      if (i == f.width - 1) wcstombs(buff, &w_c, BUFF_SIZE);
    }
  } else if (f.width) {
    wcstombs(buff, &w_c, BUFF_SIZE);
    for (int i = s21_strlen(buff); i < f.width; i++) buff[i] = ' ';
  } else {
    wcstombs(buff, &w_c, BUFF_SIZE);
  }
}

void format_char(flags f, char *buff, char c) {
  if (!f.minus && f.width > 1) {  // учитываем знак +
    for (int i = 0; i < f.width - 1; i++) {
      buff[i] = ' ';
    }
    buff[f.width - 1] = c;
  } else if (f.width > 1) {  // учитываем знак +
    buff[0] = c;
    for (int i = 1; i < f.width; i++) {
      buff[i] = ' ';
    }
  } else {
    buff[0] = c;
  }
}

void parse_char(flags f, char *buff, va_list va) {
  if (f.length == 'l') {
    wchar_t w_c;
    w_c = va_arg(
        va, wchar_t);  // получаем аргумент типа wchar_t из списка аргументов va
    format_wchar(
        f, buff,
        w_c);  // форматируем символ wchar_t с помощью функции format_wchar()
  } else {
    char c;
    c = va_arg(va, int);
    format_char(f, buff,
                c);  // форматируем символ char с помощью функции format_char()
  }
}

void format_string(flags f, char *buff, char *str) {
  char tmp[BUFF_SIZE] = {'\0'};
  s21_strcpy(tmp, str);
  if (f.is_precision_set) tmp[f.precision] = '\0';

  int shift = f.width - s21_strlen(tmp);
  int len = s21_strlen(tmp);

  if (f.minus && shift > 0) {
    s21_strcpy(buff, tmp);
    s21_memset(buff + len, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buff, ' ', shift);
    s21_strcpy(buff + shift, tmp);
  } else {
    s21_strcpy(buff, tmp);
  }
}

void parse_string(flags f, char *buff, va_list va) {
  char *str = va_arg(va, char *);
  format_string(f, buff, str);
}

void parse_float(flags f, char *buff, va_list va) {
  long double val = 0;
  val = va_arg(va, double);

  if (!f.is_precision_set) {
    f.precision = 6;
  }

  double_to_string(val, buff, f);
  format_flags(buff, f);
}
void double_to_string(long double val, char *ret, flags f) {
  char buff[BUFF_SIZE] = {'\0'};
  int idx = BUFF_SIZE - 2;
  bool neg = val < 0 ? 1 : 0;
  val = neg ? val * -1 : val;
  long double l = 0, r = modfl(val, &l);
  if (f.precision == 0) {
    l = roundl(val);
    r = 0;
  }
  char fractions[BUFF_SIZE] = {'\0'};
  for (int i = 0; i < f.precision; i++) {
    r = r * 10;
    fractions[i] = (int)r + '0';
  }
  long long right = roundl(r), left = l;
  if (!right) {
    for (int i = 0; i < f.precision; idx--, i++) buff[idx] = '0';
  } else {
    for (int i = s21_strlen(fractions); right || i > 0; right /= 10, idx--, i--)
      buff[idx] = (int)(right % 10 + 0.05) + '0';
  }
  if ((f.is_precision_set && f.precision != 0) || (int)r ||
      (!f.is_precision_set && val == 0) || s21_strlen(fractions))
    buff[idx--] = '.';
  if (!left) {
    buff[idx] = '0';
    idx--;
  } else {
    for (; left; left /= 10, idx--) buff[idx] = (int)(left % 10) + '0';
  }
  for (int i = 0; buff[idx + 1]; idx++, i++) {
    ret[i] = buff[idx + 1];
  }
}

int s21_isdigit(char c) { return (c >= '0' && c <= '9'); }
