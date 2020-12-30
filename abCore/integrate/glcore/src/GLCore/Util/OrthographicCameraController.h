#pragma once

#include "OrthographicCamera.h"
#include "GLCore/Core/Timestep.h"

#include "GLCore/Events/ApplicationEvent.h"
#include "GLCore/Events/MouseEvent.h"

using namespace GLCore;

namespace GLUtils {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float width, float height, bool rotation = true);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		void SetProjection(float left, float right, float bottom, float top);
		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; m_Camera.SetProjection(m_Left * m_ZoomLevel, m_Right * m_ZoomLevel, m_Bottom * m_ZoomLevel, m_Top * m_ZoomLevel);}
		void SetPosition(glm::vec3 pos) { m_CameraPosition = pos; m_Camera.SetPosition(m_CameraPosition);}
		void SetTranslationSpeed(float f) { m_CameraTranslationSpeed = f; };
		void SetRotationSpeed(float f) { m_CameraRotationSpeed = f; };
		void ResetCamRotation() { m_CameraRotation = 0.0f; };

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_Left, m_Right, m_Bottom, m_Top = 1.0f;
		float m_WRadius, m_HRadius;
		float m_AspectRatio;
		OrthographicCamera m_Camera;

		bool m_Rotation;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f, m_ZoomLevel = 3.0f;
	};

}