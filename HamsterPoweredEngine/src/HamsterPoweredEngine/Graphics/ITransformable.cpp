﻿#include "ITransformable.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Hamster
{
    void ITransformable::RecalculateTransform()
    {
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 rotationMatrix = glm::toMat4(rotation);
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
        transform = translationMatrix * rotationMatrix * scaleMatrix;
    }

}
