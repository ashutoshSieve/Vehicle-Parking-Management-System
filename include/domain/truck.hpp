#ifndef TRUCK_HPP
#define TRUCK_HPP
#include<string>
#include<ctime>
#include"vehicle.hpp"
#include"pricing/feeCalculator.hpp"
class Truck:public Vehicle, public FeeCalculator{
    std::string VehicleType="Truck";
    public:
    Truck(std::string num);
    std::string getVehicleType() const override;
    double calculateFee(time_t in, time_t out)const override;
};
#endif