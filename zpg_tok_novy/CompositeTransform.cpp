#include "CompositeTransform.h"

void CompositeTransform::addTransform(std::shared_ptr<Transform> transform) { 
    transforms.push_back(transform);
}

glm::mat4 CompositeTransform::getMatrix() const {
    glm::mat4 result(1.0f);
    for (const auto& transform : transforms) {
        result = result * transform->getMatrix();
    }
    return result;
}

//void CompositeTransform::clear() {
//    transforms.clear();
//}
