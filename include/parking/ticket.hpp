#ifndef TICKET_HPP
#define TICKET_HPP
#include<string>
#include<ctime>
#include"parkingSlot.hpp"
#include"domain/vehicle.hpp"

class Ticket{
    int ticketId;
    time_t entryTime;
    ParkSlot* slot;
    Vehicle* vehicle;
    public:
    Ticket(int id, time_t tm, ParkSlot* slt, Vehicle* v);
    int getId() const;
    time_t getEntryTime() const;
    ParkSlot* getSlot();
    const ParkSlot* getSlot() const;
    Vehicle* getVehicle();
    const Vehicle* getVehicle() const;
};
#endif
