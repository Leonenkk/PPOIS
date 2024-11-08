#include "gtest/gtest.h"
#include "CustomerServiceDepartment.h"
#include "Client.h"
#include "Employee.h"
#include "LogisticsDepartment.h"

class CustomerServiceDepartmentTest : public ::testing::Test {
protected:
    CustomerServiceDepartment* customerService;
    LogisticsDepartment* logisticsDepartment;

    void SetUp() override {
        std::vector<Employee> employees = {
            Employee("Alice", 30, 5000, 5, 1),
            Employee("Bob", 40, 6000, 10, 2)
        };

        std::vector<Client> clients = {
            Client("Alice", 30, Order("USA", 101, 1, 1)),
            Client("Bob", 40, Order("Canada", 102, 2, 2))
        };

        logisticsDepartment = new LogisticsDepartment(employees, {}, {}, nullptr);
        customerService = new CustomerServiceDepartment(employees, clients);
        customerService->setLogisticsDepartment(logisticsDepartment);
    }

    void TearDown() override {
        delete customerService;
        delete logisticsDepartment;
    }
};

TEST_F(CustomerServiceDepartmentTest, GetAndSetClients) {
    std::vector<Client> clients = customerService->getClients();
    EXPECT_EQ(clients.size(), 2);

    std::vector<Client> newClients = { Client("Charlie", 25, Order("UK", 103, 3, 3)) };
    customerService->setClients(newClients);

    clients = customerService->getClients();
    EXPECT_EQ(clients.size(), 1);
    EXPECT_EQ(clients[0].getName(), "Charlie");
}

TEST_F(CustomerServiceDepartmentTest, AddClient) {
    Client newClient("Dave", 35, Order("Germany", 104, 4, 4));
    customerService->addClient(newClient);

    std::vector<Client> clients = customerService->getClients();
    EXPECT_EQ(clients.size(), 3);
    EXPECT_EQ(clients.back().getName(), "Dave");
}

TEST_F(CustomerServiceDepartmentTest, CreateTaskForLogistics) {
    customerService->createTaskForLogistics("Alice", "Deliver urgent package");

    std::vector<Client> clients = customerService->getClients();
    EXPECT_EQ(clients.size(), 1);
    EXPECT_EQ(clients[0].getName(), "Bob");

    std::vector<std::string> tasks = logisticsDepartment->getTasks();
    EXPECT_EQ(tasks.size(), 1);
    EXPECT_EQ(tasks[0], "Deliver urgent package");
}