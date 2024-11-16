#include <gtest/gtest.h>
#include "Person.h"

class PersonTest : public ::testing::Test {
protected:
    Person person{"John", "Doe", 30, "Male", "123 Main St", "555-1234"};
};

TEST_F(PersonTest, GetFullName) {
    EXPECT_EQ(person.getFullName(), "John Doe");
}

TEST_F(PersonTest, GetContactInfo) {
    EXPECT_EQ(person.getContactInfo(), "Address: 123 Main St, Phone: 555-1234");
}

TEST_F(PersonTest, SetAddress) {
    person.setAddress("456 Elm St");
    EXPECT_EQ(person.getContactInfo(), "Address: 456 Elm St, Phone: 555-1234");
}

TEST_F(PersonTest, SetPhone) {
    person.setPhone("555-5678");
    EXPECT_EQ(person.getContactInfo(), "Address: 123 Main St, Phone: 555-5678");
}