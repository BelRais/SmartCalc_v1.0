#include "mainwindow.h"

#include <QMessageBox>

#include "../s21_cal/s21_calculator.h"
#include "credit.h"
#include "graphikwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->num_0, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->num_1, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->num_2, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->num_3, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->num_4, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->num_5, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->num_6, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->num_7, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->num_8, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->num_9, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->button_dot, SIGNAL(clicked()), this, SLOT(add()));

  connect(ui->button_equal, SIGNAL(clicked()), this, SLOT(result()));
  connect(ui->button_plus, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->button_minus, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->button_mult, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->button_div, SIGNAL(clicked()), this, SLOT(add()));

  connect(ui->button_sin, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->button_asin, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->button_cos, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->button_acos, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->button_atan, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->button_tan, SIGNAL(clicked()), this, SLOT(add()));

  connect(ui->button_in, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->button_rang, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->button_log, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->button_mod, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->button_sqrt, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->button_close, SIGNAL(clicked()), this, SLOT(add()));
  connect(ui->button_open, SIGNAL(clicked()), this, SLOT(add()));

  connect(ui->button_X, SIGNAL(clicked()), this, SLOT(add()));
}
QString MainWindow::from_double_to_qstr(double x) {
  char strr[512];
  sprintf(strr, "%f", x);
  QString qstr = strr;
  return qstr;
}
MainWindow::~MainWindow() { delete ui; }

void MainWindow::add() {
  QPushButton *button = (QPushButton *)sender();
  QString str;
  str = (ui->result_show_l->text() + button->text());
  ui->result_show_l->setText(str);
}

void MainWindow::on_button_AC_clicked() { ui->result_show_l->setText(""); }

void MainWindow::result() {
  double x = 0;
  int err = 0;
  bool ok = true;
  if (!ui->lineEdit_x->text().isEmpty()) {
    x = ui->lineEdit_x->text().toDouble(&ok);
  }
  if (!ok) {
    ui->result_show_l->setText("x isn't valid");
  } else {
    if (ui->result_show_l->text().length() < 256) {
      QByteArray ba = ui->result_show_l->text().toLocal8Bit();
      double res = s21_main_calculator(ba.data(), x, &err);
      if (err == 1) {
        ui->result_show_l->setText("Ошибка!");
      } else if (err == 0) {
        // QString result = QString::number(res, 'g', 7);
        ui->result_show_l->setText(from_double_to_qstr(res));
      } else {
        ui->result_show_l->setText("Ошибка!");
      }
    } else {
      ui->result_show_l->setText("too long for me :c");
    }
  }
}

void MainWindow::on_button_graf_clicked() {
  graphikWindow window;
  QString str = ui->result_show_l->text();
  window.set_Qstr(str);
  window.setModal(true);
  window.exec();
}

void MainWindow::on_button_credit_clicked() {
  Credit credit;
  credit.credit_calc();
  credit.setModal(true);
  credit.exec();
}

void MainWindow::on_button_deposit_clicked() {
  QMessageBox::critical(
      this, "Я не успел :с",
      "Дорогой пир, извини, что ты не сможешь посмотреть свои накопления, "
      "будет в версие 2.0 после дедлайна :)");
}
