#include "gtest/gtest.h"
#include "Medication.h"
#include <ctime>

std::tm createTestDate(int day, int month, int year) {
    std::tm date = {};
    date.tm_mday = day;
    date.tm_mon = month - 1;
    date.tm_year = year - 1900;
    return date;
}

TEST(MedicationTest, CorrectConstructorAndPropertyRetrieval) {
    std::tm expiryDate = createTestDate(31, 12, 2025);
    Medication med("M001", "Paracetamol", "Painkiller", 10.5, expiryDate);

    EXPECT_EQ(med.getMedicationID(), "M001");
    EXPECT_EQ(med.getName(), "Paracetamol");
    EXPECT_EQ(med.getType(), "Painkiller");
    EXPECT_DOUBLE_EQ(med.getPrice(), 10.5);
    EXPECT_EQ(med.getExpiryDate().tm_mday, 31);
    EXPECT_EQ(med.getExpiryDate().tm_mon, 11);
    EXPECT_EQ(med.getExpiryDate().tm_year, 125);
}

TEST(MedicationTest, ExpiryDateValidation) {
    std::tm expiryDate = createTestDate(31, 12, 2025);
    Medication med("M001", "Paracetamol", "Painkiller", 10.5, expiryDate);
    EXPECT_TRUE(med.checkExpiry());

    expiryDate = createTestDate(1, 1, 2020);
    med.setExpiryDate(expiryDate);
    EXPECT_FALSE(med.checkExpiry());
}

TEST(MedicationTest, ExpiryDateUpdate) {
    std::tm initialExpiryDate = createTestDate(31, 12, 2025);
    Medication med("M001", "Paracetamol", "Painkiller", 10.5, initialExpiryDate);

    EXPECT_EQ(med.getExpiryDate().tm_mday, 31);
    EXPECT_EQ(med.getExpiryDate().tm_mon, 11);  // Декабрь
    EXPECT_EQ(med.getExpiryDate().tm_year, 125); // 2025 - 1900

    std::tm newExpiryDate = createTestDate(1, 1, 2027);
    med.setExpiryDate(newExpiryDate);

    EXPECT_EQ(med.getExpiryDate().tm_mday, 1);
    EXPECT_EQ(med.getExpiryDate().tm_mon, 0);  // Январь
    EXPECT_EQ(med.getExpiryDate().tm_year, 127); // 2027 - 1900
}
