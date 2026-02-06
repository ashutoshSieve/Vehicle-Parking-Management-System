#ifndef RECEIPT_HPP
#define RECEIPT_HPP

#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include "utils/fileManager.hpp"
#include "parking/ticket.hpp"

namespace receipts {
    inline std::string format_time(time_t t) {
        std::tm tm{};
        #if defined(_WIN32)
            localtime_s(&tm, &t);
        #else
            tm = *std::localtime(&t);
        #endif
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    inline std::string build_receipt_text(const Ticket* t, double fee, time_t exitTime) {
        std::ostringstream oss;
        oss << "========== PARKING RECEIPT ==========\n";
        oss << "Ticket ID      : " << t->getId() << "\n";
        oss << "Vehicle        : " << t->getVehicle()->getVehicleType()
            << " [" << t->getVehicle()->getNumber() << "]\n";
        oss << "Slot           : " << t->getSlot()->getSlotId()
            << " (" << t->getSlot()->getSlotType() << ")\n";
        oss << "Entry Time     : " << format_time(t->getEntryTime()) << "\n";
        oss << "Exit  Time     : " << format_time(exitTime) << "\n";
        oss << "-------------------------------------\n";
        oss << "Total Fee (INR): " << fee << "\n";
        oss << "Generated At   : " << files::now_iso() << "\n";
        oss << "=====================================\n";
        return oss.str();
    }

    inline void write_receipt(const Ticket* t, double fee, time_t exitTime) {
        const std::string path = "receipts/ticket_" + std::to_string(t->getId()) + ".txt";
        const std::string text = build_receipt_text(t, fee, exitTime);
        files::write_text(path, text);
    }
}
#endif
