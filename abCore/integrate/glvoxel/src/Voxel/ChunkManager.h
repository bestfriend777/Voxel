#pragma once
#include "VoxelGL.h"
//#include "Renderer.h" // remove CreateCube from renderer, move to Voxel.h


class ChunkManager {
public:
	ChunkManager();
	~ChunkManager();

private:
	void UpdateLoadList();
	void UpdateSetupList();
	void UpdateRebuildList();
	void UpdateUnloadList();
	void UpdateVisibilityList();
	void UpdateRenderList();

public:

private:
	std::vector <glm::vec3> m_ActiveChunkList; // temp

	std::vector <glm::vec3> m_LoadList;
	std::vector <glm::vec3> m_SetupList;
	std::vector <glm::vec3> m_RebuildList;
	std::vector <glm::vec3> m_UnloadList;
	std::vector <glm::vec3> m_UpdateVisibilityList;
	std::vector <glm::vec3> m_RenderList;
};