#include "Chunk.h"

Chunk::Chunk(float x, float y, float z, bool isActive)
	: m_Active(isActive), m_Position({ x, y, z })
{
}

Chunk::~Chunk()
{
}

void Chunk::AddBlock(Block block)
{
}

void Chunk::RemoveBlock(uint32_t element)
{
}

void Chunk::SetActive(bool isActive)
{
	m_Active = isActive;
}

bool Chunk::GetActiveState()
{
	return m_Active;
}

void Chunk::SetPosition(float x, float y, float z)
{
	m_Position = { x, y, z };
}

float* Chunk::SetPosition()
{
	return m_Position.data();
}
