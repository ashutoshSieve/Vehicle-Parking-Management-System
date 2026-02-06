#ifndef PARKINGLOT_HPP
#define PARKINGLOT_HPP
#include<queue>
#include<ctime>
#include<unordered_map>
#include"ticket.hpp"
#include"parkingSlot.hpp"


class ParkingLot{
    std::queue<ParkSlot*>small;
    std::queue<ParkSlot*>medium;
    std::queue<ParkSlot*>large;
    int smallCapacity=0;
    int mediumCapacity=0;
    int largeCapacity=0;
    int nextIdGenrator=1;
    public:
    std::unordered_map<int,Ticket*>activeTicket;
    ParkingLot(int, int, int);
    ~ParkingLot();
    Ticket* park(Vehicle* vh, time_t entryTime=std::time(nullptr));
    ParkSlot* acquireSlotFor(const std::string& vehicleType);
    void releaseSlot(ParkSlot*);
    double unpark(int ticketId, time_t exitTime = std::time(nullptr));
};
#endif