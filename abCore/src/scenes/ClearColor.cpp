#include "ClearColor.h"

namespace scene {

	ClearColor::ClearColor()
		: m_Color(0.0, 0.0, 1.0, 1.0)
	{
		m_VB = std::make_unique<VertexBuffer>();
		m_VL = std::make_unique<VertexBufferLayout>();
		m_VA = std::make_unique<VertexArray>();
		m_IB = std::make_unique<IndexBuffer>();
		m_Shader = std::make_unique<Shader>("assets/shaders/basic.vert.glsl", "assets/shaders/basic.frag.glsl");
		m_Renderer = std::make_unique<Renderer>();
		m_Renderer->Init();
	}

	ClearColor::~ClearColor()
	{
	}

	void ClearColor::OnUpdate(float deltaTime)
	{

	}

	void ClearColor::OnEvent()
	{
	}

	void ClearColor::OnRender()
	{
		m_Renderer->Clear(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	}

	void ClearColor::OnImGuiRender()
	{

	}
}