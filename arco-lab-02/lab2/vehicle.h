#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>

class Vehicle {
private:
  std::string vehicleType;
  std::string name;
  std::string plate;

  std::string color;

  int wheelNum;

  bool hasEngine;
  int engineHp;

  bool hasFuel;
  std::string fuelType;

  bool hasWings;
  bool hasReactors;
  bool hasUndercarriage;

  bool isLocomotive;
  int wagonNum;

  std::string repairKit;

public:
  Vehicle(std::string vehicleType, std::string name, std::string plate,
          std::string color, int wheelNum, bool hasEngine, int engineHp,
          bool hasFuel, std::string fuelType, bool hasWings, bool hasReactors,
          bool hasUndercarriage, bool isLocomotive, int wagonNum,
          std::string repairKit);
  ~Vehicle(void);

  std::string getVehicleType() const;
  std::string getName() const;
  std::string getPlate() const;

  std::string getColor() const;

  int getWheelNum() const;

  bool getHasEngine() const;
  int getEngineHp() const;

  bool getHasFuel() const;
  std::string getFuelType() const;

  bool getHasWings() const;
  bool getHasReactors() const;
  bool getHasUndercarriage() const;

  bool getIsLocomotive() const;
  int getWagonNum() const;

  std::string getRepairKit() const;
};

#endif // VEHICLE_H
