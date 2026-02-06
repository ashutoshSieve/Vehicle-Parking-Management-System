#include<string>
#include<ctime>
#include"domain/electricCar.hpp"
#include"domain/vehicle.hpp"

EleCar::EleCar(std::string num):Vehicle(num){}
std::string EleCar::getVehicleType() const {return VehicleType;}
double EleCar::calculateFee(time_t in, time_t out) const {
    long h = secondsToCeilHours(in, out);
    if (h <= 1) return 40.0;
    return 40.0 + (h - 1) * 25.0;
}
