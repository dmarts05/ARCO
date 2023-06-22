#ifndef FORMHELPERSNAMESPACE_H
#define FORMHELPERSNAMESPACE_H

#include <iostream>

namespace FormHelpers {
bool isNameUsed(std::string name);

bool isPlateUsed(std::string plate);

std::string generatePlate();

std::string getVehicleType(std::string color, int wheelNum, bool hasEngine,
                           int engineHp, bool hasFuel, std::string fuelType,
                           bool hasWings, bool hasReactors,
                           bool hasUndercarriage, bool isLocomotive,
                           int wagonNum, std::string repairKit);
} // namespace FormHelpers

#endif // FORMHELPERSNAMESPACE_H
