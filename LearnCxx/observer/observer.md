
欢迎来到`zensnorlax`的博客\
本篇博客, `zen`参考了`Head First 设计模式` [^1] 中的`observer`模式

```cpp
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
```
拷贝了下参考书的设计图
<br></br>
<figure style = "text-align: center;">
  <img src="/home/qing/CodeJourney/LearnCxx/observer/observer_design.png" alt="observer 设计图">
  <br></br>
  <figcaption>observer 设计图</figcaption>
</figure>
  <br></br>

**设计图讲解**

- 定义实现`Subject`接口的`WeatherData` 定义实现`Observer` `DisplayElement`接口的`CurrentConditionsDisplay` `StatisticsDisplay` `ThirdPartyDisplay`
- 接口的作用

    - 规范行为, 你不能保证看你代码的是什么人
    - 动态绑定 减少修改, 如果不使用接口必须为每一个`observer`建立一个成员变量， 而不能使用同类型的集合
    - 低耦合， 当使用接口后， `subject`与`observer`分离， 不用考虑相互之间的实现, 也由此方便实现复用
- 具体`observer`注册具体`subject`, 当具体`subject`发生变化, 通知已注册的观察者更新数据    

**代码详解**

- 引入的snorlax_log.h 请见[C++ 简易日志系统](https://juejin.cn/post/7414424759227416614)
- 为了方便内存管理, 引入`shared_ptr`智能指针， 在这里不详细展开叙述
- 为了提高查找效率引入`unordered_set`, 平均时间复杂度为O(1), 相比使用列表效率有所提高

[^1]: [点击这里可下载`Head First 设计模式`pdf](https://pc.woozooo.com/mydisk.php)


