// fraction_test.cpp (Google Test)
#include <gtest/gtest.h>
#include "fraction.h"
TEST(FractionTest, ConstructorTest) {
    Fraction f1('+', 1, 2);
    ASSERT_EQ(f1.getNumerator(), 1);
    ASSERT_EQ(f1.getDenominator(), 2);

    Fraction f2(Sign('-'), 3, 4);
    ASSERT_EQ(f2.getNumerator(), -3);
    ASSERT_EQ(f2.getDenominator(), 4);

    Fraction f3(5);
    ASSERT_EQ(f3.getNumerator(), 5);
    ASSERT_EQ(f3.getDenominator(), 1);

    Fraction f4(Sign('-'), 6, -3);
    ASSERT_EQ(f4.getNumerator(), 2);
    ASSERT_EQ(f4.getDenominator(), 1);

    ASSERT_THROW(Fraction f5('+',1, 0), std::invalid_argument);


}

TEST(FractionTest, ArithmeticTest) {
    Fraction f1('+', 1, 2);
    Fraction f2(Sign('-'), 3, 4);
    Fraction f3(5);
    Fraction f4(2);

    Fraction sum = f1 + f2;
    ASSERT_EQ(sum.getNumerator(), -1);
    ASSERT_EQ(sum.getDenominator(), 4);

    Fraction diff = f3 - f2;
    ASSERT_EQ(diff.getNumerator(), 23);
    ASSERT_EQ(diff.getDenominator(), 4);

    Fraction prod = f1 * f2;
    ASSERT_EQ(prod.getNumerator(), -3);
    ASSERT_EQ(prod.getDenominator(), 8);

    Fraction quot = f3 / f2;
    ASSERT_EQ(quot.getNumerator(), -20);
    ASSERT_EQ(quot.getDenominator(), 3);


    Fraction sum2 = f1 + 1;
    ASSERT_EQ(sum2.getNumerator(), 3);
    ASSERT_EQ(sum2.getDenominator(), 2);

    Fraction diff2 = f3 - 1;
    ASSERT_EQ(diff2.getNumerator(), 4);
    ASSERT_EQ(diff2.getDenominator(), 1);


    Fraction prod2 = f1 * 2;
    ASSERT_EQ(prod2.getNumerator(), 1);
    ASSERT_EQ(prod2.getDenominator(), 1);

    Fraction quot2 = f3 / 1;
    ASSERT_EQ(quot2.getNumerator(), 5);
    ASSERT_EQ(quot2.getDenominator(), 1);

    Fraction f5('+',0, 5);
    ASSERT_THROW(f1 / f5, std::runtime_error);
}

TEST(FractionTest, SimplifyTest) {
    Fraction f1('-',6, 3);
    ASSERT_EQ(f1.getNumerator(), -2);
    ASSERT_EQ(f1.getDenominator(), 1);


    Fraction f2(Sign('-'), 10, -5);
    ASSERT_EQ(f2.getNumerator(), 2);
    ASSERT_EQ(f2.getDenominator(), 1);

}

TEST(FractionTest, ComparisonTest) {
    Fraction f1('+',1, 2);
    Fraction f2('-',3, 4);
    Fraction f3('+',1, 2);

    ASSERT_TRUE(f2 < f1);
    ASSERT_TRUE(f1 > f2);
    ASSERT_TRUE(f1 == f3);
    ASSERT_TRUE(f1 >= f3);
    ASSERT_TRUE(f3 <= f1);
    ASSERT_TRUE(f1 != f2);

}

TEST(FractionTest, IncrementDecrementTest) {
    Fraction f1('+', 1, 2);
    Fraction f2 = f1++;
    ASSERT_EQ(f2.getNumerator(), 1);
    ASSERT_EQ(f2.getDenominator(), 2);
    ASSERT_EQ(f1.getNumerator(), 3);
    ASSERT_EQ(f1.getDenominator(), 2);

    Fraction f3('+', 1, 2);
    Fraction f4 = ++f3;
    ASSERT_EQ(f4.getNumerator(), 3);
    ASSERT_EQ(f4.getDenominator(), 2);
    ASSERT_EQ(f3.getNumerator(), 3);
    ASSERT_EQ(f3.getDenominator(), 2);


    Fraction f5('+', 1, 2);
    Fraction f6 = f5--;
    ASSERT_EQ(f6.getNumerator(), 1);
    ASSERT_EQ(f6.getDenominator(), 2);
    ASSERT_EQ(f5.getNumerator(), -1);
    ASSERT_EQ(f5.getDenominator(), 2);

    Fraction f7('+', 1, 2);
    Fraction f8 = --f7;
    ASSERT_EQ(f8.getNumerator(), -1);
    ASSERT_EQ(f8.getDenominator(), 2);
    ASSERT_EQ(f7.getNumerator(), -1);
    ASSERT_EQ(f7.getDenominator(), 2);


}

TEST(FractionTest, OutputTest) {
    Fraction f1('+', 1, 2);
    std::stringstream ss;
    ss << f1;
    ASSERT_EQ(ss.str(), "+1/2");

    Fraction f2(Sign('-'), 3, 4);
    std::stringstream ss2;
    ss2 << f2;
    ASSERT_EQ(ss2.str(), "-3/4");
}