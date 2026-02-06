#ifndef CAR_HPP
#define CAR_HPP
#include<string>
#include<ctime>
#include"vehicle.hpp"
#include"pricing/feeCalculator.hpp"
class Car:public Vehicle, public FeeCalculator{
    std::string VehicleType="Car";
    public:
    Car(std::string num);
    std::string getVehicleType() const override;
    double calculateFee(time_t in, time_t out) const override;
};
#endif
