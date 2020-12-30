#pragma once
#include <glm/glm.hpp>

namespace GLUtils {

	class Camera
	{
	public:
		Camera(float fov, float width, float height, float n, float f);


		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position);

		// This should replace Rotation or join it 


		inline float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation);

		inline const glm::mat4& GetPerspectiveMatrix() const { return m_PerspectiveMatrix; }
		void SetPerspective(float fov, float width, float height, float n, float f);

		// INLINE ONLY
		inline const glm::vec3& GetDirection() const { return m_Direction; }
		inline void SetDirection(const glm::vec3& direction) { m_Direction = direction; RecalculateViewMatrix(); }

		inline const glm::vec3& GetUp() const { return m_Up; }
		inline void SetUp(const glm::vec3& up) { m_Up = up; RecalculateViewMatrix(); }
		inline const glm::vec3& GetFront() const { return m_Front; }
		void SetFront(const glm::vec3& front);
		inline const glm::vec3& GetRight() const { return m_Right; }
		void SetRight(const glm::vec3& right);

		inline const float GetFOV() { return m_FOV; }
		inline void SetFOV(const float fov) { m_FOV = fov; }
		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline void SetProjection(); // CURRENTLY DOES NOTHING
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline void SetViewMatrix(const glm::mat4& view) { m_ViewMatrix = view; }
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }


	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_PerspectiveMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 3.0f };
		glm::vec3 m_Up = { 0.0f, 1.0f, 0.0f };
		glm::vec3 m_Front = { 0.0f, 0.0f, -1.0f };
		glm::vec3 m_Right = glm::normalize(glm::cross(m_Up, m_Front));;

		glm::vec3 m_Direction = { 0.0f, 0.0f, -1.0f };
		glm::vec3 m_Target = { 0.0f, 0.0f, 0.0f };

		

		//glm::vec3 m_Right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), m_Direction));
		//glm::vec3 m_Up = glm::cross(m_Direction, m_Right);
		float m_FOV = 45.0f;
		float m_Rotation = 0.0f;
	};

}
