#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

extern "C" {
#include "../s21_cal/s21_calculator.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QString from_double_to_qstr(double x);

 private:
  Ui::MainWindow *ui;

 private slots:
  void add();
  void on_button_AC_clicked();
  // void on_pushButton_result_clicked();
  void result();
  void on_button_graf_clicked();
  void on_button_credit_clicked();
  void on_button_deposit_clicked();
};
#endif  // MAINWINDOW_H
