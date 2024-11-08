#ifndef CUSTOMERSERVICEDEPARTMENT_H
#define CUSTOMERSERVICEDEPARTMENT_H

#include <vector>
#include <string>
#include "Department.h"
#include "Client.h"
#include "LogisticsDepartment.h"

class CustomerServiceDepartment : public Department {
private:
    std::vector<Client> clients;
    LogisticsDepartment* logisticsDepartment;

public:
    CustomerServiceDepartment(const std::vector<Employee>& employees, const std::vector<Client>& clients);

    std::vector<Client> getClients() const;
    void setClients(const std::vector<Client>& clients);

    void addClient(const Client& client);

    void setLogisticsDepartment(LogisticsDepartment* logisticsDepartment);

    void createTaskForLogistics(const std::string& name, const std::string& task);
};

#endif