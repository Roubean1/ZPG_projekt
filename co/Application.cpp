#include "Application.h"
#include <iostream>

Application* Application::instance = nullptr;

Application::Application() : window(nullptr) {}

Application::~Application() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

Application* Application::getInstance() {
    if (!instance) {
        instance = new Application();
    }
    return instance;
}

void Application::destroyInstance() {
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

void Application::error_callback(int error, const char* description) {
    fputs(description, stderr);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Application* app = Application::getInstance(); // Získáme instanci

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        if (app->getIsDragging()) {
            app->isDragging = false;
            app->objectMovingMode = false;
            std::cout << "Object moving cancelled" << std::endl;
        }
        else {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }
    else if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9 && action == GLFW_PRESS) {
        int sceneIndex = key - GLFW_KEY_1;
        app->switchScene(sceneIndex);
    }
    else if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        auto currentScene = app->getCurrentScene();
        if (currentScene) {
            auto& lights = currentScene->getLights();
            for (auto& light : lights) {
                if (light && light->getType() == LightType::SPOT) {
                    light->toggle();
                    std::cout << "Flashlight " << (light->getIsOn() ? "ON" : "OFF") << std::endl;
                }
            }
        }
    }
    else if (key == GLFW_KEY_DELETE && action == GLFW_PRESS) {
        app->deleteSelectedObject();
    }
    else if (key == GLFW_KEY_M && action == GLFW_PRESS) {
        app->startObjectMoving();
    }


    if (key == GLFW_KEY_T && action == GLFW_PRESS) {
        app->testHomogeneousCoordinates();
    }
    if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
        app->testCustomMatrix();
    }
}

void Application::deleteSelectedObject() {
    if (selectedObject) {
        auto& objects = scenes[currentSceneIndex]->getObjects();
        objects.erase(
            std::remove(objects.begin(), objects.end(), selectedObject),objects.end()
        );
        std::cout << "Deleted object with ID: " << selectedObject->getId() << std::endl;
        selectedObject.reset();
    }
}

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
    printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);

    Application* app = Application::getInstance();
    if (app->camera) {
        app->camera->updateScreenSize(width, height);
    }
}

void Application::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    Application* app = Application::getInstance();

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        app->handleLeftClick(x, y);
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        app->processMouseButton(button, action);
    }
}

void Application::cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY) {
    Application* app = Application::getInstance();
    if (!app->rightMouseButtonPressed || !app->camera) return;

    float xOffset = static_cast<float>(mouseX - app->lastMouseX);
    float yOffset = static_cast<float>(app->lastMouseY - mouseY);

    app->lastMouseX = mouseX;
    app->lastMouseY = mouseY;

    app->camera->updateOrientation(xOffset, yOffset);
}

void Application::processMouseButton(int button, int action) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            rightMouseButtonPressed = true;
            glfwGetCursorPos(window, &lastMouseX, &lastMouseY);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else if (action == GLFW_RELEASE) {
            rightMouseButtonPressed = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}

bool Application::initialization() {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return false;
    }

    window = glfwCreateWindow(800, 600, "ZPG - TOK0030 OpenGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetFramebufferSizeCallback(window, window_size_callback);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "ERROR: %s\n", glewGetErrorString(err));
        return false;
    }

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glEnable(GL_STENCIL_TEST);

    camera = std::make_shared<Camera>(glm::vec3(0.0f, 10.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    camera->updateScreenSize(width, height);

	ShaderManager::initialize(); 

    createScenes();

    createSkybox();

    return true;
}

void Application::updateFlashlightPointer() {
    flashlight.reset();

    auto currentScene = scenes[currentSceneIndex];
    auto& lights = currentScene->getLights();

    for (auto& light : lights) {
        if (light && light->getType() == LightType::SPOT) {
            auto fl = std::dynamic_pointer_cast<FlashLight>(light);
            if (fl) {
                flashlight = fl;
                break;
            }
        }
    }
}

void Application::handleLeftClick(double x, double y) {
    int windowX = static_cast<int>(x);
    int windowY = static_cast<int>(y);

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    windowY = height - windowY;

    GLbyte color[4];
    GLfloat depth;
    GLuint stencilIndex;

    glReadPixels(windowX, windowY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    glReadPixels(windowX, windowY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(windowX, windowY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &stencilIndex);

    printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n", windowX, windowY, color[0], color[1], color[2], color[3], depth, stencilIndex);

    glm::vec3 screenPos = glm::vec3(x, height - y, depth);
    glm::vec4 viewport = glm::vec4(0, 0, width, height);
    glm::vec3 worldPos = glm::unProject(screenPos, camera->getViewMatrix(), camera->getProjectionMatrix(), viewport);

    printf("unProject [%f, %f, %f]\n", worldPos.x, worldPos.y, worldPos.z);


    if (auto meteorScene = std::dynamic_pointer_cast<MeteorScene>(scenes[currentSceneIndex])) {
        if (stencilIndex != 0) {
            selectObject(stencilIndex);

            if (selectedObject) {
                for (auto& meteor : meteorScene->getActiveMeteors()) {
                    if (meteor->getId() == selectedObject->getId()) {
                        meteorScene->onMeteorHit(meteor);
                        selectedObject.reset();
                        return;
                    }
                }
            }
        }
        return;
    }

    if (isDragging && selectedObject) {
        updateSelectedObjectPosition(worldPos);
        isDragging = false;
        objectMovingMode = false;
        std::cout << "Object placed at new position" << std::endl;
        return;
    }
    else if (stencilIndex == 0) {
        addTreeAtPosition(worldPos);
    }
    else {
        selectObject(stencilIndex);

        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
            startObjectMoving();
            isDragging = true;
        }
    }

    
}

void Application::selectObject(unsigned int id) {
    selectedObject.reset();
    auto& objects = scenes[currentSceneIndex]->getObjects();

    std::cout << "Object with ID : " << id << std::endl;
    std::cout << "Total objects in scene: " << objects.size() << std::endl;

    for (auto& obj : objects) {
        if (obj->getId() == id) {
            selectedObject = obj;
            std::cout << "Selected object with ID : " << id << std::endl;
            break;
        }
    }
}

void Application::addTreeAtPosition(const glm::vec3& worldPos) {
    auto currentScene = scenes[currentSceneIndex];

    auto phongShader = ShaderManager::getShader("phong");

    auto barkMaterial = std::make_shared<Material>(
        glm::vec3(0.02f, 0.02f, 0.015f),
        glm::vec3(0.10f, 0.07f, 0.05f),
        glm::vec3(0.02f, 0.02f, 0.015f),
        8.0f
    );

    auto treeObj = std::make_shared<DrawableObject>(
        tree, sizeof(tree) / (6 * sizeof(float)), 6,
        phongShader, barkMaterial
    );

    treeObj->setId(currentScene->getNextObjectId());
    treeObj->getTransformations()->addTransform(std::make_shared<Translate>(worldPos));
    treeObj->getTransformations()->addTransform(std::make_shared<Rotate>(glm::radians(static_cast<float>(rand() % 360)), glm::vec3(0, 1, 0)));
    treeObj->getTransformations()->addTransform(std::make_shared<Scale>(glm::vec3(0.7f + (rand() % 30) / 100.0f)));

    currentScene->addObject(treeObj);
    std::cout << "Added tree at position: " << worldPos.x << ", " << worldPos.y << ", " << worldPos.z << " with ID: " << treeObj->getId() << std::endl;
}

void Application::toggleFlashlight() {
    if (flashlight) {
        flashlight->toggle();
        std::cout << "Flashlight " << (flashlight->getIsOn() ? "ON" : "OFF") << std::endl;
    }
}

void Application::createScenes() {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    camera->updateScreenSize(width, height);

    scenes.push_back(std::make_shared<TriangleScene>(camera));
    scenes.push_back(std::make_shared<SpheresScene>(camera));
    scenes.push_back(std::make_shared<ForestScene>(camera));
    scenes.push_back(std::make_shared<SolarSystemScene>(camera));
    scenes.push_back(std::make_shared<MeteorScene>(camera));

    for (auto& scene : scenes)
        scene->init();

    updateFlashlightPointer();
}

void Application::run() {
    if (scenes.empty()) {
        std::cerr << "No scenes!" << std::endl;
        return;
    }

    while (!glfwWindowShouldClose(window)) {
        processInput();

        if (auto meteorScene = std::dynamic_pointer_cast<MeteorScene>(scenes[currentSceneIndex])) {
            meteorScene->update();
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        if (skybox) {
            skybox->draw();
        }
        
        glClear(GL_DEPTH_BUFFER_BIT);
        
        scenes[currentSceneIndex]->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }    
}

void Application::processInput() {
    if (!camera) return;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera->forward();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera->backward();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera->left();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera->right();
}

void Application::switchScene(int sceneIndex) {
    if (sceneIndex >= 0 && sceneIndex < scenes.size()) {
        currentSceneIndex = sceneIndex;
        updateFlashlightPointer();
    }
}

void Application::createSkybox() {
    std::vector<std::string> skyboxTextures = {
        "cubemap/posx.jpg",
        "cubemap/negx.jpg",
        "cubemap/posy.jpg",
        "cubemap/negy.jpg",
        "cubemap/posz.jpg",
        "cubemap/negz.jpg"
    };
    skybox = std::make_shared<Skybox>(camera, skyboxTextures);
}

void Application::startObjectMoving() {
    if (selectedObject) {
        objectMovingMode = true;
        isDragging = true;
        std::cout << "Object moving for ID: " << selectedObject->getId() << std::endl;
    }
}

void Application::updateSelectedObjectPosition(const glm::vec3& worldPos) {
    if (!selectedObject || !isDragging) return;

    selectedObject->setPosition(worldPos);

    std::cout << "Moved object ID " << selectedObject->getId() << " to: " << worldPos.x << ", " << worldPos.y << ", " << worldPos.z << std::endl;
}

void Application::testHomogeneousCoordinates() {
    auto currentScene = getCurrentScene();
    if (!currentScene) return;

    auto& objects = currentScene->getObjects();
    for (auto& obj : objects) {
        auto shader = obj->getShaderProgram();
        if (shader) {
            shader->useProgram();

            //shader->setUniform("w", 1.0f);
            //shader->setUniform("w", 2.0f);
            shader->setUniform("w", 500.0f);
            //shader->setUniform("w", 0.5f);
        }
    }
}

void Application::testCustomMatrix()
{
    auto currentScene = getCurrentScene();
    if (!currentScene) return;

    auto& objects = currentScene->getObjects();
    for (auto& obj : objects) {

        auto shader = obj->getShaderProgram();
        if (!shader) continue;

        shader->useProgram();

        glm::mat4 custom = glm::mat4(1.0f);

        custom[3][3] = 20.0f;

        shader->setUniform("customMatrix", custom);
        shader->setUniform("useCustomMatrix", true);
    }
}
