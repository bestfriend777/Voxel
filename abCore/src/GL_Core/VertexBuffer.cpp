#include "VertexBuffer.h"

/*	glMapBuffer Implementation  */
//float data[] = {
//  0.5f, 1.0f, -0.35f
//  [...]
//};
//glBindBuffer(GL_ARRAY_BUFFER, buffer);
//// get pointer
//void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
//// now copy data into memory
//memcpy(ptr, data, sizeof(data));
//// make sure to tell OpenGL we're done with the pointer
//glUnmapBuffer(GL_ARRAY_BUFFER);

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &m_RendererID);
	//glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_RendererID);
	//glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::AddData(const void* data, unsigned int size)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

void VertexBuffer::AddSubData(const void* data, unsigned int size, int offsetSize)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferSubData(GL_ARRAY_BUFFER, offsetSize, size, data);
}

void* VertexBuffer::GetMapBuffer()
{
	void *ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	return ptr;
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
 }

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}