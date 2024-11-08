#ifndef PLANE_H
#define PLANE_H

#include <string>

class Plane {
private:
    std::string color;
    std::string model;
    std::string engine;
    int maxSpeed;
    int weight;

public:
    Plane(const std::string& color, const std::string& model, const std::string& engine, int maxSpeed, int weight);

    int getMaxSpeed() const;
    void setMaxSpeed(int maxSpeed);

    std::string getColor() const;
    void setColor(const std::string& color);

    std::string getModel() const;
    void setModel(const std::string& model);

    std::string getEngine() const;
    void setEngine(const std::string& engine);

    int getWeight() const;
    void setWeight(int weight);
};

#endif // PLANE_H
