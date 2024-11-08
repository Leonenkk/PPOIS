#include "Plane.h"

Plane::Plane(const std::string& color, const std::string& model, const std::string& engine, int maxSpeed, int weight)
    : color(color), model(model), engine(engine), maxSpeed(maxSpeed), weight(weight) {}

int Plane::getMaxSpeed() const {
    return maxSpeed;
}

void Plane::setMaxSpeed(int maxSpeed) {
    this->maxSpeed = maxSpeed;
}

std::string Plane::getColor() const {
    return color;
}

void Plane::setColor(const std::string& color) {
    this->color = color;
}

std::string Plane::getModel() const {
    return model;
}

void Plane::setModel(const std::string& model) {
    this->model = model;
}

std::string Plane::getEngine() const {
    return engine;
}

void Plane::setEngine(const std::string& engine) {
    this->engine = engine;
}

int Plane::getWeight() const {
    return weight;
}

void Plane::setWeight(int weight) {
    this->weight = weight;
}
