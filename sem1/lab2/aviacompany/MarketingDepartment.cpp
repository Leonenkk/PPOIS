#include "MarketingDepartment.h"

MarketingDepartment::MarketingDepartment(const std::vector<Employee>& employees,
                                         const std::vector<std::string>& promotions,
                                         const std::vector<std::string>& areasOfAnalysis)
    : Department(employees), promotions(promotions), areasOfAnalysis(areasOfAnalysis), financeDepartment(nullptr) {}

std::vector<std::string> MarketingDepartment::getPromotions() const {
    return promotions;
}

void MarketingDepartment::setPromotions(const std::vector<std::string>& promotions) {
    this->promotions = promotions;
}

std::vector<std::string> MarketingDepartment::getAreasOfAnalysis() const {
    return areasOfAnalysis;
}

void MarketingDepartment::setAreasOfAnalysis(const std::vector<std::string>& areasOfAnalysis) {
    this->areasOfAnalysis = areasOfAnalysis;
}

void MarketingDepartment::setFinanceDepartment(FinanceDepartment* financeDepartment) {
    this->financeDepartment = financeDepartment;
}

void MarketingDepartment::sendMoneyToFinanceDepartment(int money) {
    if (financeDepartment) {
        financeDepartment->addMoneyToBudget(money);
    }
}
