#include "RaceTrackScene.h"
#include "ShaderManager.h"
#include "Translate.h"
#include "Scale.h"
#include "Rotate.h"
#include "Material.h"
#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include <iostream>
#include <cmath>

RaceTrackScene::RaceTrackScene(std::shared_ptr<Camera> cam)
    : Scene(cam)
{
}

void RaceTrackScene::init()
{
    auto& lights = getLights();
    lights.clear();

    lights.push_back(std::make_shared<AmbientLight>(glm::vec3(0.2f, 0.2f, 0.2f)));
    lights.push_back(std::make_shared<DirectionalLight>(
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(0.8f, 0.8f, 0.8f)
    ));
    lights.push_back(std::make_shared<PointLight>(
        glm::vec3(0.0f, 10.0f, 0.0f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        1.0f, 0.09f, 0.032f
    ));

    createRaceTrack();

    auto formulaModel = ModelLoader::load("formula1.obj");
    if (!formulaModel){
        formulaModel = ModelLoader::load("sphere.obj");
    }

    auto phongShader = ShaderManager::getShader("phong");

    auto carMaterial = std::make_shared<Material>(
        glm::vec3(0.1f, 0.1f, 0.15f),
        glm::vec3(0.3f, 0.3f, 0.8f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        256.0f                             
    );

    formulaCar = std::make_shared<DrawableObject>(
        formulaModel, phongShader, carMaterial
    );

    carSplineMovement = std::make_shared<BezierSplineMovement>(
        trackPoints, 0.3f, true, true
    );

    auto carTransform = std::make_shared<CompositeTransform>();
    carTransform->addTransform(carSplineMovement);
    carTransform->addTransform(std::make_shared<Scale>(glm::vec3(0.1f)));
    carTransform->addTransform(std::make_shared<Rotate>(glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

    formulaCar->getTransformations()->addTransform(carTransform);
    formulaCar->setId(getNextObjectId());
    addObject(formulaCar);

	auto groundModel = ModelLoader::load("teren.obj");
    auto grassTexture = std::make_shared<Texture>("assets/grass.png");

    auto groundMaterial = std::make_shared<Material>(
        glm::vec3(0.02f, 0.05f, 0.02f),
        glm::vec3(0.1f, 0.3f, 0.1f),
        glm::vec3(0.02f, 0.02f, 0.02f),
        8.0f
	);

    auto ground = std::make_shared<DrawableObject>(
        groundModel,phongShader, groundMaterial, grassTexture
    );

    ground->getTransformations()->addTransform(std::make_shared<Translate>(glm::vec3(0.0f, -1.8f, 0.0f)));
    ground->getTransformations()->addTransform(std::make_shared<Scale>(glm::vec3(1.0f, 1.0f, 1.0f)));

    addObject(ground);

    std::cout << "Race Track Scene init!" << std::endl;
}

void RaceTrackScene::createRaceTrack()
{
    trackPoints.clear();

    trackPoints.push_back(glm::vec3(0.0f, 0.0f, 10.0f));
    trackPoints.push_back(glm::vec3(8.0f, 0.0f, 12.0f));
    trackPoints.push_back(glm::vec3(12.0f, 0.0f, 8.0f));
    trackPoints.push_back(glm::vec3(10.0f, 0.0f, 0.0f));

    trackPoints.push_back(glm::vec3(8.0f, 0.0f, -2.0f));
    trackPoints.push_back(glm::vec3(0.0f, 0.0f, -4.0f));
    trackPoints.push_back(glm::vec3(-8.0f, 0.0f, -2.0f));
    trackPoints.push_back(glm::vec3(-10.0f, 0.0f, 0.0f));

    trackPoints.push_back(glm::vec3(-12.0f, 0.0f, 8.0f));
    trackPoints.push_back(glm::vec3(-8.0f, 0.0f, 12.0f));
}



void RaceTrackScene::update()
{

}

void RaceTrackScene::draw()
{
    Scene::draw();
}

void RaceTrackScene::addTrackPoint(const glm::vec3& point)
{
    trackPoints.push_back(point);

    if (trackPoints.size() >= 4 && carSplineMovement) {
        carSplineMovement->clearControlPoints();
        for (const auto& p : trackPoints) {
            carSplineMovement->addControlPoint(p);
        }
    }
}

void RaceTrackScene::startCarMovement()
{
    if (trackPoints.size() >= 4) {
        carSplineMovement = std::make_shared<BezierSplineMovement>(
            trackPoints, 0.3f, true, true
        );

        auto carTransform = std::make_shared<CompositeTransform>();
        carTransform->addTransform(carSplineMovement);
        carTransform->addTransform(std::make_shared<Scale>(glm::vec3(0.1f)));
        carTransform->addTransform(std::make_shared<Rotate>(glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

        formulaCar->getTransformations() = carTransform;

        std::cout << "Car move!" << std::endl;
    }
}