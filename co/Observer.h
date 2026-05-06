#pragma once
#include "Action.h"

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onNotify(ActionNotify eventType) = 0;
};
