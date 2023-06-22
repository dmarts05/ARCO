#include "formhelpersnamespace.h"
#include "garage.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

namespace FormHelpers {
bool isNameUsed(std::string name) {
  bool used = false;

  for (auto &vehicle : Garage::vehicles) {
    if (vehicle.getName() == name) {
      used = true;
      break;
    }
  }

  return used;
}

bool isPlateUsed(std::string plate) {
  bool used = false;

  for (auto &vehicle : Garage::vehicles) {
    if (vehicle.getPlate() == plate) {
      used = true;
      break;
    }
  }

  return used;
}

std::string generatePlate() {
  srand(time(nullptr));
  std::string plate = "";
  std::string letters = "BCFGHJKLMNPRSTVWXYZ";

  // Generate 4 random numbers for the plate
  for (int i = 0; i < 4; i++) {
    plate += std::to_string(rand() % 10);
  }

  // Generate 3 random letters for the plate
  for (int i = 0; i < 3; i++) {
    plate += letters[rand() % letters.length()];
  }

  return plate;
}

std::string getVehicleType(std::string color, int wheelNum, bool hasEngine,
                           int engineHp, bool hasFuel, std::string fuelType,
                           bool hasWings, bool hasReactors,
                           bool hasUndercarriage, bool isLocomotive,
                           int wagonNum, std::string repairKit) {

  std::string vehicleType;

  if (wheelNum == 2 && !hasEngine && !hasFuel && !hasWings && !hasReactors &&
      !hasUndercarriage && !isLocomotive && wagonNum == 0 &&
      repairKit == "Kit de reparación de pinchazos") {
    // Bicycle
    vehicleType = "Bicicleta";
  } else if (wheelNum == 3 && !hasEngine && !hasFuel && !hasWings &&
             !hasReactors && !hasUndercarriage && !isLocomotive &&
             wagonNum == 0 && repairKit == "Kit de reparación de pinchazos") {
    // Tricycle
    vehicleType = "Triciclo";
  } else if (wheelNum == 2 && hasEngine && engineHp >= 80 && engineHp <= 450 &&
             hasFuel &&
             (fuelType == "Eléctrico" || fuelType == "Gasolina" ||
              fuelType == "Diésel" || fuelType == "Híbrido") &&
             !hasWings && !hasReactors && !hasUndercarriage && !isLocomotive &&
             wagonNum == 0 && repairKit == "Kit de reparación de pinchazos") {
    // Motorbike
    vehicleType = "Motocicleta";
  } else if (wheelNum == 4 && hasEngine && engineHp >= 80 && engineHp <= 250 &&
             hasFuel &&
             (fuelType == "Eléctrico" || fuelType == "Gasolina" ||
              fuelType == "Diésel" || fuelType == "Híbrido") &&
             !hasWings && !hasReactors && !hasUndercarriage && !isLocomotive &&
             wagonNum == 0 && repairKit == "Rueda de repuesto") {
    // Car
    vehicleType = "Coche";
  } else if (wheelNum == 4 && hasEngine && engineHp > 250 && engineHp <= 450 &&
             hasFuel && (fuelType == "Eléctrico" || fuelType == "Gasolina") &&
             !hasWings && !hasReactors && !hasUndercarriage && !isLocomotive &&
             wagonNum == 0 && repairKit == "Kit de reparación de pinchazos") {
    // Sports car
    vehicleType = "Coche deportivo";
  } else if (wheelNum == 6 && hasEngine && engineHp == 450 && hasFuel &&
             fuelType == "Queroseno" && color == "Blanco" && hasWings &&
             hasReactors && hasUndercarriage && !isLocomotive &&
             wagonNum == 0 && repairKit == "Rueda de repuesto") {
    // Plane
    vehicleType = "Avión";
  } else if (wheelNum == 40 && hasEngine && engineHp == 450 && hasFuel &&
             (fuelType == "Eléctrico" || fuelType == "Diésel") &&
             color == "Negro" && !hasWings && !hasReactors &&
             !hasUndercarriage && isLocomotive && wagonNum >= 5 &&
             wagonNum <= 20 && repairKit == "Rueda de repuesto") {
    // Train
    vehicleType = "Tren";

  } else {
    // Invalid vehicle
    vehicleType = "";
  }

  return vehicleType;
}
} // namespace FormHelpers
