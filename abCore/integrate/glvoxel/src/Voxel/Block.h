#pragma once

enum BlockType {
	BlockType_Default = 0, 
	BlockType_Dirt,
	BlockType_Grass,
	BlockType_Stone,
	BlockType_Sand,
	BlockType_Wood,
	BlockType_Water,

	BlockType_NumTypes,
};

class Block
{
public:
	Block(bool active, float scale = 1.0, BlockType type = BlockType_Default);
	~Block();

	inline BlockType GetType() { return m_Type; }
	inline bool GetActiveState() { return m_Active; }
	inline float GetScale() { return m_Scale; }

	inline void SetType(BlockType type) { m_Type = type; }
	inline void SetActive(bool active) { m_Active = active; }
	inline void SetScale(float scale) { m_Scale = scale; }

private:
	BlockType m_Type;
	bool m_Active;
	float m_Scale;
};