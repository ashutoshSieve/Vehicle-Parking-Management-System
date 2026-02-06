#include <iostream>
#include <ctime>
#include <stdexcept>
#include "parking/parkingLot.hpp"
#include "parking/parkingSlot.hpp"
#include "parking/ticket.hpp"
#include "domain/vehicle.hpp"
#include "domain/car.hpp"
#include "domain/bike.hpp"
#include "domain/truck.hpp"
#include "domain/electricCar.hpp"

static void print_ticket(const char* tag, const Ticket* t) {
    if (!t) {
        std::cout << tag << ": (no ticket)\n";
        return;
    }
    std::cout << tag<< " -> Ticket#" << t->getId()<< " | Slot#" << t->getSlot()->getSlotId()
              << " (" << t->getSlot()->getSlotType() << ")"
              << " | Vehicle: " << t->getVehicle()->getVehicleType()
              << " [" << t->getVehicle()->getNumber() << "]\n";
}

int main() {
    try {
        ParkingLot lot(1, 2, 1);
        time_t base = std::time(nullptr);

        Vehicle* car1  = new Car("MH-12-AB-0001");
        Vehicle* bike1 = new Bike("MH-12-XY-1111");
        Vehicle* truck1 = new Truck("MH-12-TT-2222");
        Vehicle* ev1   = new EleCar("MH-12-EV-3333");
        Vehicle* truck2 = new Truck("MH-12-TT-4444"); 
        
        Ticket* tCar1  = lot.park(car1,   base +   0 * 60);
        Ticket* tBike1 = lot.park(bike1,  base +   2 * 60);
        Ticket* tTruck1= lot.park(truck1, base +   5 * 60);
        Ticket* tEv1   = lot.park(ev1,    base +   7 * 60);

        std::cout << "=== After Parking ===\n";
        print_ticket("Car1 ",  tCar1);
        print_ticket("Bike1",  tBike1);
        print_ticket("Truck1", tTruck1);
        print_ticket("EV1  ",  tEv1);

        Ticket* tTruck2_fail = lot.park(truck2, base + 10 * 60);
        if (!tTruck2_fail) {
            std::cout << "Truck2: No Large slot available\n";
        }

        // Car1: park ~now, unpark after 2.5 hours
        if (tCar1) {
            time_t exitCar1 = tCar1->getEntryTime() + (2 * 3600) + (30 * 60);
            double fee = lot.unpark(tCar1->getId(), exitCar1);
            std::cout << "Unpark Car1 (Ticket#" << tCar1->getId() << "): Fee = Rs" << fee << "\n";
            delete car1;  car1 = nullptr;
        }

        // Bike1: unpark after 45 minutes (should ceil to 1 hour)
        if (tBike1) {
            time_t exitBike1 = tBike1->getEntryTime() + (45 * 60);
            double fee = lot.unpark(tBike1->getId(), exitBike1);
            std::cout << "Unpark Bike1 (Ticket#" << tBike1->getId() << "): Fee = Rs" << fee << "\n";
            delete bike1; bike1 = nullptr;
        }

        // EV1: unpark after 1 hour 10 minutes
        if (tEv1) {
            time_t exitEv1 = tEv1->getEntryTime() + (1 * 3600) + (10 * 60);
            double fee = lot.unpark(tEv1->getId(), exitEv1);
            std::cout << "Unpark EV1 (Ticket#" << tEv1->getId() << "): Fee = Rs" << fee << "\n";
            delete ev1; ev1 = nullptr;
        }

        // Truck1: unpark after 3 hours
        if (tTruck1) {
            time_t exitTruck1 = tTruck1->getEntryTime() + (3 * 3600);
            double fee = lot.unpark(tTruck1->getId(), exitTruck1);
            std::cout << "Unpark Truck1 (Ticket#" << tTruck1->getId() << "): Fee = Rs" << fee << "\n";
            delete truck1; truck1 = nullptr;
        }

        // ---- Now that the Large slot is free, try to park Truck2 again (should succeed) ----
        Ticket* tTruck2 = lot.park(truck2, base + 12 * 60);
        print_ticket("Truck2 (2nd attempt)", tTruck2);
        if (tTruck2) {
            time_t exitTruck2 = tTruck2->getEntryTime() + (30 * 60);
            double fee = lot.unpark(tTruck2->getId(), exitTruck2);
            std::cout << "Unpark Truck2 (Ticket#" << tTruck2->getId() << "): Fee = Rs" << fee << "\n";
            delete truck2; truck2 = nullptr;
        } else {
            std::cout << "Unexpected: Truck2 still couldn't park.\n";
            delete truck2; truck2 = nullptr;
        }

        // ---- Show error handling: invalid ticket ----
        try {
            (void)lot.unpark(999999, base + 1000); // invalid id
            std::cout << "Unexpected: unpark(999999) succeeded\n";
        } catch (const std::exception& e) {
            std::cout << "invalid unpark: " << e.what() << "\n";
        }

        std::cout << "=== Demo complete ===\n";
        return 0;
    }catch (const std::exception& ex) {
        std::cerr << "Fatal error: " << ex.what() << "\n";
        return 1;
    }
}