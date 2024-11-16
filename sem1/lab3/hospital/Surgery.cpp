#include "Surgery.h"
#include "OperatingRoom.h"
#include <iostream>

Surgery::Surgery(const std::string& surgeryID, const std::string& patientID, const std::string& doctorID,
                 const std::string& date, int duration, const std::string& status)
    : surgeryID(surgeryID), patientID(patientID), doctorID(doctorID), date(date), duration(duration),
      status(status), operatingRoom(nullptr) {}

void Surgery::schedule(OperatingRoom* room) {
    if (room->checkAvailability(date)) {
        operatingRoom = room;
        status = "Scheduled";
        room->reserve(date, duration);
        std::cout << "Surgery scheduled in operating room " << operatingRoom->getRoomID() << std::endl;
    } else {
        std::cout << "Operating room is not available." << std::endl;
    }
}

void Surgery::cancel() {
    status = "Cancelled";
    if (operatingRoom) {
        operatingRoom->release();
        std::cout << "Surgery cancelled and operating room released." << std::endl;
    }
}

void Surgery::complete() {
    status = "Completed";
    std::cout << "Surgery completed." << std::endl;
}

std::string Surgery::getSurgeryID() const {
    return surgeryID;
}

std::string Surgery::getStatus() const {
    return status;
}

std::string Surgery::getDate() const {
    return date;
}

OperatingRoom* Surgery::getOperatingRoom() const {
    return operatingRoom;
}
