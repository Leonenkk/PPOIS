#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>

class Appointment {
private:
    std::string appointmentID;
    std::string patientID;
    std::string doctorID;
    std::string date;
    std::string time;
    std::string status;

public:
    Appointment(const std::string& appointmentID, const std::string& patientID, const std::string& doctorID,
               const std::string& date, const std::string& time, const std::string& status);

    void confirm();
    void cancel();
    void reschedule(const std::string& newDate, const std::string& newTime);

    std::string getAppointmentID() const;
    std::string getPatientID() const;
    std::string getDoctorID() const;
    std::string getDate() const;
    std::string getTime() const;
    std::string getStatus() const;
};

#endif
