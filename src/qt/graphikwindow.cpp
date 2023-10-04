#include "graphikwindow.h"

#include "../s21_cal/s21_calculator.h"
#include "ui_graphikwindow.h"

graphikWindow::graphikWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::graphikWindow) {
  ui->setupUi(this);
}
void graphikWindow::set_Qstr(QString stri) {
  qstr = stri;
  QByteArray ba = qstr.toLocal8Bit();
  char *str = ba.data();
  graph_out(str);
}

void graphikWindow::graph_out(char *str) {
  h = 0.1;
  xBegin = ui->lineEdit_xmin->text().toDouble();
  xEnd = ui->lineEdit_xmax->text().toDouble();
  yBegin = ui->lineEdit_ymin->text().toDouble();
  yEnd = ui->lineEdit_ymax->text().toDouble();

  ui->widget->clearGraphs();

  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange(yBegin, yEnd);

  int err = 0;

  if (err == 0) {
    for (X = xBegin; X <= xEnd; X += h) {
      double Y = s21_main_calculator(str, X, &err);
      x.push_back(X);
      y.push_back(Y);
    }
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
  x.clear();
  y.clear();
}

graphikWindow::~graphikWindow() { delete ui; }

void graphikWindow::on_pushButton_5_clicked() {
  bool bol = true;
  if (ui->lineEdit_xmin->text().isEmpty()) {
    xBegin = -10;
    ui->lineEdit_xmin->setText("-10");
  }
  if (ui->lineEdit_xmax->text().isEmpty()) {
    xEnd = 10;
    ui->lineEdit_xmax->setText("10");
  }
  if (ui->lineEdit_ymin->text().isEmpty()) {
    yBegin = -10;
    ui->lineEdit_ymin->setText("-10");
  }
  if (ui->lineEdit_ymax->text().isEmpty()) {
    yEnd = 10;
    ui->lineEdit_ymin->setText("10");
  }

  QString min_x_str = ui->lineEdit_xmin->text();
  QString max_x_str = ui->lineEdit_xmax->text();
  QString min_y_str = ui->lineEdit_ymin->text();
  QString max_y_str = ui->lineEdit_ymax->text();

  QRegularExpression regul("^\\-?[0-9]+([.][0-9]?)?$");
  QRegularExpressionMatch match_min_x = regul.match(min_x_str);
  QRegularExpressionMatch match_max_x = regul.match(max_x_str);
  QRegularExpressionMatch match_min_y = regul.match(min_y_str);
  QRegularExpressionMatch match_max_y = regul.match(max_y_str);
  if (match_min_x.hasMatch() && match_max_x.hasMatch() &&
      match_min_y.hasMatch() && match_max_y.hasMatch()) {
    double x_min = min_x_str.toDouble(&bol);
    double x_max = max_x_str.toDouble(&bol);
    double y_min = min_y_str.toDouble(&bol);
    double y_max = max_y_str.toDouble(&bol);
    if (!bol || x_min < -1000000 || x_min > 1000000 || x_max < -1000000 ||
        x_max > 1000000 || y_min < -1000000 || y_min > 1000000 ||
        y_max < -1000000 || y_max > 1000000) {
      QMessageBox::critical(this, "Ошибка!",
                            "Неправильно введённые данные! Данные должны быть "
                            "в пределах -1000000 и 1000000!");
    } else {
      set_Qstr(this->qstr);
    }
  } else {
    QMessageBox::critical(this, "Ошибка!", "Неправильно введённые данные!");
  }
}
