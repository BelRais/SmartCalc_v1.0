#ifndef SRC_S21_CALCULATOR_H
#define SRC_S21_CALCULATOR_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_n 256

struct stack {
  char *arr;
  int top;
};

struct stack_double {
  double *arr;
  int top;
};

struct stack_double *init_stack_double();
void push_stack_double(struct stack_double *a, double elem);
double pop_stack_double(struct stack_double *s);
void destroy_stack_double(struct stack_double *s);

struct stack *init();
void push(struct stack *s, char elem);
char peek(struct stack *s);
char pop(struct stack *s);
void destroy(struct stack *s);

int balance_brackets(char *str);
int is_numberOrSign(char a);
void remove_spaces(char *str, char *result);
int check_symbols(char *str, int i);
int validation_gut(char *str, char *ans);
int func(char *str, char *ans);
int priopity_of_functions(char a);
void postfix(char *str, char *postfix_str);
double operation_calc_binar(double a, double b, char oper, int *err);
double operation_calc_unar(double a, char oper);
int from_postfix(char *str, double *result, double x);
double s21_main_calculator(char *str, double x, int *err);

double calculate_annuity(double loan_amount, int term, double interest_rate);
double calculate_differentiated(double loan_amount, int term,
                                double interest_rate, double *D,
                                double *persent);
void calculate_credit(double loan_amount, int term, double interest_rate,
                      int type, char *monthly_payment, double *overpayment,
                      double *total_payment);

#endif  // SRC_S21_CALCULATOR_H