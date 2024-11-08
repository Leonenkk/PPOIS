#include "gtest/gtest.h"
#include "Plane.h"

class PlaneTest : public ::testing::Test {
protected:
    Plane* plane;

    void SetUp() override {
        plane = new Plane("Red", "Boeing 737", "Jet", 900, 80000);
    }

    void TearDown() override {
        delete plane;
    }
};

TEST_F(PlaneTest, ConstructorAndGetters) {
    EXPECT_EQ(plane->getColor(), "Red");
    EXPECT_EQ(plane->getModel(), "Boeing 737");
    EXPECT_EQ(plane->getEngine(), "Jet");
    EXPECT_EQ(plane->getMaxSpeed(), 900);
    EXPECT_EQ(plane->getWeight(), 80000);
}

TEST_F(PlaneTest, SetAndGetColor) {
    plane->setColor("Blue");
    EXPECT_EQ(plane->getColor(), "Blue");
}

TEST_F(PlaneTest, SetAndGetModel) {
    plane->setModel("Airbus A320");
    EXPECT_EQ(plane->getModel(), "Airbus A320");
}

TEST_F(PlaneTest, SetAndGetEngine) {
    plane->setEngine("Turbofan");
    EXPECT_EQ(plane->getEngine(), "Turbofan");
}

TEST_F(PlaneTest, SetAndGetMaxSpeed) {
    plane->setMaxSpeed(950);
    EXPECT_EQ(plane->getMaxSpeed(), 950);
}

TEST_F(PlaneTest, SetAndGetWeight) {
    plane->setWeight(85000);
    EXPECT_EQ(plane->getWeight(), 85000);
}

TEST_F(PlaneTest, SetMaxSpeedNegative) {
    plane->setMaxSpeed(-100);
    EXPECT_EQ(plane->getMaxSpeed(), -100);
}
