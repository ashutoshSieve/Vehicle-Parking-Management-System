#ifndef ELECAR_HPP
#define ELECAR_HPP
#include<string>
#include<ctime>
#include"vehicle.hpp"
#include"pricing/feeCalculator.hpp"
class EleCar:public Vehicle, public FeeCalculator{
    std::string VehicleType="Electric Car";
    public:
    EleCar(std::string num);
    std::string getVehicleType() const override;
    double calculateFee(time_t in, time_t out) const override;
};
#endif