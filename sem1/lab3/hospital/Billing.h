#ifndef BILLING_H
#define BILLING_H

#include <string>
#include <vector>

class Billing {
private:
    std::string billID;
    std::string patientID;
    double amount;
    std::vector<std::string> services;
    bool insuranceCovered;

public:
    Billing(const std::string& billID, const std::string& patientID, double amount,
            const std::vector<std::string>& services, bool insuranceCovered);

    void generateInvoice();
    void applyInsuranceDiscount();
    void markAsPaid();

    std::string getBillID() const;
    std::string getPatientID() const;
    double getAmount() const;
    bool isInsuranceCovered() const;
    const std::vector<std::string>& getServices() const;
};

#endif
