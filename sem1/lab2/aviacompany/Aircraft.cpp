#include "Aircraft.h"

Aircraft::Aircraft(const std::string& color, const std::string& model, const std::string& engine, int maxSpeed, int weight,
                   int maxWeight, int numberOfEngines)
    : Plane(color, model, engine, maxSpeed, weight), maxWeight(maxWeight), numberOfEngines(numberOfEngines) {}

int Aircraft::getMaxWeight() const { return maxWeight; }
void Aircraft::setMaxWeight(int maxWeight) { this->maxWeight = maxWeight; }

int Aircraft::getNumberOfEngines() const { return numberOfEngines; }
void Aircraft::setNumberOfEngines(int numberOfEngines) { this->numberOfEngines = numberOfEngines; }

std::list<std::string> Aircraft::getRoute() const { return route; }
void Aircraft::setRoute(const std::list<std::string>& route) { this->route = route; }

void Aircraft::addCityToRoute(const std::string& city) { route.push_back(city); }
