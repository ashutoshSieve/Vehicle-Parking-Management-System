#ifndef VEHICLE_HPP
#define VEHICLE_HPP
#include <string>
class Vehicle{
    std::string VehicleNumber;
    public:
    Vehicle(std::string num);
    const std::string getNumber() const;
    virtual std::string getVehicleType()const=0;
    virtual ~Vehicle()=default;
};
#endif