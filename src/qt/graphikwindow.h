#ifndef GRAPHIKWINDOW_H
#define GRAPHIKWINDOW_H

#include <QDialog>
#include <QVector>
#include <QtMath>

extern "C" {
#include "../s21_cal/s21_calculator.h"
}

namespace Ui {
class graphikWindow;
}

class graphikWindow : public QDialog {
  Q_OBJECT

 public:
  explicit graphikWindow(QWidget *parent = nullptr);
  ~graphikWindow();
  void graph_out(char *str);
  void set_Qstr(QString qstr);

 private slots:
  void on_pushButton_5_clicked();

 private:
  Ui::graphikWindow *ui;
  double xBegin, xEnd, yBegin, yEnd, h, X;
  QString qstr;

  QVector<double> x, y;
};

#endif  // GRAPHIKWINDOW_H
