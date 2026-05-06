#pragma once
#include "OpenGL_Include.h"
#include "Scene.h"
#include "Camera.h"
#include "Light.h"
#include "FlashLight.h"
#include "Skybox.h"
#include "ShaderManager.h"
#include "MeteorScene.h"
#include "Rotate.h"

#include "TriangleScene.h"
#include "SpheresScene.h"
#include "ForestScene.h"
#include "SolarSystemScene.h"

#include <iostream>
#include <memory>
#include <vector>

class Application
{
private:
    static Application* instance;

    GLFWwindow* window = nullptr;
    std::vector<std::shared_ptr<Scene>> scenes;
    int currentSceneIndex = 0;

    bool rightMouseButtonPressed = false;
    double lastMouseX = 0.0, lastMouseY = 0.0;

    std::shared_ptr<Camera> camera;
    std::shared_ptr<Light> light;
    std::shared_ptr<FlashLight> flashlight;
    std::shared_ptr<Skybox> skybox;
    std::shared_ptr<DrawableObject> selectedObject;

    unsigned int nextObjectId = 1;

    bool objectMovingMode = false;
    bool isDragging = false;
    glm::vec3 dragStartPosition = glm::vec3(0.0f); // Inicializace

    void handleLeftClick(double x, double y);
    void deleteSelectedObject();
    void addTreeAtPosition(const glm::vec3& worldPos);
    void selectObject(unsigned int id);

    void startObjectMoving();
    void updateSelectedObjectPosition(const glm::vec3& worldPos);
    void testHomogeneousCoordinates();

    Application();

public:
    ~Application();

    static Application* getInstance();
    static void destroyInstance();

    bool initialization();
    void createScenes();
    void run();
    void switchScene(int sceneIndex);

    void processInput();
    void processMouseButton(int button, int action);

    static void error_callback(int error, const char* description);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void window_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY);

    std::shared_ptr<Camera> getCamera() const { return camera; }
    std::shared_ptr<Light> getLight() const { return light; }
    Scene* getCurrentScene() const { return scenes[currentSceneIndex].get(); }
    std::shared_ptr<FlashLight> getFlashlight() const { return flashlight; }
    void toggleFlashlight();
    void updateFlashlightPointer();
    void testCustomMatrix();

    unsigned int getNextObjectId() const { return nextObjectId; }
    void incrementObjectId() { nextObjectId++; }
    void setNextObjectId(unsigned int id) { nextObjectId = id; }

    bool getIsDragging() const { return isDragging; }
    bool getObjectMovingMode() const { return objectMovingMode; }

    int getCurrentSceneIndex() { return currentSceneIndex; }

    void createSkybox();
};