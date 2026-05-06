#pragma once
#include "Subject.h"
#include "Action.h"
#include "LightType.h"
#include <glm/vec3.hpp>
#include <memory>
#include <vector>

class Light : public Subject {
protected:
    LightType type;
    glm::vec3 color;
    bool isOn = true;

public:
    Light(LightType t, const glm::vec3& c);
    virtual ~Light();

    LightType getType() const;
    glm::vec3 getColor() const;
    bool getIsOn() const { return isOn; }

    void setColor(const glm::vec3& c);
    void toggle() {
        isOn = !isOn;
        notify(ActionNotify::LightO);
    }
    void setOn(bool on) {
        isOn = on;
        notify(ActionNotify::LightO);
    }

    virtual glm::vec3 getPosition() const = 0;
    virtual glm::vec3 getDirection() const = 0;

    virtual float getConstant() const { return 1.0f; }
    virtual float getLinear() const { return 0.0f; }
    virtual float getQuadratic() const { return 0.0f; }

    virtual float getCutOff() const { return 0.0f; }
    virtual float getOuterCutOff() const { return 0.0f; }
};
