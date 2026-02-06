#include<string>
#include<queue>
#include<ctime>
#include<iostream>
#include<stdexcept>
#include<unordered_map>
#include"parking/parkingLot.hpp"
#include"parking/parkingSlot.hpp"
#include"parking/ticket.hpp"
#include"pricing/feeCalculator.hpp"
#include"domain/vehicle.hpp"
#include"utils/receipt.hpp"

ParkingLot::ParkingLot(int sm, int md, int lg):smallCapacity(sm), mediumCapacity(md), largeCapacity(lg){
    int id = 1;
    for (int i=0; i<smallCapacity; ++i) {
        auto* s=new ParkSlot(id++, "Small");
        small.push(s);
    }
    for (int i=0; i <mediumCapacity; ++i) {
        auto* s=new ParkSlot(id++, "Medium");
        medium.push(s);
    }
    for (int i=0; i<largeCapacity; ++i) {
        auto* s=new ParkSlot(id++, "Large");
        large.push(s);
    }
}
ParkingLot::~ParkingLot() {
    for (auto& kv : activeTicket) {
        delete kv.second;
    }
    activeTicket.clear();
}
ParkSlot* ParkingLot::acquireSlotFor(const std::string& type){
    if(type=="Car" || type=="Electric Car"){
        if (medium.empty()) return nullptr;
        auto* m = medium.front(); medium.pop();
        m->Occupy();return m;
    }else if(type=="Bike"){
        if (small.empty()) return nullptr;
        auto* s = small.front(); small.pop();
        s->Occupy();return s;
    }else if(type=="Truck"){
        if (large.empty()) return nullptr;
        auto* l = large.front(); large.pop();
        l->Occupy();return l;
    }
    return nullptr;
}
Ticket* ParkingLot::park(Vehicle* vh, time_t entryTime){
    if(!vh) return nullptr;
    std::string type=vh->getVehicleType();
    ParkSlot* slot=acquireSlotFor(type);
    if(!slot) return nullptr;
    Ticket* tckt=new Ticket(nextIdGenrator++,entryTime,slot,vh);
    activeTicket[tckt->getId()]=tckt;
    return tckt;
}
void ParkingLot::releaseSlot(ParkSlot* s){
    s->free();
    const std::string& t = s->getSlotType();
    if      (t == "Small")  small.push(s);
    else if (t == "Medium") medium.push(s);
    else if (t == "Large")  large.push(s);
}
double ParkingLot::unpark(int ticketId, time_t exitTime){
    auto it=activeTicket.find(ticketId);
    if (it==activeTicket.end()) {
        throw std::runtime_error("Invalid ticket id");
    }
    Ticket* tc=it->second;
    auto sl=it->second->getSlot();
    time_t entTime=it->second->getEntryTime();
    std::string vType=it->second->getVehicle()->getVehicleType();
    auto vh=it->second->getVehicle();

    const FeeCalculator* strategy = dynamic_cast<FeeCalculator*>(vh);
    double amount=strategy->calculateFee(entTime,exitTime);

    try {
        receipts::write_receipt(tc, amount, exitTime);
    } catch (const std::exception& e) {
        std::cerr << "Receipt write failed: " << e.what() << "\n";
    }

    releaseSlot(sl);
    activeTicket.erase(it);
    delete tc;
    return amount;
}