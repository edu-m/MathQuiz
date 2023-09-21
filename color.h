// header for color manipulation

#pragma once
#include <stdarg.h>
#include <stdio.h>
#define RED 'r'
#define GREEN 'y'
#define BLUE 'b'
#define YELLOW 'y'

void red();

void green();

void blue();

void yellow();

void reset();

void print_c(const char c, const char *format, ...);
