#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>

extern "C" {
#include "../s21_cal/s21_calculator.h"
}

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();
  void set_Type();
  void credit_calc();
  QString from_double_to_qstr(double x);
  bool checker(QString strr);

 private slots:
  void on_clear_clicked();
  void on_sum_clicked();

 private:
  Ui::Credit *ui;
  double S, r;
  int m, type;
  char *monthly_payment;
  double overpayment, total_payment;
};

#endif  // CREDIT_H
