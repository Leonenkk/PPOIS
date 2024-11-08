#include "Order.h"

Order::Order(const std::string& country, int productId, int customerId, int id)
    : country(country), productId(productId), customerId(customerId), id(id) {}

int Order::getId() const {
    return id;
}

void Order::setId(int id) {
    this->id = id;
}

int Order::getCustomerId() const {
    return customerId;
}

void Order::setCustomerId(int customerId) {
    this->customerId = customerId;
}

int Order::getProductId() const {
    return productId;
}

void Order::setProductId(int productId) {
    this->productId = productId;
}

std::string Order::getCountry() const {
    return country;
}

void Order::setCountry(const std::string& country) {
    this->country = country;
}
