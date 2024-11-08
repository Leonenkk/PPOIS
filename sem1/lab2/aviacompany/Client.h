#ifndef CLIENT_H
#define CLIENT_H

#include "People.h"
#include "Order.h"

class Client : public People {
private:
    Order order;

public:
    Client(const std::string& name, int age, const Order& order);

    Order getOrder() const;
    void setOrder(const Order& order);
};

#endif // CLIENT_H
