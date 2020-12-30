#include "glpch.h"
#include "CameraController.h"

#include "GLCore/Core/Input.h"
#include "GLCore/Core/KeyCodes.h"

namespace GLUtils {
	// rewrite camera constructor values so they dont throw away the values for the screen size
	// the way it is currently written uses a range -1.0f, 1.0f
	// the rewrite should make it so you have to rewrite the positions to be in the range of the screen size 

	CameraController::CameraController(float fov, float width, float height, float n, float f, bool rotation)
		: m_Width(width), m_Height(height), m_AspectRatio(width/height), m_Camera(m_ZoomLevel + fov, width, height, n, f), m_Rotation(rotation), 
		m_LastX(width/2), m_LastY(height/2)
	{
		// negative degrees rotate counter clockwise??
		m_fov = glm::radians(fov);
		m_Yaw = -90.0f;
		m_Pitch = 1.0f;
		// Note that we convert the angle to radians first
		m_CameraDirection.x = cos(glm::radians(m_Yaw)); 
		m_CameraDirection.z = sin(glm::radians(m_Yaw));
	}

	void CameraController::OnUpdate(Timestep ts)
	{
		//Updating the cameras m_up vec3 dynamically allows you to implement space engineers style roll
			//implemented if: m_up is updated to reflect the viewers up vector after rolling
		if (Input::IsKeyPressed(HZ_KEY_W)){
			m_CameraPosition += m_CameraTranslationSpeed * m_Camera.GetFront() * ts.GetSeconds();
		}
		if (Input::IsKeyPressed(HZ_KEY_S)){
			m_CameraPosition -= m_CameraTranslationSpeed * m_Camera.GetFront() * ts.GetSeconds();
		}
		if (Input::IsKeyPressed(HZ_KEY_A)){
			glm::vec3 vec = glm::normalize(glm::cross(m_Camera.GetFront(), m_Camera.GetUp()));
			m_CameraPosition -= vec * m_CameraTranslationSpeed * ts.GetSeconds();
		}
		if (Input::IsKeyPressed(HZ_KEY_D)){
			glm::vec3 vec = glm::normalize(glm::cross(m_Camera.GetFront(), m_Camera.GetUp()));
			m_CameraPosition += vec * m_CameraTranslationSpeed * ts.GetSeconds();
		}		
		if (Input::IsKeyPressed(HZ_KEY_SPACE)){
			glm::vec3 vec = glm::normalize(glm::cross(m_Camera.GetFront(), m_Camera.GetRight()));
			m_CameraPosition += vec * m_CameraTranslationSpeed * ts.GetSeconds();
		}
		if (Input::IsKeyPressed(HZ_KEY_C)){
			//glm::vec3 right = 
			glm::vec3 vec = glm::normalize(glm::cross(m_Camera.GetFront(), m_Camera.GetRight()));
			m_CameraPosition -= vec * m_CameraTranslationSpeed * ts.GetSeconds();
		}
		
		if (Input::IsKeyPressed(HZ_KEY_LEFT_SHIFT)) {
			m_Rotation = false;
			m_LastX = Input::GetMouseX();
			m_LastY = Input::GetMouseY();
		}
			
		else
			m_Rotation = true;

		if (m_Rotation)
		{
			float x = Input::GetMouseX();
			float y = Input::GetMouseY();
			m_XOffset = (x - m_LastX) * m_CameraRotationSpeed;
			m_YOffset = (m_LastY - y) * m_CameraRotationSpeed;
			m_LastX = x;
			m_LastY = y;
			m_Yaw += m_XOffset;
			m_Pitch += m_YOffset;

			m_CameraDirection.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
			m_CameraDirection.y = sin(glm::radians(m_Pitch));				  
			m_CameraDirection.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
			m_Camera.SetFront(m_CameraDirection);

			if (m_Pitch > 89.0f)
				m_Pitch = 89.0f;
			if (m_Pitch < -89.0f)
				m_Pitch = -89.0f;
		}

		m_Camera.SetPosition(m_CameraPosition);
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(GLCORE_BIND_EVENT_FN(CameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(GLCORE_BIND_EVENT_FN(CameraController::OnWindowResized));
	}

	void CameraController::SetProjection()
	{
		// UPDATE OR REMOVE
	}

	void CameraController::SetPerspective(float fov, float width, float height, float n, float f)
	{
		m_Camera.SetPerspective(fov, width, height, n, f);
	}


	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		return false;
	}

	bool CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		return false;
	}

}