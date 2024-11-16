#include "OperatingRoom.h"
#include <iostream>

OperatingRoom::OperatingRoom(const std::string& roomID)
    : roomID(roomID), availability(true) {}

bool OperatingRoom::checkAvailability(const std::string& date) const {
    return availability;
}

void OperatingRoom::reserve(const std::string& date, int duration) {
    if (availability) {
        availability = false;
        std::cout << "Operating room " << roomID << " reserved for surgery on " << date << std::endl;
    }
}

void OperatingRoom::release() {
    availability = true;
    std::cout << "Operating room " << roomID << " released." << std::endl;
}

std::string OperatingRoom::getRoomID() const {
    return roomID;
}

bool OperatingRoom::isAvailable() const {
    return availability;
}
