#include <gtest/gtest.h>
#include "Billing.h"

TEST(BillingTest, TestConstructorAndGetters) {
    std::vector<std::string> services = {"Consultation", "X-ray"};
    Billing bill("BILL001", "123", 500.0, services, true);

    // Проверяем, что геттеры возвращают правильные значения
    EXPECT_EQ(bill.getBillID(), "BILL001");
    EXPECT_EQ(bill.getPatientID(), "123");
    EXPECT_EQ(bill.getAmount(), 500.0);
    EXPECT_TRUE(bill.isInsuranceCovered());
    EXPECT_EQ(bill.getServices().size(), 2);
    EXPECT_EQ(bill.getServices()[0], "Consultation");
    EXPECT_EQ(bill.getServices()[1], "X-ray");
}

TEST(BillingTest, TestGenerateInvoiceWithoutInsurance) {
    std::vector<std::string> services = {"Consultation", "Blood Test"};
    Billing bill("BILL002", "124", 300.0, services, false);

    EXPECT_NO_THROW(bill.generateInvoice());
}

TEST(BillingTest, TestGenerateInvoiceWithInsurance) {
    std::vector<std::string> services = {"Surgery", "Post-op care"};
    Billing bill("BILL003", "125", 1000.0, services, true);

    EXPECT_NO_THROW(bill.generateInvoice());
    EXPECT_EQ(bill.getAmount(), 800.0);
}

TEST(BillingTest, TestMarkAsPaid) {
    std::vector<std::string> services = {"Emergency Care"};
    Billing bill("BILL004", "126", 150.0, services, true);

    EXPECT_NO_THROW(bill.markAsPaid());
}
