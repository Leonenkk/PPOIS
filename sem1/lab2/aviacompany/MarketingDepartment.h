#ifndef MARKETINGDEPARTMENT_H
#define MARKETINGDEPARTMENT_H

#include "Department.h"
#include "FinanceDepartment.h"
#include <vector>
#include <string>

class MarketingDepartment : public Department {
private:
    std::vector<std::string> promotions;
    std::vector<std::string> areasOfAnalysis;
    FinanceDepartment* financeDepartment; // Ассоциация с FinanceDepartment

public:
    MarketingDepartment(const std::vector<Employee>& employees,
                        const std::vector<std::string>& promotions,
                        const std::vector<std::string>& areasOfAnalysis);

    std::vector<std::string> getPromotions() const;
    void setPromotions(const std::vector<std::string>& promotions);

    std::vector<std::string> getAreasOfAnalysis() const;
    void setAreasOfAnalysis(const std::vector<std::string>& areasOfAnalysis);

    void setFinanceDepartment(FinanceDepartment* financeDepartment);
    void sendMoneyToFinanceDepartment(int money);
};

#endif // MARKETINGDEPARTMENT_H
