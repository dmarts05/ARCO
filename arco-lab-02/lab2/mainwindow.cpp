#include "mainwindow.h"
#include "addvehicleformwindow.h"
#include "garagewindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setVehicleNumLabelText(int vehicleNum) {
  this->ui->vehiclesNumLabel->setText("N.º de vehículos en el garaje: " +
                                      QString::number(vehicleNum));
}

void MainWindow::on_showAddVehicleFormBtn_clicked() {
  AddVehicleFormWindow addVehicleFormWindow;
  addVehicleFormWindow.setModal(true);
  connect(&addVehicleFormWindow, &AddVehicleFormWindow::vehiclesNumChanged,
          this, &MainWindow::setVehicleNumLabelText);
  addVehicleFormWindow.exec();
}

void MainWindow::on_showGarageBtn_clicked() {
  GarageWindow garageWindow;
  garageWindow.setModal(true);
  garageWindow.exec();
}
