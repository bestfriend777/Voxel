#pragma once

#include "VertexBuffer.h"

#include "GLHelper.h"
#include "GLStd.h"

class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout);
	~VertexArray();

	void PrintAttribData(const VertexBufferLayout& layout);

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};