#include "SolarSystemScene.h"
#include "ShaderManager.h"
#include "ModelLoader.h"
#include "Translate.h"
#include "Scale.h"
#include "Rotate.h"
#include "DynamicRotation.h"
#include "CompositeTransform.h"
#include "AmbientLight.h"
#include "Material.h"
#include <iostream>

SolarSystemScene::SolarSystemScene(std::shared_ptr<Camera> cam)
    : Scene(cam), timeScale(1.0f), orbitSpeedMultiplier(1.0f), rotationSpeedMultiplier(1.0f)
{
}

void SolarSystemScene::init() {
    planetModel = ModelLoader::load("planet.obj");
	textModel = ModelLoader::load("text_tok0030.obj");

    sunTexture = std::make_shared<Texture>("assets/textures/8k_sun.jpg");
    mercuryTexture = std::make_shared<Texture>("assets/textures/8k_mercury.jpg");
    venusTexture = std::make_shared<Texture>("assets/textures/8k_venus.jpg");
    earthTexture = std::make_shared<Texture>("assets/textures/8k_earth.jpg");
    moonTexture = std::make_shared<Texture>("assets/textures/8k_moon.jpg");
    marsTexture = std::make_shared<Texture>("assets/textures/8k_mars.jpg");
    jupiterTexture = std::make_shared<Texture>("assets/textures/8k_jupiter.jpg");
    saturnTexture = std::make_shared<Texture>("assets/textures/8k_saturn.jpg");
    uranusTexture = std::make_shared<Texture>("assets/textures/2k_uranus.jpg");
    neptuneTexture = std::make_shared<Texture>("assets/textures/2k_neptune.jpg");

    auto& lights = getLights();
    lights.clear();
    sunLight = std::make_shared<PointLight>(glm::vec3(0.0f), glm::vec3(1.2f, 1.0f, 0.8f), 1.0f, 0.001f, 0.0002f);
    lights.push_back(sunLight);
    lights.push_back(std::make_shared<AmbientLight>(glm::vec3(0.15f)));

    auto shader = ShaderManager::getShader("phong");

    // Oběh kolem Slunce
    const float mercuryOrbitSpeed = 0.04f;   // 88 dní
    const float venusOrbitSpeed = 0.016f;    // 225 dní  
    const float earthOrbitSpeed = 0.01f;     // 365 dní
    const float marsOrbitSpeed = 0.0053f;    // 687 dní
    const float jupiterOrbitSpeed = 0.00084f; // 12 let
    const float saturnOrbitSpeed = 0.00034f;  // 29 let
    const float uranusOrbitSpeed = 0.000119f; // 84 let
    const float neptuneOrbitSpeed = 0.000061f; // 165 let

    // Rotace kolem osy
    const float sunRotationSpeed = 0.002f;    // 27 dní
    const float mercuryRotationSpeed = 0.006f; // 59 dní
    const float venusRotationSpeed = 0.0016f; // 243 dní (retrográdní)
    const float earthRotationSpeed = 0.5f;    // 1 den
    const float marsRotationSpeed = 0.49f;    // 1.03 dne
    const float jupiterRotationSpeed = 1.2f;  // 0.41 dne (9.9 hodin)
    const float saturnRotationSpeed = 1.1f;   // 0.44 dne (10.7 hodin)
    const float uranusRotationSpeed = 0.7f;   // 0.72 dne (17.2 hodin)
    const float neptuneRotationSpeed = 0.75f; // 0.67 dne (16.1 hodin)
    const float moonOrbitSpeed = 0.13f;       // 27.3 dní (kolem Země)
    const float moonRotationSpeed = 0.13f;    // 27.3 dní (vázaná rotace)

    auto getOrbitSpeed = [&](float baseSpeed) { return baseSpeed * orbitSpeedMultiplier * timeScale; };
    auto getRotationSpeed = [&](float baseSpeed) { return baseSpeed * rotationSpeedMultiplier * timeScale; };



   
    auto sunMaterial = std::make_shared<Material>(
    glm::vec3(1.0f, 0.6f, 0.2f),
    glm::vec3(1.0f, 0.8f, 0.3f),
    glm::vec3(0.3f, 0.2f, 0.1f),
    32.0f
    );


    auto sun = std::make_shared<DrawableObject>(planetModel, shader, sunMaterial, sunTexture);
    auto sunTrans = std::make_shared<CompositeTransform>();
    sunTrans->addTransform(std::make_shared<Scale>(glm::vec3(5.0f)));
    sunTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, 1, 0.1f), getRotationSpeed(sunRotationSpeed)));
    sun->getTransformations()->addTransform(sunTrans);
    sun->setId(getNextObjectId());
    addObject(sun);

    auto mercuryMaterial = std::make_shared<Material>(
        glm::vec3(0.2f), 
        glm::vec3(0.9f),
        glm::vec3(0.4f), 
        128.0f
    );

    auto mercury = std::make_shared<DrawableObject>(planetModel, shader, mercuryMaterial, mercuryTexture);
    auto mercuryTrans = std::make_shared<CompositeTransform>();
    mercuryTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, 1, 0), getOrbitSpeed(mercuryOrbitSpeed)));
    mercuryTrans->addTransform(std::make_shared<Translate>(glm::vec3(15.0f, 0, 0)));
    mercuryTrans->addTransform(std::make_shared<Scale>(glm::vec3(0.4f)));
    mercuryTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, 1, 0), getRotationSpeed(mercuryRotationSpeed)));
    mercury->getTransformations()->addTransform(mercuryTrans);
    mercury->setId(getNextObjectId());
    addObject(mercury);

    auto venusMaterial = std::make_shared<Material>(
        glm::vec3(0.2f), 
        glm::vec3(0.9f), 
        glm::vec3(0.4f), 
        128.0f
    );

    auto venus = std::make_shared<DrawableObject>(planetModel, shader, venusMaterial, venusTexture);
    auto venusTrans = std::make_shared<CompositeTransform>();
    venusTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, 1, 0), getOrbitSpeed(venusOrbitSpeed)));
    venusTrans->addTransform(std::make_shared<Translate>(glm::vec3(21.0f, 0, 0)));
    venusTrans->addTransform(std::make_shared<Rotate>(glm::radians(177.4f), glm::vec3(0, 0, 1)));
    venusTrans->addTransform(std::make_shared<Scale>(glm::vec3(0.9f)));
    venusTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, -1, 0), getRotationSpeed(venusRotationSpeed)));
    venus->getTransformations()->addTransform(venusTrans);
    venus->setId(getNextObjectId());
    addObject(venus);

    auto earthMaterial = std::make_shared<Material>(
        glm::vec3(0.2f, 0.25f, 0.3f),
        glm::vec3(0.4f, 0.6f, 0.8f),
        glm::vec3(0.5f),
        64.0f
    );

    auto earth = std::make_shared<DrawableObject>(planetModel, shader, earthMaterial, earthTexture);
    auto earthTrans = std::make_shared<CompositeTransform>();
    earthTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, 1, 0), getOrbitSpeed(earthOrbitSpeed)));
    earthTrans->addTransform(std::make_shared<Translate>(glm::vec3(30.0f, 0, 0)));
    earthTrans->addTransform(std::make_shared<Rotate>(glm::radians(23.5f), glm::vec3(0, 0, 1)));
    earthTrans->addTransform(std::make_shared<Scale>(glm::vec3(1.0f)));
    earthTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, 1, 0), getRotationSpeed(earthRotationSpeed)));
    earth->getTransformations()->addTransform(earthTrans);
    earth->setId(getNextObjectId());
    addObject(earth);

    auto moonMaterial = std::make_shared<Material>(
        glm::vec3(0.2f), 
        glm::vec3(0.8f), 
        glm::vec3(0.5f), 
        64.0f
    );

    auto moon = std::make_shared<DrawableObject>(planetModel, shader, moonMaterial, moonTexture);
    auto moonTrans = std::make_shared<CompositeTransform>();
    moonTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, 1, 0), getOrbitSpeed(earthOrbitSpeed)));
    moonTrans->addTransform(std::make_shared<Translate>(glm::vec3(30.0f, 0, 0)));
    moonTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, 1, 0), getOrbitSpeed(moonOrbitSpeed)));
    moonTrans->addTransform(std::make_shared<Translate>(glm::vec3(4.0f, 0, 0)));
    moonTrans->addTransform(std::make_shared<Scale>(glm::vec3(0.27f)));
    moonTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, 1, 0), getRotationSpeed(moonRotationSpeed)));
    moon->getTransformations()->addTransform(moonTrans);
    moon->setId(getNextObjectId());
    addObject(moon);

    auto marsMaterial = std::make_shared<Material>(
        glm::vec3(0.2f), 
        glm::vec3(0.9f), 
        glm::vec3(0.4f), 
        128.0f
    );

    auto mars = std::make_shared<DrawableObject>(planetModel, shader, marsMaterial, marsTexture);
    auto marsTrans = std::make_shared<CompositeTransform>();
    marsTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, 1, 0), getOrbitSpeed(marsOrbitSpeed)));
    marsTrans->addTransform(std::make_shared<Translate>(glm::vec3(45.0f, 0, 0)));
    marsTrans->addTransform(std::make_shared<Rotate>(glm::radians(25.2f), glm::vec3(0, 0, 1)));
    marsTrans->addTransform(std::make_shared<Scale>(glm::vec3(0.53f)));
    marsTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, 1, 0), getRotationSpeed(marsRotationSpeed)));
    mars->getTransformations()->addTransform(marsTrans);
    mars->setId(getNextObjectId());
    addObject(mars);

    auto textMaterial = std::make_shared<Material>(
        glm::vec3(0.3f, 0.3f, 0.3f),
        glm::vec3(0.7f, 0.7f, 0.7f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        32.0f
    );

    auto textObj = std::make_shared<DrawableObject>(textModel, shader, textMaterial, earthTexture);
    auto textTrans = std::make_shared<CompositeTransform>();
    textTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, -1, 0), getOrbitSpeed(venusOrbitSpeed) * 2));
    textTrans->addTransform(std::make_shared<Translate>(glm::vec3(55.0f, 0, 0)));
    textTrans->addTransform(std::make_shared<Rotate>(glm::radians(4.5f), glm::vec3(0, 0, 1)));
    textTrans->addTransform(std::make_shared<Scale>(glm::vec3(1.f)));
    textTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, -1, 0), getRotationSpeed(earthRotationSpeed)));
    textObj->getTransformations()->addTransform(textTrans);
    textObj->setId(getNextObjectId());
    addObject(textObj);

    auto jupiterMaterial = std::make_shared<Material>(
        glm::vec3(0.2f), 
        glm::vec3(0.9f), 
        glm::vec3(0.4f), 
        128.0f
    );

    auto jupiter = std::make_shared<DrawableObject>(planetModel, shader, jupiterMaterial, jupiterTexture);
    auto jupiterTrans = std::make_shared<CompositeTransform>();
    jupiterTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, 1, 0), getOrbitSpeed(jupiterOrbitSpeed)));
    jupiterTrans->addTransform(std::make_shared<Translate>(glm::vec3(77.0f, 0, 0)));
    jupiterTrans->addTransform(std::make_shared<Rotate>(glm::radians(3.1f), glm::vec3(0, 0, 1)));
    jupiterTrans->addTransform(std::make_shared<Scale>(glm::vec3(2.5f)));
    jupiterTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, 1, 0), getRotationSpeed(jupiterRotationSpeed)));
    jupiter->getTransformations()->addTransform(jupiterTrans);
    jupiter->setId(getNextObjectId());
    addObject(jupiter);

    auto saturnMaterial = std::make_shared<Material>(
        glm::vec3(0.2f), 
        glm::vec3(0.9f), 
        glm::vec3(0.4f), 
        128.0f
    );

    auto saturn = std::make_shared<DrawableObject>(planetModel, shader, saturnMaterial, saturnTexture);
    auto saturnTrans = std::make_shared<CompositeTransform>();
    saturnTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, 1, 0), getOrbitSpeed(saturnOrbitSpeed)));
    saturnTrans->addTransform(std::make_shared<Translate>(glm::vec3(95.0f, 0, 0)));
    saturnTrans->addTransform(std::make_shared<Rotate>(glm::radians(26.7f), glm::vec3(0, 0, 1)));
    saturnTrans->addTransform(std::make_shared<Scale>(glm::vec3(2.0f)));
    saturnTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, 1, 0), getRotationSpeed(saturnRotationSpeed)));
    saturn->getTransformations()->addTransform(saturnTrans);
    saturn->setId(getNextObjectId());
    addObject(saturn);

    auto uranusMaterial = std::make_shared<Material>(
        glm::vec3(0.2f), 
        glm::vec3(0.9f), 
        glm::vec3(0.4f), 
        128.0f
    );

    auto uranus = std::make_shared<DrawableObject>(planetModel, shader, uranusMaterial, uranusTexture);
    auto uranusTrans = std::make_shared<CompositeTransform>();
    uranusTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, 1, 0), getOrbitSpeed(uranusOrbitSpeed)));
    uranusTrans->addTransform(std::make_shared<Translate>(glm::vec3(120.0f, 0, 0)));
    uranusTrans->addTransform(std::make_shared<Rotate>(glm::radians(97.8f), glm::vec3(0, 0, 1)));
    uranusTrans->addTransform(std::make_shared<Scale>(glm::vec3(1.5f)));
    uranusTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, 1, 0), getRotationSpeed(uranusRotationSpeed)));
    uranus->getTransformations()->addTransform(uranusTrans);
    uranus->setId(getNextObjectId());
    addObject(uranus);

    auto neptuneMaterial = std::make_shared<Material>(
        glm::vec3(0.2f), 
        glm::vec3(0.9f), 
        glm::vec3(0.4f), 
        128.0f
    );

    auto neptune = std::make_shared<DrawableObject>(planetModel, shader, neptuneMaterial, neptuneTexture);
    auto neptuneTrans = std::make_shared<CompositeTransform>();
    neptuneTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, 1, 0), getOrbitSpeed(neptuneOrbitSpeed)));
    neptuneTrans->addTransform(std::make_shared<Translate>(glm::vec3(150.0f, 0, 0)));
    neptuneTrans->addTransform(std::make_shared<Rotate>(glm::radians(28.3f), glm::vec3(0, 0, 1)));
    neptuneTrans->addTransform(std::make_shared<Scale>(glm::vec3(1.5f)));
    neptuneTrans->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, 1, 0), getRotationSpeed(neptuneRotationSpeed)));
    neptune->getTransformations()->addTransform(neptuneTrans);
    neptune->setId(getNextObjectId());
    addObject(neptune);

    if (camera) {
        camera->setPosition(glm::vec3(0.0f, 30.0f, 80.0f));
    }

    std::cout << "Solar System init" << std::endl;
}