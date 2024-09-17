#include "../logger/snorlax_log.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <unordered_set>

class Observer {
  public:
    virtual void update(float temperature, float humidity, float pressure) = 0;
    virtual ~Observer() = default;
};

class DisplayElement {
  public:
    virtual void display() const = 0;
    virtual ~DisplayElement() = default;
};

class Subject {
  public:
    virtual void addObserver(Observer *observer) = 0;
    virtual void removeObserver(Observer *observer) = 0;
    virtual ~Subject() = default;

  private:
    virtual void notifyObservers() = 0;
};

class WeatherStation : public Subject {
  public:
    WeatherStation() {}

    void addObserver(Observer *observer) override {
        observers_.insert(observer);
        LOG(Level::INFO, "Observer added.");
    }

    void removeObserver(Observer *observer) override {
        observers_.erase(observer);
        LOG(Level::INFO, "Observer removed.");
    }

    void setMeasurements(float temperature, float humidity, float pressure) {
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

  private:
    void notifyObservers() override {
        LOG(Level::INFO, "Notifying observers...");
        for (auto observer : observers_) {
            observer->update(temperature_, humidity_, pressure_);
            LOG(Level::INFO, "Observer notified.");
        }
    }

    void measurementsChanged() {
        notifyObservers();
        LOG(Level::INFO, "Measurements changed, observers updated.");
    }

    std::unordered_set<Observer *> observers_;
    float temperature_;
    float humidity_;
    float pressure_;
};

class CurrentConditionsObserver : public Observer, public DisplayElement {
  public:
    CurrentConditionsObserver(std::shared_ptr<Subject> subject)
        : subject_(subject) {
        subject_->addObserver(this);
        LOG(Level::INFO, "CurrentConditionsObserver created and registered.");
    }

    ~CurrentConditionsObserver() {
        subject_->removeObserver(this);
        LOG(Level::INFO,
            "CurrentConditionsObserver destroyed and unregistered.");
    }

    void update(float temperature, float humidity, float pressure) override {
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

    void display() const override {
        std::cout << "Current conditions: Temperature: " << temperature_
                  << ", Humidity: " << humidity_ << ", Pressure: " << pressure_
                  << std::endl;
        LOG(Level::INFO, "Displayed current conditions.");
    }

  private:
    std::shared_ptr<Subject> subject_;
    float temperature_;
    float humidity_;
    float pressure_;
};

int main() {
    std::ofstream file("observer.txt");
    SnorlaxLog &logger = SnorlaxLog::getInstance();
    logger.setOutputStream(file);
    logger.setLevel(Level::INFO);

    auto weather_station = std::make_shared<WeatherStation>();

    CurrentConditionsObserver current_display(weather_station);

    weather_station->setMeasurements(25.0f, 65.0f, 1013.0f);
    weather_station->setMeasurements(30.0f, 70.0f, 1010.0f);

    return 0;
}
