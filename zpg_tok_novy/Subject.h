#pragma once
#include "OpenGL_Include.h"
#include <vector>
#include "Observer.h"

class Subject {
private:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* observer);

    void removeObserver(Observer* observer);

    void notify(ActionNotify eventType);
};