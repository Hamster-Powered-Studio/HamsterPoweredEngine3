#pragma once
#include <glm/fwd.hpp>
#include <glm/mat4x4.hpp>


namespace Hamster
{
    // A view matrix. This is a wrapper around a view matrix. It is used to set the view matrix uniform in shaders
    class View
    {
    public:
        // Create a default view matrix
        View();
        ~View();

        // Get the view matrix
        const glm::mat4& GetViewMatrix() const;
        // Set the view matrix
        void SetViewMatrix(const glm::mat4& _viewMatrix);

        // Set the position of the view matrix
        void SetPosition(const glm::vec3& _position);
        // Set the orientation of the view matrix
        void SetOrientation(const glm::vec3& _orientation);

        // Get the position of the view matrix
        glm::vec3 GetPosition() const;
        // Get the orientation of the view matrix
        glm::vec3 GetOrientation() const;

    private:
        mutable bool m_viewMatrixDirty = true;
        mutable glm::mat4 m_viewMatrix;
    
        glm::vec3 m_position;
        glm::vec3 m_orientation;
    
    };

}
