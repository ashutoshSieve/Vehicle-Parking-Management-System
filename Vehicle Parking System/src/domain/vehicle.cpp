#include<string>
#include"domain/vehicle.hpp"
Vehicle::Vehicle(std::string num):VehicleNumber(num){}
const std::string Vehicle::getNumber() const{return VehicleNumber;}