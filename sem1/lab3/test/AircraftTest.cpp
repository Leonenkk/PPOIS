#include "gtest/gtest.h"
#include "Aircraft.h"

// Тестовый класс для Aircraft
class AircraftTest : public ::testing::Test {
protected:
    // Вспомогательные данные для тестов
    Aircraft* aircraft;

    // SetUp выполняется перед каждым тестом
    void SetUp() override {
        aircraft = new Aircraft("Red", "Boeing 737", "Jet Engine", 900, 40000, 60000, 2);
    }

    // TearDown выполняется после каждого теста
    void TearDown() override {
        delete aircraft;
    }
};

// Тест конструктора и геттеров
TEST_F(AircraftTest, ConstructorAndGetters) {
    EXPECT_EQ(aircraft->getMaxWeight(), 60000);
    EXPECT_EQ(aircraft->getNumberOfEngines(), 2);
}

// Тесты для сеттеров
TEST_F(AircraftTest, Setters) {
    aircraft->setMaxWeight(65000);
    aircraft->setNumberOfEngines(4);

    EXPECT_EQ(aircraft->getMaxWeight(), 65000);
    EXPECT_EQ(aircraft->getNumberOfEngines(), 4);
}

// Тесты для маршрута
TEST_F(AircraftTest, RouteManagement) {
    // Проверка пустого маршрута
    EXPECT_TRUE(aircraft->getRoute().empty());

    // Добавление одного города в маршрут
    aircraft->addCityToRoute("New York");
    std::list<std::string> route = aircraft->getRoute();
    EXPECT_EQ(route.size(), 1);
    EXPECT_EQ(route.front(), "New York");

    // Добавление второго города
    aircraft->addCityToRoute("London");
    route = aircraft->getRoute();
    EXPECT_EQ(route.size(), 2);
    EXPECT_EQ(route.back(), "London");
}

// Тесты для setRoute и addCityToRoute
TEST_F(AircraftTest, SetRoute) {
    std::list<std::string> newRoute = {"Paris", "Berlin", "Tokyo"};
    aircraft->setRoute(newRoute);

    std::list<std::string> route = aircraft->getRoute();
    EXPECT_EQ(route.size(), 3);
    EXPECT_EQ(route.front(), "Paris");
    EXPECT_EQ(route.back(), "Tokyo");
}

// Тест на корректность маршрута
TEST_F(AircraftTest, AddCityToRoute) {
    aircraft->addCityToRoute("Los Angeles");
    aircraft->addCityToRoute("Sydney");

    std::list<std::string> route = aircraft->getRoute();
    EXPECT_EQ(route.size(), 2);
    EXPECT_EQ(route.front(), "Los Angeles");
    EXPECT_EQ(route.back(), "Sydney");
}
