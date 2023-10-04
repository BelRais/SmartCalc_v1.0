#include "s21_calculator.h"

struct stack_double *init_stack_double() {
  struct stack_double *s = malloc(sizeof(struct stack_double));
  if (s != NULL) {
    s->arr = malloc(max_n * sizeof(double));
    s->top = 0;
  }
  return s;
}
void push_stack_double(struct stack_double *a, double elem) {
  a->arr[a->top] = elem;
  a->top = a->top + 1;
}

struct stack *init() {
  struct stack *s = malloc(sizeof(struct stack));
  if (s != NULL) {
    s->arr = malloc(max_n * sizeof(char));
    s->top = 0;
  }
  return s;
}
void push(struct stack *s, char elem) {
  s->arr[s->top] = elem;
  s->top++;
}
char peek(struct stack *s) {
  char flag = '0';
  if (s->top != 0) {
    flag = s->arr[s->top - 1];
  }
  return flag;
}

char pop(struct stack *s) {
  char leksem = '0';
  if (s->top != 0) {
    leksem = s->arr[s->top - 1];
    s->top--;
  }
  return leksem;
}

double pop_stack_double(struct stack_double *s) {
  double leksem = 0.0;
  if (s->top != 0) {
    s->top--;
    leksem = s->arr[s->top];
    s->arr[s->top] = 0;
  }
  return leksem;
}
void destroy(struct stack *s) {
  if (s != NULL) {
    if (s->arr != NULL) {
      free(s->arr);
      s->top = 0;
    }
    free(s);
  }
}

void destroy_stack_double(struct stack_double *s) {
  if (s != NULL) {
    if (s->arr != NULL) {
      free(s->arr);
      s->top = 0;
    }
    free(s);
  }
}

int balance_brackets(char *str) {
  struct stack *f = init();
  int err = 0;
  for (int i = 0; i < (int)strlen(str) && err == 0; i++) {
    if (str[i] == '(') {
      push(f, str[i]);
    } else if (str[i] == ')') {
      if (peek(f) == '(') {
        pop(f);
      } else {
        err = 1;
      }
    }
  }
  if (f->top != 0) err = 1;
  destroy(f);
  return err;
}

int is_numberOrSign(char a) {
  int err = 0;
  if ((a >= '0' && a <= '9') || a == '/' || a == '*' || a == '(' || a == ')' ||
      a == '+' || a == '-' || a == '^' || a == 'x' || a == '.')
    err = 1;
  return err;
}

void remove_spaces(char *str, char *result) {
  int k = 0;
  for (int i = 0; i < (int)strlen(str); i++) {
    if (str[i] != ' ') result[k++] = str[i];
  }
  result[k] = '\0';
}

int check_symbols(char *str, int i) {
  int err = 0;
  if ((str[i] == '+' || str[i] == '-') &&
      (str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '^' ||
       str[i + 1] == 'm' || str[i + 1] == '\0')) {
    err = 1;
  } else if ((str[i] == '+' || str[i] == '-') &&
             (str[i + 1] == '+' || str[i + 1] == '-')) {
    err = 1;
  } else if ((str[i] == '*' || str[i] == '/' || str[i] == '^') &&
             (str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '^' ||
              str[i + 1] == 'm' || str[i + 1] == '\0')) {
    err = 1;
  } else if (str[i] == ')' &&
             (str[i + 1] == 'x' || (str[i + 1] >= '0' && str[i + 1] <= 9) ||
              str[i + 1] == 'c' || str[i + 1] == 's' || str[i + 1] == 't' ||
              str[i + 1] == 'a' || str[i + 1] == 'l')) {
    err = 1;
  } else if (str[i] == '(' &&
             (str[i + 1] == ')' || str[i + 1] == '*' || str[i + 1] == '/' ||
              str[i + 1] == 'm' || str[i + 1] == '^')) {
    err = 1;
  } else if (str[i] == '.' &&
             (str[i + 1] == '.' || str[i + 1] == '+' || str[i + 1] == '-' ||
              str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '(' ||
              str[i + 1] == ')' || str[i + 1] == '^' || str[i + 1] == 'm' ||
              str[i + 1] == 'c' || str[i + 1] == 's' || str[i + 1] == 't' ||
              str[i + 1] == 'a' || str[i + 1] == 'l')) {
    err = 1;
  }
  return err;
}

int validation_gut(char *str, char *ans) {
  int k = 0;
  int err = 0;
  for (int i = 0; i < (int)strlen(str) && err == 0; i++) {
    if (i + 2 < (int)strlen(str) && str[i] == 'c' && str[i + 1] == 'o' &&
        str[i + 2] == 's') {
      ans[k++] = 'c';
      i += 2;
    } else if (i + 2 < (int)strlen(str) && str[i] == 'm' && str[i + 1] == 'o' &&
               str[i + 2] == 'd') {
      ans[k++] = 'm';
      i += 2;
    } else if (i + 2 < (int)strlen(str) && str[i] == 's' && str[i + 1] == 'i' &&
               str[i + 2] == 'n') {
      ans[k++] = 's';
      i += 2;
    } else if (i + 2 < (int)strlen(str) && str[i] == 't' && str[i + 1] == 'a' &&
               str[i + 2] == 'n') {
      ans[k++] = 't';
      i += 2;
    } else if (i + 3 < (int)strlen(str) && str[i] == 'a' && str[i + 1] == 'c' &&
               str[i + 2] == 'o' && str[i + 3] == 's') {
      ans[k++] = 'C';
      i += 3;
    } else if (i + 3 < (int)strlen(str) && str[i] == 'a' && str[i + 1] == 's' &&
               str[i + 2] == 'i' && str[i + 3] == 'n') {
      ans[k++] = 'S';
      i += 3;
    } else if (i + 3 < (int)strlen(str) && str[i] == 'a' && str[i + 1] == 't' &&
               str[i + 2] == 'a' && str[i + 3] == 'n') {
      ans[k++] = 'T';
      i += 3;
    } else if (i + 3 < (int)strlen(str) && str[i] == 's' && str[i + 1] == 'q' &&
               str[i + 2] == 'r' && str[i + 3] == 't') {
      ans[k++] = 'q';
      i += 3;
    } else if (i + 1 < (int)strlen(str) && str[i] == 'l' && str[i + 1] == 'n') {
      ans[k++] = 'L';
      i += 1;
    } else if (i + 2 < (int)strlen(str) && str[i] == 'l' && str[i + 1] == 'o' &&
               str[i + 2] == 'g') {
      ans[k++] = 'l';
      i += 2;
    } else if (i == 0 && str[i] == '-') {
      ans[k++] = '0';
      ans[k++] = '-';
    } else if (i + 1 < (int)strlen(str) && str[i] == '(' && str[i + 1] == '-') {
      ans[k++] = '(';
      ans[k++] = '0';
    } else if (check_symbols(str, i)) {
      err = 1;
    } else if (is_numberOrSign(str[i])) {
      ans[k++] = str[i];
    } else {
      err = 1;
    }
  }
  ans[k] = '\0';
  return err;
}

int func(char *str, char *ans) {
  char res[255];
  remove_spaces(str, res);
  int err = 0;
  err = balance_brackets(res);
  if (err == 0) {
    err = validation_gut(res, ans);
  }
  return err;
}

int priopity_of_functions(char a) {
  int out = 1;
  if (a == 'c' || a == 's' || a == 't' || a == 'C' || a == 'S' || a == 'T' ||
      a == 'q' || a == 'l' || a == 'L' || a == '^')
    out = 4;
  if (a == '*' || a == '/' || a == 'm') out = 3;
  if (a == '+' || a == '-') out = 2;
  if (a == '(' || a == ')') out = 1;
  if ((a >= '0' && a <= '9') || a == '.') out = 0;
  return out;
}

void postfix(char *str, char *postfix_str) {
  struct stack *operators = init();
  char a[2];
  for (int i = 0; i < (int)strlen(str); i++) {
    if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == 'x') {
      sprintf(a, "%c", str[i]);
      strncat(postfix_str, a, 1);
    } else if (priopity_of_functions(str[i]) >= 2 &&
               priopity_of_functions(str[i]) <= 4) {
      strcat(postfix_str, " ");
      if (priopity_of_functions(peek(operators)) <
          priopity_of_functions(str[i])) {
        push(operators, str[i]);
      } else if (priopity_of_functions(peek(operators)) >=
                 priopity_of_functions(str[i])) {
        while (priopity_of_functions(peek(operators)) >=
               priopity_of_functions(str[i])) {
          sprintf(a, "%c", pop(operators));
          strncat(postfix_str, a, 1);
        }
        push(operators, str[i]);
      }
    } else if (str[i] == '(') {
      strcat(postfix_str, " ");
      push(operators, str[i]);
    } else if (str[i] == ')') {
      strcat(postfix_str, " ");
      while (peek(operators) != '(') {
        sprintf(a, "%c", pop(operators));
        strncat(postfix_str, a, 1);
        strcat(postfix_str, " ");
      }
      pop(operators);
    }
  }
  while (peek(operators) != '0') {
    strcat(postfix_str, " ");
    sprintf(a, "%c", pop(operators));
    strncat(postfix_str, a, 1);
  }
  destroy(operators);
}
double operation_calc_binar(double a, double b, char oper, int *err) {
  double res = 0;
  switch (oper) {
    case '+':
      res = a + b;
      break;
    case '-':
      res = a - b;
      break;
    case '*':
      res = a * b;
      break;
    case '/':
      if (b == 0)
        *err = 1;
      else
        res = a / b;
      break;
    case 'm':
      res = fmodl(a, b);
      break;
    case '^':
      res = pow(a, b);
      break;
  }
  return res;
}
double operation_calc_unar(double a, char oper) {
  double res = 0;
  switch (oper) {
    case 'c':
      res = cos(a);
      break;
    case 's':
      res = sin(a);
      break;
    case 't':
      res = tan(a);
      break;
    case 'C':
      res = acos(a);
      break;
    case 'S':
      res = asin(a);
      break;
    case 'T':
      res = atan(a);
      break;
    case 'q':
      res = sqrt(a);
      break;
    case 'L':
      res = log(a);
      break;
    case 'l':
      res = log10(a);
      break;
  }
  return res;
}

int from_postfix(char *str, double *result,
                 double x) {  //высчитывание постфиксной записи
  int err = 0;
  struct stack_double *st = init_stack_double();
  for (int i = 0; i < (int)strlen(str); i++) {
    if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.') {
      char number[max_n] = "";
      int k = 0;
      while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.') {
        number[k++] = str[i];
        i++;
      }
      number[k] = '\0';
      double a = atof(number);
      push_stack_double(st, a);
    } else if (str[i] == 'x') {
      push_stack_double(st, x);
    } else if (priopity_of_functions(str[i]) == 2 ||
               priopity_of_functions(str[i]) == 3 || str[i] == '^') {
      double b = pop_stack_double(st);
      if (st->top == 0) {
        err = 1;
      } else {
        double a = pop_stack_double(st);
        double c = operation_calc_binar(a, b, str[i], &err);
        if (err == 0) {
          push_stack_double(st, c);
        }
      }
    } else if (priopity_of_functions(str[i]) == 4) {
      double a = pop_stack_double(st);
      double c = operation_calc_unar(a, str[i]);
      push_stack_double(st, c);
    }
  }
  *result = pop_stack_double(st);
  destroy_stack_double(st);
  return err;
}

double s21_main_calculator(char *str, double x, int *err) {
  double result = 0;
  char ans[max_n] = "";
  *err = func(str, ans);

  if (*err == 0) {
    char post[max_n] = "";
    postfix(ans, post);
    *err = from_postfix(post, &result, x);
  }
  return result;
}

double calculate_annuity(double loan_amount, int term,
                         double interest_rate) {  // Спасибо ИУЭФ за формулу
  double j = 0;
  int m = 1;  // эта часть отвечала за переодичность, но формулу чутка переделал
  double rate_pre_mon =
      interest_rate / 100.0;  // переводим % в числовой вид (это еще в годах)
  double rate = rate_pre_mon / 12.0;  // переводим на 1 месяц %
  j = loan_amount * (rate / m * pow(1 + rate / m, term * m)) /
      (pow(1 + rate / m, term * m) - 1);
  return j;
}

double calculate_differentiated(double loan_amount, int term,
                                double interest_rate, double *D,
                                double *persent) {
  double j = 0;
  int m = 1;
  double base = 0;
  double rate = interest_rate / 100.0;
  base = loan_amount / (m * term * 1.0);
  *persent = *D * rate / 12.0;
  *D = *D - base;
  j = base + *persent;
  return j;
}

void calculate_credit(double loan_amount, int term, double interest_rate,
                      int type, char *monthly_payment, double *overpayment,
                      double *total_payment) {
  double payment = 0.0;
  double overpay = 0.0;
  double total_pay = 0.0;
  switch (type) {
    case 1: {  // annu
      payment = calculate_annuity(loan_amount, term, interest_rate);
      overpay = payment * term - loan_amount;
      total_pay = payment * term;
      sprintf(monthly_payment, "%.2f", payment);
      break;
    }
    case 2: {  // diff
      double D = loan_amount;
      double max_monthly_cal = 0;
      double min_monthly_cal = 0;
      for (int i = 1; i <= term; i++) {
        double monthly_cal = 0;
        double persent = 0;
        monthly_cal = calculate_differentiated(loan_amount, term, interest_rate,
                                               &D, &persent);
        if (i == 1) max_monthly_cal = monthly_cal;
        if (i == term) min_monthly_cal = monthly_cal;
        overpay += persent;
      }
      char w[256];
      sprintf(w, "%.2f %s %.2f", max_monthly_cal, "...", min_monthly_cal);
      total_pay = overpay + loan_amount;
      snprintf(monthly_payment, strlen(w) + 1, "%s", w);
      break;
    }
  }
  *overpayment = round(overpay * 100) / 100;
  *total_payment = round(total_pay * 100) / 100;
}