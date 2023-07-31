#include "color.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_NUM 24
#define MAX_INPUT_SIZE 64
#define MAIN_LOOP while (q_amt-- > 0)
#define RED 'r'
#define GREEN 'y'
#define BLUE 'b'
#define YELLOW 'y'

static int _add(const int *x, const int *y) { return *x + *y; }
static int _mul(const int *x, const int *y) { return *x * *y; }
static int _sub(const int *x, const int *y) { return *x - *y; }
static int _div(const int *x, const int *y) { return *x / *y; }

static void die(const char *fmt, ...) {
  va_list argp;
  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  va_end(argp);
  fputc('\n', stderr);
  exit(1);
}

void banner() { printf("\t\t\tMath Quiz\n\n\t\t  By Eduardo Meli 2023\n\n"); }

typedef enum { OP_ADD, OP_MUL, OP_SUB, OP_DIV } op_type;

int get_value(const char *op) {
  switch (*op) {
  case '+':
    return OP_ADD;
  case '*':
    return OP_MUL;
  case '-':
    return OP_SUB;
  case '/':
    return OP_DIV;
  default:
    return -1;
  }
}

void parse_input(char *s, char *p,
                 long *input) { // parse the input to ignore all non-integers
  // printf("%lu", strlen(s));
  while (fgets(s, MAX_INPUT_SIZE, stdin)) {
    *input = strtol(s, &p, 10);
    if (strlen(s) >= 10 || (p == s || *p != '\n'))
      printf("Please enter a valid integer: ");
    else
      break;
  }
}

void op_gen(char *op, char *ops, int *n1, int *n2) {
  *op = ops[rand() % 4];
  *n1 = rand() % MAX_NUM + 1;
  // generates a "friendlier" set of numbers
  // to compute when division occurs so that
  // there will always an integer division
  // with lowish numbers in the denominator
  *n1 += (*op == '/' && *n1 % 2 != 0);
  if (*op == '/')
    do {
      *n2 = ((rand() % *n1 / 2)) + 2;
    } while (*n1 % *n2 != 0);
  else
    *n2 = rand() % MAX_NUM;
}

void parse_args(int argc, char **argv, int *q_amt) {
  const char *arg;
  int user_amt;
  *q_amt = 10;
  for (int i = 1; i < argc; i++) {
    if (*argv[i] != '-')
      continue;
    if (*(argv[i] + 1) == 'c' && (user_amt = atoi(argv[i] + 2)) > 0)
      *q_amt = user_amt;
    else
      die("Invalid value. Please insert a value greater than zero.");
  }
}

int compare(const int *input, const int *result) { return (*input == *result); }

void print_score(const int *correct_answers) {
  print_c(BLUE, "Correct Answers: %d\n", *correct_answers);
}

void handle_input_correct(int *correct_answers, const int *result) {
  ++(*correct_answers);
  print_c(GREEN, "Correct!\n");
  print_score(correct_answers);
}

void handle_input_wrong(int *correct_answers, const int *result) {
  print_c(RED, "Result is %d. Try again!\n", *result);
  print_score(correct_answers);
}

int main(int argc, char **argv) {
  srand(time(NULL));
  banner();
  char ops[4] = {'*', '+', '-', '/'};
  int (*fx[4])(const int *, const int *) = {_add, _mul, _sub, _div};
  void (*handle_outcomes[2])(int *, const int *) = {handle_input_wrong,
                                                    handle_input_correct};
  int n1, n2, result, q_amt;
  char op, *p, s[MAX_INPUT_SIZE];
  long input;

  int correct_answers = 0;
  parse_args(argc, argv, &q_amt);
  int value, q_amt_copy = q_amt;
  MAIN_LOOP {
    op_gen(&op, ops, &n1, &n2);
    printf("%d %c %d\n> ", n1, op, n2);
    parse_input(s, p, &input);
    if ((value = get_value(&op)) == -1)
      die("An error has occured and the application was shut down.");
    result = fx[value](&n1, &n2);
    handle_outcomes[compare((int *)&input, &result)](&correct_answers, &result);
  }
  printf("\a\aYou scored %d out of %d! (%d%%)\n", correct_answers, q_amt_copy,
         (correct_answers * 100 / q_amt_copy));
  return 0;
}
