#include "Billing.h"
#include <iostream>

Billing::Billing(const std::string& billID, const std::string& patientID, double amount,
                 const std::vector<std::string>& services, bool insuranceCovered)
    : billID(billID), patientID(patientID), amount(amount), services(services), insuranceCovered(insuranceCovered) {}

void Billing::generateInvoice() {
    std::cout << "Invoice ID: " << billID << "\n";
    std::cout << "Patient ID: " << patientID << "\n";
    std::cout << "Services: ";
    for (const auto& service : services) {
        std::cout << service << ", ";
    }
    std::cout << "\nTotal amount: $" << amount << "\n";

    if (insuranceCovered) {
        applyInsuranceDiscount();
    } else {
        std::cout << "No insurance coverage applied.\n";
    }
}

void Billing::applyInsuranceDiscount() {
    double discount = 0.20;  // Пример скидки 20%
    double discountAmount = amount * discount;
    amount -= discountAmount;
    std::cout << "Insurance discount applied: -$" << discountAmount << "\n";
    std::cout << "Amount after discount: $" << amount << "\n";
}

void Billing::markAsPaid() {
    std::cout << "Bill " << billID << " has been paid.\n";
}

std::string Billing::getBillID() const {
    return billID;
}

std::string Billing::getPatientID() const {
    return patientID;
}

double Billing::getAmount() const {
    return amount;
}

bool Billing::isInsuranceCovered() const {
    return insuranceCovered;
}

const std::vector<std::string>& Billing::getServices() const {
    return services;
}
