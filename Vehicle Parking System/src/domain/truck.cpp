#include<string>
#include<ctime>
#include"domain/truck.hpp"
#include"domain/vehicle.hpp"

Truck::Truck(std::string num):Vehicle(num){}
std::string Truck::getVehicleType() const {return VehicleType;}
double Truck::calculateFee(time_t in, time_t out) const {
    long h = secondsToCeilHours(in, out);
    if (h <= 1) return 15.0;
    return 15.0 + (h - 1) * 10.0;
}