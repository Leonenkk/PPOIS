#include "gtest/gtest.h"
#include "Pharmacy.h"
#include "Prescription.h"

TEST(PharmacyTest, TestDispenseMedication) {
    Pharmacy pharmacy("P001", "New York");
    Prescription prescription("RX001", "D001", "P001");
    prescription.addMedication("Aspirin", "500mg", 7);
    prescription.addMedication("Cough Syrup", "10ml", 5);
    pharmacy.receivePrescription(&prescription);
    pharmacy.restock("Aspirin", 10);
    pharmacy.restock("Cough Syrup", 5);
    pharmacy.dispenseMedication(prescription);
    pharmacy.checkInventory("Aspirin");
    pharmacy.checkInventory("Cough Syrup");
}

TEST(PharmacyTest, TestRestockAndInventory) {
    Pharmacy pharmacy("P002", "Los Angeles");
    pharmacy.restock("Paracetamol", 20);
    pharmacy.restock("Antibiotics", 10);
    pharmacy.checkInventory("Paracetamol");
    pharmacy.checkInventory("Antibiotics");
    pharmacy.checkInventory("Aspirin");
}