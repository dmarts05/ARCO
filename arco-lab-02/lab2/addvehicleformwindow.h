#ifndef ADDVEHICLEFORMWINDOW_H
#define ADDVEHICLEFORMWINDOW_H

#include <QDialog>
#include <iostream>

namespace Ui {
class AddVehicleFormWindow;
}

class AddVehicleFormWindow : public QDialog {
  Q_OBJECT

public:
  explicit AddVehicleFormWindow(QWidget *parent = nullptr);
  ~AddVehicleFormWindow();

private slots:
  void on_wagonNumSpinBox_valueChanged(int newValue);

  void on_cancelBtn_clicked();

  void on_generatePlateBtn_clicked();

  void on_addVehicleBtn_clicked();

signals:
  void vehiclesNumChanged(int newVehiclesNum);

private:
  Ui::AddVehicleFormWindow *ui;

  void resetForm();
};

#endif // ADDVEHICLEFORMWINDOW_H
