// observer.hpp
#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <memory>
#include <unordered_set>

// 观察者接口
class Observer {
  public:
    virtual void update(float temperature, float humidity, float pressure) = 0;
    virtual ~Observer() = default;
};

// 显示元素接口
class DisplayElement {
  public:
    virtual void display() const = 0;
    virtual ~DisplayElement() = default;
};

// 主题接口
class Subject {
  public:
    virtual void addObserver(Observer *observer) = 0;
    virtual void removeObserver(Observer *observer) = 0;
    virtual ~Subject() = default;

  private:
    virtual void notifyObservers() = 0;
};

// 气象站类
class WeatherStation : public Subject {
  public:
    WeatherStation();
    void addObserver(Observer *observer) override;
    void removeObserver(Observer *observer) override;
    void setMeasurements(float temperature, float humidity, float pressure);

  private:
    void notifyObservers() override;
    void measurementsChanged();
    std::unordered_set<Observer *> observers_;
    float temperature_;
    float humidity_;
    float pressure_;
};

// 当前状况观察者类
class CurrentConditionsObserver : public Observer, public DisplayElement {
  public:
    explicit CurrentConditionsObserver(std::shared_ptr<Subject> subject);
    ~CurrentConditionsObserver();
    void update(float temperature, float humidity, float pressure) override;
    void display() const override;

  private:
    std::shared_ptr<Subject> subject_;
    float temperature_;
    float humidity_;
    float pressure_;
};

#endif // WEATHER_STATION_HPP
