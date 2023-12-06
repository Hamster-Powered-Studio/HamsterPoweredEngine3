#pragma once
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/detail/type_quat.hpp>
#include <glm/gtc/quaternion.hpp>

struct TransformComponent
{
    public:
        TransformComponent(const glm::mat4& transform = glm::mat4(1.0f)): transform(transform) {}
    
        // Immediately set position to a given value
        void SetPosition(glm::vec3 _position) { position = _position; isDirty = true; }

        // Immediately set rotation to a quaternion value
        void SetRotation(glm::quat _rotation) { rotation = _rotation; isDirty = true; }

        // Immediately set rotation to a euler angle value
        void SetRotation(glm::vec3 _rotation) { rotation = glm::quat(_rotation); isDirty = true; }

        // Set the scale of the object on each axis individually
        void SetScale(glm::vec3 _scale) { scale = _scale; isDirty = true; }

        // Set the scale of the object on all axis at once
        void SetScale(float _scale) { scale = glm::vec3(_scale, _scale, _scale); isDirty = true; }

        // Get the current position of the object
        const glm::vec3& GetPosition() const { return position; }

        // Get the current rotation of the object as a quaternion
        const glm::quat& GetRotation() const { return rotation; }

        // Get the current rotation of the object as euler angles
        const glm::vec3& GetRotationEuler() const { return glm::eulerAngles(rotation); }

        // Get the current scale of the object
        const glm::vec3& GetScale() const { return scale; }

        // Translate the object by a given vector
        void Translate(glm::vec3 _translation) { position += _translation; isDirty = true; }

        // Rotate the object by a given quaternion
        void Rotate(glm::quat _rotation) { rotation *= _rotation; isDirty = true;}

        // Rotate the object by a given euler angle
        void Rotate(glm::vec3 _rotation) { rotation *= glm::quat(_rotation); isDirty = true;}

        // Rotate the object by a given axis and angle
        void Rotate(glm::vec3 _axis, float _angleDeg) { rotation *= glm::angleAxis(glm::radians(_angleDeg), _axis); isDirty = true;}

        // Rotate the object by a given axis and angle in radians
        void RotateRad(glm::vec3 _axis, float _angleRad) { rotation *= glm::angleAxis(_angleRad, _axis); isDirty = true;}

        // Scale the object relative to its current scale on all axis
        void Scale(glm::vec3 _scale) { scale *= _scale; isDirty = true;}

        // Scale the object relative to its current scale on each axis individually
        void Scale(float _scale) { scale *= glm::vec3(_scale, _scale, _scale); isDirty = true;}

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

        bool IsDirty();
        glm::vec3 GetForwardVector() const;

    private:
        glm::vec3 position = {0, 0, 0};
        glm::quat rotation = glm::quat(1, 0, 0, 0);
        glm::vec3 scale = {1, 1, 1};
        glm::mat4 transform = glm::mat4(1.0f);
        bool isDirty = true;
    
};
