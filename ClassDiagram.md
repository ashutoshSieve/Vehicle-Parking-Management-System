# Parking System UML

```mermaid
classDiagram
    direction LR

    %% ====== Core Domain ======
    class Vehicle {
      <<abstract>>
      - string VehicleNumber
      + Vehicle(string num)
      + getVehicleType() string*
      + getNumber() string
      + ~Vehicle()
    }

    class FeeCalculator {
      <<interface>>
      + calculateFee(time_t in, time_t out) double*
      + ~FeeCalculator()
    }

    class Bike {
      - string VehicleType = "Bike"
      + Bike(string)
      + getVehicleType() string
      + calculateFee(time_t, time_t) double
    }

    class Car {
      - string VehicleType = "Car"
      + Car(string)
      + getVehicleType() string
      + calculateFee(time_t, time_t) double
    }

    class ElectricCar {
      - string VehicleType = "ElectricCar"
      + ElectricCar(string)
      + getVehicleType() string
      + calculateFee(time_t, time_t) double
    }

    class Truck {
      - string VehicleType = "Truck"
      + Truck(string)
      + getVehicleType() string
      + calculateFee(time_t, time_t) double
    }

    Vehicle <|-- Bike
    Vehicle <|-- Car
    Vehicle <|-- ElectricCar
    Vehicle <|-- Truck

    FeeCalculator <|.. Bike
    FeeCalculator <|.. Car
    FeeCalculator <|.. ElectricCar
    FeeCalculator <|.. Truck

    %% ====== Parking Entities ======
    class ParkSlot {
      - int slotId
      - bool occupied
      - string slotType   "Small|Medium|Large"
      + ParkSlot(int, string)
      + getSlotId() int
      + getSlotType() string
      + isOccupied() bool
      + occupy() void
      + free() void
    }

    class Ticket {
      - int ticketId
      - time_t entryTime
      - ParkSlot* slot
      - Vehicle* vehicle
      + Ticket(int, time_t, ParkSlot*, Vehicle*)
      + getId() int
      + getEntryTime() time_t
      + getSlot() ParkSlot*
      + getSlot() const ParkSlot*
      + getVehicle() Vehicle*
      + getVehicle() const Vehicle*
    }

    class ParkingLot {
      - queue<ParkSlot*> small
      - queue<ParkSlot*> medium
      - queue<ParkSlot*> large
      - unordered_map<int, Ticket*> activeTicket
      - int smallCapacity
      - int mediumCapacity
      - int largeCapacity
      - int nextIdGenrator
      + ParkingLot(int,int,int)
      + ~ParkingLot()
      + park(Vehicle*, time_t) Ticket*
      + unpark(int, time_t) double
      -- helpers --
      - acquireSlotFor(string) ParkSlot*
      - releaseSlot(ParkSlot*) void
    }

    %% Ownership/associations
    ParkingLot "1" o--> "0..*" ParkSlot : owns
    ParkingLot "1" --> "0..*" Ticket : manages
    Ticket "1" --> "1" ParkSlot : holds
    Ticket "1" --> "1" Vehicle : holds

    %% ====== Utilities ======
    class Receipt {
      <<utility>>
      + write_receipt(const Ticket*, double, time_t) void
      + build_receipt_text(const Ticket*, double, time_t) string
    }

    class Files {
      <<utility>>
      + now_iso() string
      + parent_dir(string) string
      + ensure_dir(string) void
      + write_text(string, string) void
      + write_text_strict(string, string) void
    }

    ParkingLot ..> Receipt : uses on unpark()
    Receipt ..> Files : uses for write