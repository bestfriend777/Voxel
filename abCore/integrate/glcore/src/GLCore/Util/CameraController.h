#pragma once

#include "Camera.h"
#include "GLCore/Core/Timestep.h"

#include "GLCore/Events/ApplicationEvent.h"
#include "GLCore/Events/MouseEvent.h"

using namespace GLCore;

namespace GLUtils {

	class CameraController
	{
	public:
		CameraController(float fov, float width, float height, float n, float f, bool rotation = true);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		Camera& GetCamera() { return m_Camera; }
		const Camera& GetCamera() const { return m_Camera; }

		void SetProjection();
		void SetPerspective(float fov, float width, float height, float n, float f);

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { /*UPDATE WITH ZOOM*/ };

		void SetPosition(glm::vec3 pos) { m_CameraPosition = pos; m_Camera.SetPosition(m_CameraPosition);}
		// void SetDirection....

		void SetTranslationSpeed(float f) { m_CameraTranslationSpeed = f; };
		void SetRotationSpeed(float f) { m_CameraRotationSpeed = f; };
		void ResetCamRotation() { m_CameraRotation = 0.0f; };

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		Camera m_Camera;
		float m_Width, m_Height, m_AspectRatio;

		// most of these should be in the camera itself
		bool m_Rotation;
		float m_MouseX, m_MouseY;
		float m_LastX, m_LastY, m_XOffset, m_YOffset;
		float m_fov, m_Pitch, m_Yaw, m_Roll;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_CameraDirection;
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f, m_ZoomLevel = 3.0f;
	};

}