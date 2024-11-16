#include "gtest/gtest.h"
#include "Surgery.h"
#include "OperatingRoom.h"

TEST(SurgeryTest, TestScheduleSurgery) {
    OperatingRoom room("OR001");
    Surgery surgery("S001", "P001", "D001", "2024-11-20", 3, "Pending");

    EXPECT_EQ(surgery.getStatus(), "Pending");

    surgery.schedule(&room);

    EXPECT_EQ(surgery.getStatus(), "Scheduled");

    EXPECT_EQ(room.isAvailable(), false);
}

TEST(SurgeryTest, TestCancelSurgery) {
    OperatingRoom room("OR002");
    Surgery surgery("S002", "P002", "D002", "2024-11-21", 2, "Scheduled");

    surgery.schedule(&room);

    EXPECT_EQ(surgery.getStatus(), "Scheduled");

    surgery.cancel();

    EXPECT_EQ(surgery.getStatus(), "Cancelled");

    EXPECT_EQ(room.isAvailable(), true);
}

TEST(SurgeryTest, TestCompleteSurgery) {
    OperatingRoom room("OR003");
    Surgery surgery("S003", "P003", "D003", "2024-11-22", 4, "Scheduled");

    surgery.schedule(&room);

    EXPECT_EQ(surgery.getStatus(), "Scheduled");

    surgery.complete();

    EXPECT_EQ(surgery.getStatus(), "Completed");
}

TEST(SurgeryTest, TestRoomAvailability) {
    OperatingRoom room("OR004");
    Surgery surgery("S004", "P004", "D004", "2024-11-23", 5, "Pending");

    EXPECT_EQ(room.isAvailable(), true);

    surgery.schedule(&room);

    EXPECT_EQ(room.isAvailable(), false);

    surgery.cancel();

    EXPECT_EQ(room.isAvailable(), true);
}
