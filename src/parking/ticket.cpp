#include<string>
#include<ctime>
#include"parking/parkingSlot.hpp"
#include"domain/vehicle.hpp"
#include"parking/ticket.hpp"

Ticket::Ticket(int id, time_t tm, ParkSlot* slt, Vehicle* v):ticketId(id), entryTime(tm), slot(slt), vehicle(v){}
int Ticket::getId() const {return ticketId;}
time_t Ticket::getEntryTime() const {return entryTime;}
ParkSlot* Ticket::getSlot() {return slot;}
const ParkSlot* Ticket::getSlot() const {return slot;}
Vehicle* Ticket::getVehicle() { return vehicle; } 
const Vehicle* Ticket::getVehicle() const {return vehicle;}