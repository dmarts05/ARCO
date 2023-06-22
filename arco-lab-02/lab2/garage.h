#ifndef GARAGE_H
#define GARAGE_H

#include "vehicle.h"
#include <vector>

class Garage {
public:
  static std::vector<Vehicle> vehicles;
  Garage() = delete;
};

#endif // GARAGE_H
