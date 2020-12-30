#pragma once

#include "GLHelper.h"
#include "GLStd.h"

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	
	// Broken variable. Gets passed size instead;
	unsigned int m_Count;
public:
	IndexBuffer();
	IndexBuffer(const unsigned int* data, unsigned int size);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	void AddData(const unsigned int* data, unsigned int size);

	inline void SetCount(unsigned int count) { m_Count = count; }
	inline unsigned int GetCount() const { return m_Count; }
};