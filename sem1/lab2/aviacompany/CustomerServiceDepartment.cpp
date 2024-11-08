#include "CustomerServiceDepartment.h"
#include <algorithm>

CustomerServiceDepartment::CustomerServiceDepartment(const std::vector<Employee>& employees, const std::vector<Client>& clients)
    : Department(employees), clients(clients), logisticsDepartment(nullptr) {}

std::vector<Client> CustomerServiceDepartment::getClients() const {
    return clients;
}

void CustomerServiceDepartment::setClients(const std::vector<Client>& clients) {
    this->clients = clients;
}

void CustomerServiceDepartment::addClient(const Client& client) {
    clients.push_back(client);
}

void CustomerServiceDepartment::setLogisticsDepartment(LogisticsDepartment* logisticsDepartment) {
    this->logisticsDepartment = logisticsDepartment;
}

void CustomerServiceDepartment::createTaskForLogistics(const std::string& name, const std::string& task) {
    clients.erase(std::remove_if(clients.begin(), clients.end(),
                                 [&name](const Client& client) { return client.getName() == name; }),
                  clients.end());

    if (logisticsDepartment) {
        logisticsDepartment->addTask(task);
    }
}