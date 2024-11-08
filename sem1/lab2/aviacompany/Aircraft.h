#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "Plane.h"
#include <string>
#include <list>

class Aircraft : public Plane {
private:
    int maxWeight;
    int numberOfEngines;
    std::list<std::string> route;

public:
    Aircraft(const std::string& color, const std::string& model, const std::string& engine, int maxSpeed, int weight,
             int maxWeight, int numberOfEngines);

    int getMaxWeight() const;
    void setMaxWeight(int maxWeight);

    int getNumberOfEngines() const;
    void setNumberOfEngines(int numberOfEngines);

    std::list<std::string> getRoute() const;
    void setRoute(const std::list<std::string>& route);

    void addCityToRoute(const std::string& city);
};

#endif // AIRCRAFT_H
