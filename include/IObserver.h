#pragma once

#include <vector>
#include <algorithm>

/**
 * @brief (Observer Pattern) The Observer interface.
 * Defines the update method that Subjects will call.
 */
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update() = 0;
};

/**
 * @brief (Observer Pattern) The Subject (Observable) interface.
 * Defines methods for attaching, detaching, and notifying observers.
 */
class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void attach(IObserver* observer) = 0;
    virtual void detach(IObserver* observer) = 0;
    virtual void notify() = 0;
};

/**
 * @brief Helper implementation of ISubject.
 * Can be inherited by any class that needs to be observable.
 */
class Subject : public ISubject {
public:
    void attach(IObserver* observer) override {
        m_observers.push_back(observer);
    }

    void detach(IObserver* observer) override {
        m_observers.erase(
            std::remove(m_observers.begin(), m_observers.end(), observer),
            m_observers.end()
        );
    }

    void notify() override {
        for (IObserver* observer : m_observers) {
            observer->update();
        }
    }

private:
    std::vector<IObserver*> m_observers;
};