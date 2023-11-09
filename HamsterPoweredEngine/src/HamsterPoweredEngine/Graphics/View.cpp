#include "View.h"


#include <glm/gtc/matrix_transform.hpp>

namespace Hamster
{
    View::View()
    {
        m_viewMatrix = glm::mat4(1.0f);
        m_position = glm::vec3(0, 0, 0);
        m_orientation = glm::vec3(0, 0, 1);
    
    }

    View::~View()
    {
    }

    const glm::mat4& View::GetViewMatrix() const
    {
        // We only recalculate the view matrix if the position or orientation has changed
        if (m_viewMatrixDirty)
        {
            m_viewMatrix = glm::lookAt(m_position, m_position + m_orientation, glm::vec3(0, 1, 0));
            m_viewMatrixDirty = false;
        }
        return m_viewMatrix;
    }

    void View::SetViewMatrix(const glm::mat4& _viewMatrix)
    {
        m_viewMatrix = _viewMatrix;
    }

    void View::SetPosition(const glm::vec3& _position)
    {
        m_position = _position;
        m_viewMatrixDirty = true;
    }

    void View::SetOrientation(const glm::vec3& _orientation)
    {
        m_orientation = _orientation;
        m_viewMatrixDirty = true;
    }

    glm::vec3 View::GetPosition() const
    {
        return m_position;
    }

    glm::vec3 View::GetOrientation() const
    {
        return m_orientation;
    }
}

