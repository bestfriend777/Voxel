#pragma once

#include <vector>
#include <array>

#include "Block.h"

// can remove most of these includes after writing chunkManager/block classes
//#include "VoxelGLCore.h"
//#include "VoxelLib.h"

/*
	TODO:
	- Convert this class to a chunk manager
	- Create a new chunk class
		- Move chunk constructor and destructors
		- Chunk offset and other basic data
		- Most classes will stay in the manager
	- Implement block class
		- will just contain basic material info
		- IndexBuffer will go to ChunkManager or ChunkRenderer
	- Might need to extend index buffer so that each chunk has unique indices?

	Voxel Hierarchy:
		- World
		- Chunk
		- Block
		- Triangle/Index
		- Point/Vertex
*/

class Chunk
{
public:
	Chunk(float x, float y, float z, bool isActive = true);
	~Chunk();

	void AddBlock(Block block);
	void RemoveBlock(uint32_t element);

	void SetActive(bool isActive);
	void SetPosition(float x, float y, float z);
	bool GetActiveState();
	float* SetPosition();

private:
	bool m_Active; 
	std::array<float, 3> m_Position;
	std::vector<Block> m_Blocks;
};