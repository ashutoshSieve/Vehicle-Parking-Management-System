#include<string>
#include"domain/bike.hpp"
#include"domain/vehicle.hpp"
#include<ctime>
Bike::Bike(std::string num):Vehicle(num){}
std::string Bike::getVehicleType() const {return VehicleType;}
double Bike::calculateFee(time_t in, time_t out) const {
    long h = secondsToCeilHours(in, out);
    if (h <= 1) return 20.0;
    return 20.0 + (h - 1) * 10.0;
}
