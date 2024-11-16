#include <gtest/gtest.h>
#include "../hospital/Appointment.h"


TEST(AppointmentTest, TestConstructorAndGetters) {
    Appointment appointment("1", "123", "456", "2024-11-15", "10:00", "Scheduled");

    // Проверяем, что методы get возвращают правильные значения
    EXPECT_EQ(appointment.getAppointmentID(), "1");
    EXPECT_EQ(appointment.getPatientID(), "123");
    EXPECT_EQ(appointment.getDoctorID(), "456");
    EXPECT_EQ(appointment.getDate(), "2024-11-15");
    EXPECT_EQ(appointment.getTime(), "10:00");
    EXPECT_EQ(appointment.getStatus(), "Scheduled");
}

TEST(AppointmentTest, TestConfirmMethod) {
    Appointment appointment("1", "123", "456", "2024-11-15", "10:00", "Scheduled");
    appointment.confirm();
    EXPECT_EQ(appointment.getStatus(), "Confirmed");
}

TEST(AppointmentTest, TestCancelMethod) {
    Appointment appointment("1", "123", "456", "2024-11-15", "10:00", "Scheduled");
    appointment.cancel();
    EXPECT_EQ(appointment.getStatus(), "Cancelled");
}

TEST(AppointmentTest, TestRescheduleMethod) {
    Appointment appointment("1", "123", "456", "2024-11-15", "10:00", "Scheduled");
    appointment.reschedule("2024-11-16", "12:00");
    EXPECT_EQ(appointment.getDate(), "2024-11-16");
    EXPECT_EQ(appointment.getTime(), "12:00");
    EXPECT_EQ(appointment.getStatus(), "Rescheduled");
}
