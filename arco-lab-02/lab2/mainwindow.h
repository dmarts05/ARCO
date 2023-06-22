#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
  void on_showAddVehicleFormBtn_clicked();

  void on_showGarageBtn_clicked();

private:
  Ui::MainWindow *ui;

  void setVehicleNumLabelText(int vehicleNum);
};
#endif // MAINWINDOW_H
