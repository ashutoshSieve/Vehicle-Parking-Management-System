#include<string>
#include<ctime>
#include"domain/car.hpp"
#include"domain/vehicle.hpp"

Car::Car(std::string num):Vehicle(num){}
std::string Car::getVehicleType() const {return VehicleType;}
double Car::calculateFee(time_t in, time_t out) const {
    long h = secondsToCeilHours(in, out);
    if (h <= 1) return 20.0;
    return 20.0 + (h - 1) * 15.0;
}