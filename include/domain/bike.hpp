#ifndef BIKE_HPP
#define BIKE_HPP
#include<string>
#include<ctime>
#include"vehicle.hpp"
#include"pricing/feeCalculator.hpp"
class Bike:public Vehicle, public FeeCalculator{
    std::string VehicleType="Bike";
    public:
    Bike(std::string num);
    std::string getVehicleType() const override;
    double calculateFee(time_t in, time_t out) const override;
};
#endif
