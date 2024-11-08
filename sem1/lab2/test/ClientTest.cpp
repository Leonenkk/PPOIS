#include "gtest/gtest.h"
#include "Client.h"
#include "Order.h"

TEST(ClientTest, ConstructorTest) {
    Order order("USA", 101, 1001, 1);
    Client client("John Doe", 30, order);
    EXPECT_EQ(client.getOrder().getId(), 1);
    EXPECT_EQ(client.getOrder().getCustomerId(), 1001);
    EXPECT_EQ(client.getOrder().getProductId(), 101);
    EXPECT_EQ(client.getOrder().getCountry(), "USA");
}

TEST(ClientTest, SetOrderTest) {
    Order order1("USA", 101, 1001, 1);
    Order order2("Canada", 102, 1002, 2);
    Client client("John Doe", 30, order1);
    EXPECT_EQ(client.getOrder().getId(), 1);
    client.setOrder(order2);
    EXPECT_EQ(client.getOrder().getId(), 2);
    EXPECT_EQ(client.getOrder().getCustomerId(), 1002);
    EXPECT_EQ(client.getOrder().getProductId(), 102);
    EXPECT_EQ(client.getOrder().getCountry(), "Canada");
}

TEST(ClientTest, GetOrderTest) {
    Order order("Germany", 103, 1003, 3);
    Client client("Jane Smith", 25, order);
    Order returnedOrder = client.getOrder();
    EXPECT_EQ(returnedOrder.getId(), 3);
    EXPECT_EQ(returnedOrder.getCustomerId(), 1003);
    EXPECT_EQ(returnedOrder.getProductId(), 103);
    EXPECT_EQ(returnedOrder.getCountry(), "Germany");
}