#ifndef GARAGEWINDOW_H
#define GARAGEWINDOW_H

#include <QDialog>

namespace Ui {
class GarageWindow;
}

class GarageWindow : public QDialog {
  Q_OBJECT

public:
  explicit GarageWindow(QWidget *parent = nullptr);
  ~GarageWindow();

private slots:
  void on_showHomeBtn_clicked();

private:
  Ui::GarageWindow *ui;
};

#endif // GARAGEWINDOW_H
