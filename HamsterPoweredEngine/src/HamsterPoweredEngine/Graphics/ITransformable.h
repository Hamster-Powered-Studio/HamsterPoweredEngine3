#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Hamster
{
    // Interface for objects that have a transform and can be manipulated
    class ITransformable
    {
    public:
        // Immediately set position to a given value
        void SetPosition(glm::vec3 _position) { position = _position; RecalculateTransform(); }

        // Immediately set rotation to a quaternion value
        void SetRotation(glm::quat _rotation) { rotation = _rotation; RecalculateTransform(); }

        // Immediately set rotation to a euler angle value
        void SetRotation(glm::vec3 _rotation) { rotation = glm::quat(_rotation); RecalculateTransform(); }

        // Set the scale of the object on each axis individually
        void SetScale(glm::vec3 _scale) { scale = _scale; RecalculateTransform(); }

        // Set the scale of the object on all axis at once
        void SetScale(float _scale) { scale = glm::vec3(_scale, _scale, _scale); RecalculateTransform(); }

        // Get the current position of the object
        const glm::vec3& GetPosition() const { return position; }

        // Get the current rotation of the object as a quaternion
        const glm::quat& GetRotation() const { return rotation; }

        // Get the current rotation of the object as euler angles
        const glm::vec3& GetRotationEuler() const { return glm::eulerAngles(rotation); }

        // Get the current scale of the object
        const glm::vec3& GetScale() const { return scale; }

        // Translate the object by a given vector
        void Translate(glm::vec3 _translation) { position += _translation; RecalculateTransform(); }

        // Rotate the object by a given quaternion
        void Rotate(glm::quat _rotation) { rotation *= _rotation; RecalculateTransform();}

        // Rotate the object by a given euler angle
        void Rotate(glm::vec3 _rotation) { rotation *= glm::quat(_rotation); RecalculateTransform();}

        // Rotate the object by a given axis and angle
        void Rotate(glm::vec3 _axis, float _angleDeg) { rotation *= glm::angleAxis(glm::radians(_angleDeg), _axis); RecalculateTransform();}

        // Rotate the object by a given axis and angle in radians
        void RotateRad(glm::vec3 _axis, float _angleRad) { rotation *= glm::angleAxis(_angleRad, _axis); RecalculateTransform();}

        // Scale the object relative to its current scale on all axis
        void Scale(glm::vec3 _scale) { scale *= _scale; RecalculateTransform();}

        // Scale the object relative to its current scale on each axis individually
        void Scale(float _scale) { scale *= glm::vec3(_scale, _scale, _scale); RecalculateTransform();}

        // Updates the transform matrix
        void RecalculateTransform();

        // Get the transform matrix
        const glm::mat4& GetTransform()
        {

            return transform;
        }

        // Overwrite the transform matrix
        void SetTransform(const glm::mat4& _transform)
        {
            transform = _transform;
            position = glm::vec3(transform[3]);
            rotation = glm::quat_cast(transform);
            scale = glm::vec3(glm::length(transform[0]), glm::length(transform[1]), glm::length(transform[2]));
        }
        
    private:
        glm::vec3 position = {0, 0, 0};
        glm::quat rotation = glm::quat(1, 0, 0, 0);
        glm::vec3 scale = {1, 1, 1};
        glm::mat4 transform = glm::mat4(1.0f);
    
    };

}
