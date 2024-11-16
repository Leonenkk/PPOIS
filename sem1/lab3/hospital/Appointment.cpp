#include "Appointment.h"

Appointment::Appointment(const std::string& appointmentID, const std::string& patientID,
                         const std::string& doctorID, const std::string& date,
                         const std::string& time, const std::string& status)
    : appointmentID(appointmentID), patientID(patientID), doctorID(doctorID),
      date(date), time(time), status(status) {}

void Appointment::confirm() {
    status = "Confirmed";
}

void Appointment::cancel() {
    status = "Cancelled";
}

void Appointment::reschedule(const std::string& newDate, const std::string& newTime) {
    date = newDate;
    time = newTime;
    status = "Rescheduled";
}

std::string Appointment::getAppointmentID() const {
    return appointmentID;
}

std::string Appointment::getPatientID() const {
    return patientID;
}

std::string Appointment::getDoctorID() const {
    return doctorID;
}

std::string Appointment::getDate() const {
    return date;
}

std::string Appointment::getTime() const {
    return time;
}

std::string Appointment::getStatus() const {
    return status;
}
