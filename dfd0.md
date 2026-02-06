# Data Flow Diagram (DFD Level 0)

```mermaid
flowchart LR
    %% External Entities
    U[User / Operator]
    F[(Receipts Filesystem)]

    %% System
    S[[Vehicle Parking Management System]]

    %% Data Flows
    U -- Park Request (Vehicle No, Type, EntryTime) --> S
    S -- Ticket (TicketId, Slot, EntryTime) --> U

    U -- Unpark Request (TicketId, ExitTime) --> S
    S -- Fee Amount --> U

    %% Receipts
    S -- Receipt TXT --> F