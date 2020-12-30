#pragma once

#include "GLHelper.h"
#include "GLStd.h"

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer();
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void AddData(const void* data, unsigned int size);
	void AddSubData(const void* data, unsigned int size, int offsetSize);
	void* GetMapBuffer();
	
	void Bind() const;
	void Unbind() const;
};