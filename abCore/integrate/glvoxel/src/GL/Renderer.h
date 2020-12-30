#pragma once

#include <GLStd.h>
#include <GLHelper.h>

//#include "VoxelGL.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"
//#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


//#include "voxel/VoxelLib.h"
//#include "CreateCube.h" // remove

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

	void Draw(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shader) const;
	void Draw(const ShaderProgram& shader) const;
	void DrawWireFrame(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shader) const;
	void DrawWireFrame(const ShaderProgram& shader) const;

	// inline functions
	inline void RenderFaces(bool rf) { m_RenderFaces = rf; }

private:
	std::unique_ptr<VertexBuffer> m_VB;
	std::unique_ptr<IndexBuffer> m_IB;
	std::unique_ptr<VertexArray> m_VA;
	std::unique_ptr<VertexBufferLayout> m_Layout;

	bool m_RenderFaces = true;
};