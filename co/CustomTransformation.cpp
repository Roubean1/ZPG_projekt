#include "CustomTransformation.h"

CustomTransformation::CustomTransformation() {
    customMat = glm::mat4(1.0f);
    customMat[3][3] = 20.0f;
}

glm::mat4 CustomTransformation::getMatrix() const {
    return customMat;
}