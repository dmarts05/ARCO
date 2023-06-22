#include "vehicle.h"

Vehicle::Vehicle(std::string vehicleType, std::string name, std::string plate,
                 std::string color, int wheelNum, bool hasEngine, int engineHp,
                 bool hasFuel, std::string fuelType, bool hasWings,
                 bool hasReactors, bool hasUndercarriage, bool isLocomotive,
                 int wagonNum, std::string repairKit) {
  this->vehicleType = vehicleType;
  this->name = name;
  this->plate = plate;

  this->color = color;

  this->wheelNum = wheelNum;

  this->hasEngine = hasEngine;
  this->engineHp = engineHp;

  this->hasFuel = hasFuel;
  this->fuelType = fuelType;

  this->hasWings = hasWings;
  this->hasReactors = hasReactors;
  this->hasUndercarriage = hasUndercarriage;

  this->isLocomotive = isLocomotive;
  this->wagonNum = wagonNum;

  this->repairKit = repairKit;
}

Vehicle::~Vehicle() {}

std::string Vehicle::getVehicleType() const { return vehicleType; }

std::string Vehicle::getName() const { return name; }

std::string Vehicle::getPlate() const { return plate; }

std::string Vehicle::getColor() const { return color; }

int Vehicle::getWheelNum() const { return wheelNum; }

bool Vehicle::getHasEngine() const { return hasEngine; }

int Vehicle::getEngineHp() const { return engineHp; }

bool Vehicle::getHasFuel() const { return hasFuel; }

std::string Vehicle::getFuelType() const { return fuelType; }

bool Vehicle::getHasWings() const { return hasWings; }

bool Vehicle::getHasReactors() const { return hasReactors; }

bool Vehicle::getHasUndercarriage() const { return hasUndercarriage; }

bool Vehicle::getIsLocomotive() const { return isLocomotive; }

int Vehicle::getWagonNum() const { return wagonNum; }

std::string Vehicle::getRepairKit() const { return repairKit; }
