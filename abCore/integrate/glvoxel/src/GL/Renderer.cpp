#include "Renderer.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function <<
			" " << file << ":" << line << std::endl;
	}
	return true;
}

void Renderer::Init()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
}

void Renderer::Clear(float v0, float v1, float v2, float v3) const
{
	glClearColor(v0, v1, v2, v3);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(const ShaderProgram& shader) const
{
	shader.Bind();
	m_VA->Bind();
	m_IB->Bind();

	if (m_RenderFaces)
		glDrawElements(GL_TRIANGLES, m_IB->GetCount(), GL_UNSIGNED_INT, nullptr);
	else
		glDrawElements(GL_LINES, m_IB->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawWireFrame(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	glDrawElements(GL_LINES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawWireFrame(const ShaderProgram& shader) const
{
	shader.Bind();
	m_VA->Bind();
	m_IB->Bind();
	glDrawElements(GL_LINES, m_IB->GetCount(), GL_UNSIGNED_INT, nullptr);
}
