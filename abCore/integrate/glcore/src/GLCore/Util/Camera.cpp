#include "glpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace GLUtils {

	Camera::Camera(float fov, float width, float height, float n, float f)
		: m_ViewMatrix(1.0f)
	{
		SetPerspective(fov, width, height, n, f);
		m_ViewMatrix = glm::lookAt(m_Position, m_Front, glm::vec3(0.0f, 1.0f, 0.0f));
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RecalculateViewMatrix();
	}

	void Camera::SetFront(const glm::vec3& direction)
	{
		m_Front = glm::normalize(direction);
		RecalculateViewMatrix();
	}

	void Camera::SetRight(const glm::vec3& right)
	{
		// Is it faster to calculate on request or should m_right be updated in recalculateviewmatrix?
		// TODO: HAVE SETRIGHT() CHANGE CAMERA ROTATION ON CHANGE
		m_Right = glm::normalize(glm::cross(m_Up, m_Front));
	}

	void Camera::SetRotation(float rotation)
	{
		//m_Rotation = rotation; 
		//RecalculateViewMatrix(); 
	}

	void Camera::SetPerspective(float fov, float width, float height, float n, float f)
	{
		m_PerspectiveMatrix = glm::perspective(glm::radians(fov), width/height, n, f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::RecalculateViewMatrix()
	{
		// move to its own func VVV
		m_Right = glm::normalize(glm::cross(m_Up, m_Front));

		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
		m_ViewProjectionMatrix = m_PerspectiveMatrix * m_ViewMatrix;
	}

}