#include<string>
#include"parking/parkingSlot.hpp"

ParkSlot::ParkSlot(int id, std::string sType): slotId(id), occupied(0), slotType(sType){}
int ParkSlot::getSlotId()const{return slotId;}
std::string ParkSlot::getSlotType() const{return slotType;}
bool ParkSlot::isOccupied() const{return occupied;}
void ParkSlot::Occupy(){occupied=true;}
void ParkSlot::free(){occupied=false;}