#include "garagewindow.h"
#include "garage.h"
#include "qpushbutton.h"
#include "ui_garagewindow.h"
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

GarageWindow::GarageWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::GarageWindow) {
  ui->setupUi(this);

  // Set up vehicle GUI info
  QVector<QGroupBox *> vehicleGroupBoxes;
  for (auto &vehicle : Garage::vehicles) {
    QGridLayout *layout = new QGridLayout();

    QLabel *typeLabel =
        new QLabel(QString::fromStdString("Tipo: " + vehicle.getVehicleType()));

    QLabel *nameLabel =
        new QLabel(QString::fromStdString("Nombre: " + vehicle.getName()));

    QLabel *wheelNumLabel = new QLabel("Número de ruedas: " +
                                       QString::number(vehicle.getWheelNum()));

    std::string engineLabelMsg = "Motor: ";
    engineLabelMsg += vehicle.getHasEngine() ? "Disponible" : "No disponible";
    QLabel *engineLabel = new QLabel(QString::fromStdString(engineLabelMsg));

    QLabel *engineHpLabel = new QLabel("Potencia del motor (cv): " +
                                       QString::number(vehicle.getEngineHp()));

    std::string fuelLabelMsg = "Combustible: ";
    fuelLabelMsg += vehicle.getHasFuel() ? "Disponible" : "No disponible";
    QLabel *fuelLabel = new QLabel(QString::fromStdString(fuelLabelMsg));

    QLabel *fuelTypeLabel =
        new QLabel("Tipo de combustible: " +
                   QString::fromStdString(vehicle.getFuelType()));

    QLabel *colorLabel =
        new QLabel("Color: " + QString::fromStdString(vehicle.getColor()));

    std::string wingLabelMsg = "Alas: ";
    wingLabelMsg += vehicle.getHasWings() ? "Disponible" : "No disponible";
    QLabel *wingLabel = new QLabel(QString::fromStdString(wingLabelMsg));

    std::string reactorsLabelMsg = "Reactores: ";
    reactorsLabelMsg +=
        vehicle.getHasReactors() ? "Disponible" : "No disponible";
    QLabel *reactorsLabel =
        new QLabel(QString::fromStdString(reactorsLabelMsg));

    std::string undercarriageLabelMsg = "Tren de aterrizaje: ";
    undercarriageLabelMsg +=
        vehicle.getHasUndercarriage() ? "Disponible" : "No disponible";
    QLabel *undercarriageLabel =
        new QLabel(QString::fromStdString(undercarriageLabelMsg));

    std::string locomotiveLabelMsg = "Locomotora: ";
    locomotiveLabelMsg +=
        vehicle.getIsLocomotive() ? "Disponible" : "No disponible";
    QLabel *locomotiveLabel =
        new QLabel(QString::fromStdString(locomotiveLabelMsg));

    QLabel *wagonNumLabel =
        new QLabel("N.º de vagones: " + QString::number(vehicle.getWagonNum()));

    QLabel *repairKitLabel =
        new QLabel(QString::fromStdString("Kit: " + vehicle.getRepairKit()));

    QLabel *plateLabel =
        new QLabel(QString::fromStdString("Matrícula: " + vehicle.getPlate()));

    // Row 1
    layout->addWidget(typeLabel, 0, 0, 1, 1);
    layout->addWidget(nameLabel, 0, 1, 1, 1);
    layout->addWidget(wheelNumLabel, 0, 2, 1, 1);

    // Row 2
    layout->addWidget(engineLabel, 1, 0, 1, 1);
    layout->addWidget(engineHpLabel, 1, 1, 1, 1);
    layout->addWidget(fuelLabel, 1, 2, 1, 1);

    // Row 3
    layout->addWidget(fuelTypeLabel, 2, 0, 1, 1);
    layout->addWidget(colorLabel, 2, 1, 1, 1);
    layout->addWidget(wingLabel, 2, 2, 1, 1);

    // Row 4
    layout->addWidget(reactorsLabel, 3, 0, 1, 1);
    layout->addWidget(undercarriageLabel, 3, 1, 1, 1);
    layout->addWidget(locomotiveLabel, 3, 2, 1, 1);

    // Row 5
    layout->addWidget(wagonNumLabel, 4, 0, 1, 1);
    layout->addWidget(repairKitLabel, 4, 1, 1, 1);
    layout->addWidget(plateLabel, 4, 2, 1, 1);

    // Add label styling
    for (int i = 0; i < layout->count(); i++) {
      QLabel *label = (QLabel *)layout->itemAt(i)->widget();
      label->setAlignment(Qt::AlignCenter);
      if (label->text().toStdString().find("Tipo:") != std::string::npos ||
          label->text().toStdString().find("Nombre:") != std::string::npos) {
        label->setFont(QFont("Sans Serif", 15, QFont::Bold));
      } else {
        label->setFont(QFont("Sans Serif", 15));
      }
    }

    QGroupBox *groupBox = new QGroupBox();
    groupBox->setLayout(layout);

    vehicleGroupBoxes.push_back(groupBox);
  }

  // Insert vehicle widgets
  QVBoxLayout *layout = new QVBoxLayout();
  for (auto &groupBox : vehicleGroupBoxes) {
    layout->addWidget(groupBox);
  }

  // Insert close btn
  QPushButton *showHomeBtn = new QPushButton("Inicio");
  this->connect(showHomeBtn, &QPushButton::released, this,
                &GarageWindow::on_showHomeBtn_clicked);
  this->ui->verticalLayout->addWidget(showHomeBtn);

  this->ui->scrollAreaWidgetContents->setLayout(layout);
}

GarageWindow::~GarageWindow() { delete ui; }

void GarageWindow::on_showHomeBtn_clicked() { this->close(); }
