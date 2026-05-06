#include "Application.h"

int main(void) {
    Application* app = Application::getInstance();

    if (!app->initialization()) {
        return -1;
    }

    app->run();

    Application::destroyInstance();
    return 0;
}