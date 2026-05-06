#pragma once
#include "SpotLight.h"
#include "Camera.h"
#include "Observer.h"

class FlashLight : public SpotLight, public Observer
{
private:
    Camera* camera;

public:
    FlashLight(Camera* cam);
    void onNotify(ActionNotify eventType) override;
};
