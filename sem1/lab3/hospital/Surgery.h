#ifndef SURGERY_H
#define SURGERY_H

#include <string>

class OperatingRoom;

class Surgery {
private:
    std::string surgeryID;
    std::string patientID;
    std::string doctorID;
    std::string date;
    int duration;
    std::string status;
    OperatingRoom* operatingRoom;  // Ассоциация с операционной

public:
    Surgery(const std::string& surgeryID, const std::string& patientID, const std::string& doctorID,
            const std::string& date, int duration, const std::string& status);

    void schedule(OperatingRoom* room);
    void cancel();
    void complete();

    std::string getSurgeryID() const;
    std::string getStatus() const;
    std::string getDate() const;
    OperatingRoom* getOperatingRoom() const;
};

#endif
