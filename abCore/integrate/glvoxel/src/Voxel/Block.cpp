#include "Block.h"

Block::Block(bool active, float scale, BlockType type)
	: m_Active(active), m_Scale(scale), m_Type(type)
{
}

Block::~Block()
{
}

