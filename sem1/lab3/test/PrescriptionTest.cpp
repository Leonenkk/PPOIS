#include "gtest/gtest.h"
#include "Prescription.h"
#include "Pharmacy.h"

TEST(PrescriptionTest, TestAddMedicationAndPrint) {
    Prescription prescription("RX001", "D001", "P001");
    prescription.addMedication("Aspirin", "500mg", 7);
    prescription.addMedication("Cough Syrup", "10ml", 5);
    EXPECT_EQ(prescription.getMedications().size(), 2);
    EXPECT_EQ(prescription.getMedications()[0], "Aspirin");
    EXPECT_EQ(prescription.getDosage()[0], "500mg");
    EXPECT_EQ(prescription.getDuration()[0], 7);
    prescription.printPrescription();
}

TEST(PrescriptionTest, TestUpdateDosage) {
    Prescription prescription("RX001", "D001", "P001");
    prescription.addMedication("Aspirin", "500mg", 7);
    prescription.updateDosage("Aspirin", "600mg");
    EXPECT_EQ(prescription.getDosage()[0], "600mg");
}

TEST(PrescriptionTest, TestSendToPharmacy) {
    Pharmacy pharmacy("P003", "Chicago");
    Prescription prescription("RX002", "D002", "P002");
    prescription.sendToPharmacy(&pharmacy);
    EXPECT_EQ(prescription.getPharmacy(), &pharmacy);
}