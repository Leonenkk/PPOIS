#include "gtest/gtest.h"
#include "OperatingRoom.h"
#include <iostream>

TEST(OperatingRoomTest, TestReserveAndRelease) {
    OperatingRoom room("OR101");
    EXPECT_TRUE(room.isAvailable());
    room.reserve("2024-11-15", 2);
    EXPECT_FALSE(room.isAvailable());
    room.reserve("2024-11-16", 2);
    room.release();
    EXPECT_TRUE(room.isAvailable());
}

TEST(OperatingRoomTest, TestCheckAvailability) {
    OperatingRoom room("OR102");
    EXPECT_TRUE(room.checkAvailability("2024-11-15"));
    room.reserve("2024-11-15", 2);
    EXPECT_FALSE(room.checkAvailability("2024-11-15"));
    room.release();
    EXPECT_TRUE(room.checkAvailability("2024-11-15"));
}

TEST(OperatingRoomTest, TestMultipleReservationsAndReleases) {
    OperatingRoom room("OR103");
    room.reserve("2024-11-15", 2);
    EXPECT_FALSE(room.isAvailable());
    room.release();
    EXPECT_TRUE(room.isAvailable());
    room.reserve("2024-11-16", 3);
    EXPECT_FALSE(room.isAvailable());
    room.release();
    EXPECT_TRUE(room.isAvailable());
}