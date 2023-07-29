// header for color manipulation

#include <stdarg.h>
#include <stdio.h>

void red() { printf("\033[1;31m"); }

void green() { printf("\033[1;32m"); }

void blue() { printf("\033[1;34m"); }

void yellow() { printf("\033[1;33m"); }

void reset() { printf("\033[0m"); }

void print_c(const char c, const char *format, ...) {
  va_list args;
  va_start(args, format);
  switch (c) {
  case 'r':
    red();
    break;
  case 'g':
    green();
    break;
  case 'b':
    blue();
    break;
  case 'y':
    yellow();
    break;
  }
  vprintf(format, args);
  va_end(args);
  reset();
}