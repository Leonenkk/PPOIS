#include "gtest/gtest.h"
#include "Order.h"

class OrderTest : public ::testing::Test {
protected:
    Order* order;

    void SetUp() override {
        order = new Order("USA", 101, 202, 1);
    }

    void TearDown() override {
        delete order;
    }
};

TEST_F(OrderTest, ConstructorAndGetters) {
    EXPECT_EQ(order->getId(), 1);
    EXPECT_EQ(order->getCustomerId(), 202);
    EXPECT_EQ(order->getProductId(), 101);
    EXPECT_EQ(order->getCountry(), "USA");
}

TEST_F(OrderTest, SetId) {
    order->setId(5);
    EXPECT_EQ(order->getId(), 5);
}

TEST_F(OrderTest, SetCustomerId) {
    order->setCustomerId(999);
    EXPECT_EQ(order->getCustomerId(), 999);
}

TEST_F(OrderTest, SetProductId) {
    order->setProductId(777);
    EXPECT_EQ(order->getProductId(), 777);
}

TEST_F(OrderTest, SetCountry) {
    order->setCountry("Germany");
    EXPECT_EQ(order->getCountry(), "Germany");
}
