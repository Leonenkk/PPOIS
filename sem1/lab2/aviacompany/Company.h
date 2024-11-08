#ifndef COMPANY_H
#define COMPANY_H

#include "FinanceDepartment.h"
#include "CustomerServiceDepartment.h"
#include "ItDepartment.h"
#include "LogisticsDepartment.h"
#include "MarketingDepartment.h"
#include "SecurityDepartment.h"
#include "TechnicalDepartment.h"

class Company {
private:
    FinanceDepartment financeDepartment;
    CustomerServiceDepartment customerServiceDepartment;
    ItDepartment itDepartment;
    LogisticsDepartment logisticsDepartment;
    MarketingDepartment marketingDepartment;
    SecurityDepartment securityDepartment;
    TechnicalDepartment technicalDepartment;

public:
    Company();

    void transferMoneyToFinanceDepartment(int count);
    void transferAircraftToTechnicalDepartment(const std::string& model);
    void createTask(const std::string& name, const std::string& task);
};

#endif // COMPANY_H