#include "Client.h"

Client::Client(const std::string& name, int age, const Order& order) : People(name, age), order(order) {}

Order Client::getOrder() const {
    return order;
}

void Client::setOrder(const Order& order) {
    this->order = order;
}
