// observer.cpp
#include "observer.hpp"
#include "../logger/snorlax_log.h"
#include <iostream>

// WeatherStation 类的实现
WeatherStation::WeatherStation()
    : temperature_(0), humidity_(0), pressure_(0) {}

void WeatherStation::addObserver(Observer *observer) {
    observers_.insert(observer);
    LOG(Level::INFO, "Observer added.");
}

void WeatherStation::removeObserver(Observer *observer) {
    observers_.erase(observer);
    LOG(Level::INFO, "Observer removed.");
}

void WeatherStation::setMeasurements(float temperature, float humidity,
                                     float pressure) {
    this->temperature_ = temperature;
    this->humidity_ = humidity;
    this->pressure_ = pressure;
    LOG(Level::INFO,
        "New measurements set: Temperature = ",
        temperature,
        ", Humidity = ",
        humidity,
        ", Pressure = ",
        pressure);
    measurementsChanged();
}

void WeatherStation::notifyObservers() {
    LOG(Level::INFO, "Notifying observers...");
    for (auto observer : observers_) {
        observer->update(temperature_, humidity_, pressure_);
        LOG(Level::INFO, "Observer notified.");
    }
}

void WeatherStation::measurementsChanged() {
    notifyObservers();
    LOG(Level::INFO, "Measurements changed, observers updated.");
}

// CurrentConditionsObserver 类的实现
CurrentConditionsObserver::CurrentConditionsObserver(
    std::shared_ptr<Subject> subject)
    : subject_(std::move(subject)), temperature_(0), humidity_(0),
      pressure_(0) {
    subject_->addObserver(this);
    LOG(Level::INFO, "CurrentConditionsObserver created and registered.");
}

CurrentConditionsObserver::~CurrentConditionsObserver() {
    subject_->removeObserver(this);
    LOG(Level::INFO, "CurrentConditionsObserver destroyed and unregistered.");
}

void CurrentConditionsObserver::update(float temperature, float humidity,
                                       float pressure) {
    this->temperature_ = temperature;
    this->humidity_ = humidity;
    this->pressure_ = pressure;
    LOG(Level::INFO,
        "Observer updated with new data: Temperature = ",
        temperature,
        ", Humidity = ",
        humidity,
        ", Pressure = ",
        pressure);
    display();
}

void CurrentConditionsObserver::display() const {
    std::cout << "Current conditions: Temperature: " << temperature_
              << ", Humidity: " << humidity_ << ", Pressure: " << pressure_
              << std::endl;
    LOG(Level::INFO, "Displayed current conditions.");
}


