---
theme: smartblue
---


# 欢迎来到 `zensnorlax` 的博客

本篇博客，`zen` 参考了《Head First 设计模式》[^1] 中的观察者模式。

## 类图与详解

### 程序类图

![observer 类图](/home/qing/CodeJourney/LearnCxx/observer/observer.svg)

### 类图详解

* **`Subject` 接口**: 提供添加、删除和通知观察者的方法。
* **`Observer` 接口**: 提供更新的方法，供主题调用。
* **`DisplayElement` 接口**: 提供显示的抽象方法。
* **`WeatherStation` 类**: 实现了 `Subject` 接口，维护天气数据，并通知观察者。
* **`CurrentConditionsObserver` 类**: 实现了 `Observer` 和 `DisplayElement` 接口，接收天气数据并显示当前条件。

---

## 程序代码与详解

### 程序代码

```cpp
#include "../logger/snorlax_log.h"
#include <fstream>
#include <iostream>
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

// 天气站类，实现主题接口
class WeatherStation : public Subject {
public:
    WeatherStation() : temperature_(0), humidity_(0), pressure_(0) {}

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

// 当前条件观察者类，实现观察者和显示元素接口
class CurrentConditionsObserver : public Observer, public DisplayElement {
public:
    CurrentConditionsObserver(std::shared_ptr<Subject> subject)
        : subject_(subject), temperature_(0), humidity_(0), pressure_(0) {
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

### 代码详解

* **`snorlax_log.h`**: 请见 [C++ 简易日志系统](https://juejin.cn/post/7414424759227416614)。
* **内存管理**: 引入 `shared_ptr` 智能指针。当 `observer` 订阅时，内部计数器 +1，仅当计数器为 0 时，才能回收 `subject`。这有助于在多线程使用时管理内存，减少泄漏风险。
* **效率优化**: 引入 `unordered_set` 提高查找效率，其平均时间复杂度为 $O(1 + \alpha)$，$\alpha$ 为装载因子，相比使用列表效率更高。

[^1]: [点击这里可下载《Head First 设计模式》PDF](https://wwjp.lanzouk.com/i7Sie2a6t9pc)

---
