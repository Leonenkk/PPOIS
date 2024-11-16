#ifndef OPERATINGROOM_H
#define OPERATINGROOM_H

#include <string>
#include <vector>

class Surgery;

class OperatingRoom {
private:
    std::string roomID;
    std::vector<std::string> equipmentList;
    bool availability;

public:
    explicit OperatingRoom(const std::string& roomID);

    bool checkAvailability(const std::string& date) const;
    void reserve(const std::string& date, int duration);
    void release();

    std::string getRoomID() const;
    bool isAvailable() const;
};

#endif
