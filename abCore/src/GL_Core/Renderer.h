#pragma once
#include "GL_Core.h"
#include <GLHelper.h>
#include <GLStd.h>


#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	void Init(); // Partially move to Chunk class
	void Clear(float v0, float v2, float v3, float v4) const;

	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Draw(const Shader& shader) const;
	void DrawArrays(const VertexArray& va, const Shader& shader, const unsigned int vertices) const;

	// inline functions
	inline void RenderFaces(bool rf) { m_RenderFaces = rf; }

private:
	std::unique_ptr<VertexBuffer> m_VB;
	std::unique_ptr<IndexBuffer> m_IB;
	std::unique_ptr<VertexArray> m_VA;
	std::unique_ptr<VertexBufferLayout> m_Layout;

	bool m_RenderFaces = true;
};