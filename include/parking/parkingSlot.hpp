#ifndef PARKSLOT_HPP
#define PARKSLOT_HPP
#include<string>
class ParkSlot{
    int slotId;
    bool occupied;
    std::string slotType;
    public:
    ParkSlot(int id, std::string slotType);
    int getSlotId()const;
    std::string getSlotType() const;
    bool isOccupied() const;
    void Occupy();
    void free();
};
#endif