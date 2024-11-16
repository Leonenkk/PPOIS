#include <gtest/gtest.h>
#include "Equipment.h"
#include <ctime>

std::tm createdTestDate(int day, int month, int year) {
    std::tm date = {};
    date.tm_mday = day;
    date.tm_mon = month - 1;  // Месяцы от 0 до 11
    date.tm_year = year - 1900;  // Год начиная с 1900
    return date;
}

TEST(EquipmentTest, TestConstructorAndGetters) {
    std::tm testDate = createdTestDate(15, 8, 2023);
    Equipment equipment("E001", "X-Ray", "Radiology", testDate);

    EXPECT_EQ(equipment.getEquipmentID(), "E001");
    EXPECT_EQ(equipment.getName(), "X-Ray");
    EXPECT_EQ(equipment.getType(), "Radiology");

    std::tm maintenanceDate = equipment.getMaintenanceDate();
    EXPECT_EQ(maintenanceDate.tm_mday, 15);
    EXPECT_EQ(maintenanceDate.tm_mon, 7);  // Месяц август (8-й)
    EXPECT_EQ(maintenanceDate.tm_year, 123);  // 2023 - 1900 = 123
}

TEST(EquipmentTest, TestScheduleMaintenance) {
    std::tm testDate = createdTestDate(15, 8, 2023);
    Equipment equipment("E001", "X-Ray", "Radiology", testDate);

    std::tm newDate = createdTestDate(1, 12, 2023);
    equipment.scheduleMaintenance(newDate);

    std::tm maintenanceDate = equipment.getMaintenanceDate();
    EXPECT_EQ(maintenanceDate.tm_mday, 1);
    EXPECT_EQ(maintenanceDate.tm_mon, 11);  // Месяц декабрь
    EXPECT_EQ(maintenanceDate.tm_year, 123);  // 2023 - 1900 = 123
}

TEST(EquipmentTest, TestCheckStatus) {
    std::tm testDate = createdTestDate(15, 8, 2023);
    Equipment equipment("E001", "X-Ray", "Radiology", testDate);

    testing::internal::CaptureStdout();
    equipment.checkStatus();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Equipment: X-Ray") != std::string::npos);
    EXPECT_TRUE(output.find("Type: Radiology") != std::string::npos);
    EXPECT_TRUE(output.find("Last maintenance date: 15/8/2023") != std::string::npos);
}
