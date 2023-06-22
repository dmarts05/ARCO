#include "addvehicleformwindow.h"
#include "formhelpersnamespace.h"
#include "garage.h"
#include "ui_addvehicleformwindow.h"
#include <QMessageBox>

AddVehicleFormWindow::AddVehicleFormWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddVehicleFormWindow) {
  ui->setupUi(this);
}

AddVehicleFormWindow::~AddVehicleFormWindow() { delete ui; }

void AddVehicleFormWindow::resetForm() {
  // Reset line edits
  foreach (QLineEdit *widget, this->findChildren<QLineEdit *>()) {
    widget->clear();
  }

  // Reset check boxes
  foreach (QCheckBox *widget, this->findChildren<QCheckBox *>()) {
    widget->setChecked(false);
  }

  // Reset spin boxes
  foreach (QSpinBox *widget, this->findChildren<QSpinBox *>()) {
    widget->setValue(widget->minimum());
  }

  // Reset combo boxes
  foreach (QComboBox *widget, this->findChildren<QComboBox *>()) {
    widget->setCurrentIndex(0);
  }
}

void AddVehicleFormWindow::on_wagonNumSpinBox_valueChanged(int newValue) {
  // Sets this range for the spin box -> {0, [5, 20]}
  if (newValue > 0 && newValue < 5) {
    ui->wagonNumSpinBox->setValue(0);
    ui->wagonNumSpinBox->setSingleStep(5);
  } else {
    ui->wagonNumSpinBox->setSingleStep(1);
  }
}

void AddVehicleFormWindow::on_cancelBtn_clicked() { close(); }

void AddVehicleFormWindow::on_generatePlateBtn_clicked() {
  std::string plate;
  do {
    plate = FormHelpers::generatePlate();
  } while (FormHelpers::isPlateUsed(plate));
  ui->plateLineEdit->setText(QString::fromStdString(plate.c_str()));
}

void AddVehicleFormWindow::on_addVehicleBtn_clicked() {
  // Get data from form fields
  std::string name = this->ui->nameLineEdit->text().toStdString();
  std::string plate = this->ui->plateLineEdit->text().toStdString();

  std::string color = this->ui->colorComboBox->currentText().toStdString();

  int wheelNum =
      std::stoi(this->ui->wheelNumComboBox->currentText().toStdString());

  bool hasEngine = this->ui->engineCheckBox->isChecked();
  int engineHp = hasEngine ? this->ui->engineHpSpinBox->value() : 0;

  bool hasFuel = this->ui->fuelCheckBox->isChecked();
  std::string fuelType =
      hasFuel ? this->ui->fuelTypeComboBox->currentText().toStdString()
              : "No disponible";

  bool hasWings = this->ui->wingsCheckBox->isChecked();
  bool hasReactors = this->ui->reactorsCheckBox->isChecked();
  bool hasUndercarriage = this->ui->undercarriageCheckBox->isChecked();

  bool isLocomotive = this->ui->locomotiveCheckBox->isChecked();
  int wagonNum = this->ui->wagonNumSpinBox->value();

  std::string repairKit =
      this->ui->repairKitComboBox->currentText().toStdString();

  QMessageBox msgBox;
  msgBox.setFixedSize(500, 200);

  // Form field checks for creating a vehicle
  if (name.length() <= 0) {
    msgBox.critical(0, "Error", "El nombre del vehículo no puede estar vacío.");
    msgBox.show();
  } else if (plate.length() <= 0) {
    msgBox.critical(
        0, "Error",
        "Se debe generar una matrícula antes de crear el vehículo.");
    msgBox.show();
  } else if (FormHelpers::isNameUsed(name)) {
    msgBox.critical(0, "Error",
                    "El nombre de este vehículo ya se ha utilizado.");
    msgBox.show();
  } else {
    // No user input errors found
    // Get vehicle type
    std::string vehicleType = FormHelpers::getVehicleType(
        color, wheelNum, hasEngine, engineHp, hasFuel, fuelType, hasWings,
        hasReactors, hasUndercarriage, isLocomotive, wagonNum, repairKit);

    if (vehicleType.length() == 0) {
      // Show invalid vehicle message
      msgBox.critical(
          0, "Vehículo inválido",
          "El vehículo introducido no coincide con ningún vehículo válido.");
    } else {
      // Show new vehicle added to garage message
      std::string message = vehicleType + " añadido/a al garaje.";
      msgBox.information(0, "Vehículo agregado", message.c_str());

      // Add vehicle to garage
      Vehicle *vehicle =
          new Vehicle(vehicleType, name, plate, color, wheelNum, hasEngine,
                      engineHp, hasFuel, fuelType, hasWings, hasReactors,
                      hasUndercarriage, isLocomotive, wagonNum, repairKit);
      Garage::vehicles.push_back(*vehicle);

      // Send signal with new amount of vehicles in the garage to MainWindow
      emit vehiclesNumChanged(Garage::vehicles.size());

      // Reset form
      this->resetForm();
    }
  }
}
