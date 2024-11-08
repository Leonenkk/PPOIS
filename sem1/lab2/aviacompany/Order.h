#ifndef ORDER_H
#define ORDER_H

#include <string>

class Order {
private:
    int id;
    int customerId;
    int productId;
    std::string country;

public:
    Order(const std::string& country, int productId, int customerId, int id);

    int getId() const;
    void setId(int id);

    int getCustomerId() const;
    void setCustomerId(int customerId);

    int getProductId() const;
    void setProductId(int productId);

    std::string getCountry() const;
    void setCountry(const std::string& country);
};

#endif // ORDER_H
