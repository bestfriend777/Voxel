#pragma once

#include "Scene.h"
#include "Renderer.h"
#include "imgui/ImIncluded.h"

namespace scene {

	class ClearColor : public Scene
	{
	public:
		ClearColor();
		~ClearColor(); 

		void OnUpdate(float deltaTime) override;
		void OnEvent() override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		glm::vec4 m_Color;

		std::unique_ptr<VertexBuffer> m_VB;
		std::unique_ptr<VertexBufferLayout> m_VL;
		std::unique_ptr<VertexArray> m_VA;
		std::unique_ptr<IndexBuffer> m_IB;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Renderer> m_Renderer;
	};
}