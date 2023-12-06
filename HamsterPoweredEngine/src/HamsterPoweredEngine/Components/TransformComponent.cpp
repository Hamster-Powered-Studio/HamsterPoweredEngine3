#include "TransformComponent.h"

#include <glm/gtx/quaternion.hpp>

void TransformComponent::RecalculateTransform()
{
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 rotationMatrix = glm::toMat4(rotation);
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
    transform = translationMatrix * rotationMatrix * scaleMatrix;
    isDirty = false;
}

bool TransformComponent::IsDirty()
{
    return isDirty;
}

glm::vec3 TransformComponent::GetForwardVector() const
{
    return rotation * glm::vec3{1, 0, 0};
}
