#include "Company.h"

Company::Company()
    : financeDepartment(FinanceDepartment(std::vector<Employee>(), 1000)),
      customerServiceDepartment(CustomerServiceDepartment(std::vector<Employee>(), std::vector<Client>())),
      itDepartment(ItDepartment(std::vector<Employee>(), 50)),
      logisticsDepartment(LogisticsDepartment(std::vector<Employee>(), std::vector<Aircraft>(), std::vector<Aircraft>(), &technicalDepartment)),
      marketingDepartment(MarketingDepartment(std::vector<Employee>(), std::vector<std::string>(), std::vector<std::string>())),
      securityDepartment(SecurityDepartment(std::vector<Employee>(), std::vector<std::string>(), std::vector<std::string>())),
      technicalDepartment(TechnicalDepartment(std::vector<Employee>(), std::vector<Aircraft>()))
{
    marketingDepartment.setFinanceDepartment(&financeDepartment);
    customerServiceDepartment.setLogisticsDepartment(&logisticsDepartment);
}

void Company::transferMoneyToFinanceDepartment(int count) {
    marketingDepartment.sendMoneyToFinanceDepartment(count);
}

void Company::transferAircraftToTechnicalDepartment(const std::string& model) {
    logisticsDepartment.sendAircraftToTechnicalDepartment(model);
}

void Company::createTask(const std::string& name, const std::string& task) {
    customerServiceDepartment.createTaskForLogistics(name, task);
}
