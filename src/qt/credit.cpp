#include "credit.h"

#include <QMessageBox>

#include "../s21_cal/s21_calculator.h"
#include "QtCore/qregularexpression.h"
#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QDialog(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
}

Credit::~Credit() { delete ui; }
void Credit::credit_calc() {}
void Credit::set_Type() {
  if (ui->radioButton->isChecked()) {
    type = 1;
  } else if (ui->radioButton_2->isChecked()) {
    type = 2;
  }
}

void Credit::on_clear_clicked() {
  S = 0;
  m = 0;
  r = 0;
  type = 0;
  ui->credit_sum->setText("");
  ui->credit_tern_show->setText("");
  ui->credit_rate_show->setText("");
  ui->credit_payment_show->setText("");
  ui->credit_overpay_show->setText("");
  ui->credit_total_pay_show->setText("");
}
QString Credit::from_double_to_qstr(double x) {
  char strr[512];
  sprintf(strr, "%f", x);
  QString qstr = strr;
  return qstr;
}

bool Credit::checker(QString strr) {
  bool x = false;
  QRegularExpression regul("^\\-?[0-9]+([.][0-9]?)?$");
  QRegularExpressionMatch match_strr = regul.match(strr);
  if (match_strr.hasMatch()) {
    x = true;
  } else {
    QMessageBox::critical(this, "Ошибка!", "Введите пожалуйста цифры");
  }
  return x;
}

void Credit::on_sum_clicked() {
  QString qstr_S = ui->credit_sum->text();
  QString qstr_m = ui->credit_tern_show->text();
  QString qstr_r = ui->credit_rate_show->text();
  if (qstr_S.isEmpty() || qstr_m.isEmpty() || qstr_r.isEmpty()) {
    QMessageBox::critical(this, "Ошибка!", "Введите пожалуйста данные");
  } else if (checker(qstr_S) && checker(qstr_m) && checker(qstr_r)) {
    S = qstr_S.toDouble();
    m = qstr_m.toInt();
    r = qstr_r.toDouble();
    set_Type();
    calculate_credit(S, m, r, type, monthly_payment, &overpayment,
                     &total_payment);
    ui->credit_payment_show->setText(monthly_payment);
    ui->credit_overpay_show->setText(from_double_to_qstr(overpayment));
    ui->credit_total_pay_show->setText(from_double_to_qstr(total_payment));
  }
  // qDebug()<<"sw";
}
