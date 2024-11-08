#include "gtest/gtest.h"
#include "People.h"

class PeopleTest : public ::testing::Test {
protected:
    People* person;

    void SetUp() override {
        person = new People("John Doe", 30);
    }

    void TearDown() override {
        delete person;
    }
};

TEST_F(PeopleTest, ConstructorAndGetters) {
    EXPECT_EQ(person->getName(), "John Doe");
    EXPECT_EQ(person->getAge(), 30);
}

TEST_F(PeopleTest, SetName) {
    person->setName("Jane Smith");
    EXPECT_EQ(person->getName(), "Jane Smith");
}

TEST_F(PeopleTest, SetAge) {
    person->setAge(35);
    EXPECT_EQ(person->getAge(), 35);
}

TEST_F(PeopleTest, SetAgeNegative) {
    person->setAge(-5);
    EXPECT_EQ(person->getAge(), -5);
}
