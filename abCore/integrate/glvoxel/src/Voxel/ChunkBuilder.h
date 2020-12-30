#pragma once

#include "VoxelGL.h"
#include "NoiseMap.h"
#include "Renderer.h"

//#include "VoxelLib.h"
#include "ChunkData.h"
#include "ChunkLayout.h"
#include "Chunk.h" // includes Block.h
#include "Cube.h" // includes CreateCube.h

using namespace GLCore;
using namespace GLUtils;

class ChunkBuilder
{
public:
	ChunkBuilder();
	~ChunkBuilder();

	void Init(const CameraController& cameraController); 
	void Update(float ticks);
	void UpdateShader(float textureSlot);
	void Render(); 

	// remove
	void ReSeedNoise(); // move to noise class
	void GenerateNoise(); // move to noise class
	inline int GetNoiseGain() { return m_NoiseGain; }
	inline float GetNoiseFreq() { return m_NoiseFreq; }
	inline void SetNoiseGain(int gain) { m_NoiseGain = gain; }
	inline void SetNoiseFreq(float freq) { m_NoiseFreq = freq; }

private:
	//void GenerateChunk(float x, float y, float z);
	void GenerateIndex(); // move to chunk manager
	void GenerateVertices(); // move to block class

public:

private:
	// Management variables
	int m_TickCount, m_BlocksRendered, m_ChunksRendered, m_RenderCycleCount;
	std::vector<Chunk> m_ChunkList; // temp?

	// Opengl data
	bool m_FirstRender, m_RebuildChunk, m_RenderTextures, m_ChunkActive; // update
	glm::mat4 m_Model, m_Transform; // to shader?
	float m_TextureID;
	Texture* m_TexDoor, * m_TexIce, * m_TexSand;
	
	// OpenGL objects
	std::unique_ptr<Renderer> m_ChunkRenderer;
	std::unique_ptr<VertexBuffer> m_VB;
	std::unique_ptr<IndexBuffer> m_IB;	
	std::unique_ptr<VertexArray> m_VA;	
	std::unique_ptr<VertexBufferLayout> m_Layout; 
	std::unique_ptr<ShaderProgram> m_ChunkShader;
	ShaderProgram* m_TempShader;

	// Containers for chunk/block data
	std::array<float, 3> m_ChunkPositionOffset;
	std::array<float, 3> m_BlockPositionOffset;
	std::array<uint32_t, CHUNKDATA::INDICESPERCHUNK> m_Indices;
	std::array<CubeVertex, CHUNKDATA::VERTICESPERCHUNK> m_Vertices;

	// Camera variables
	std::unique_ptr<CameraController> m_CameraController;
	glm::vec3 m_CameraPosition, m_CameraFront, m_CameraDir, m_CameraUp;
	float m_ZoomLevel, m_CameraRotation;
	//float m_RenderDistance;
	glm::vec2 m_CursorPos;

	// REMOVE
	FastNoiseLite m_Noise;
	int m_NoiseGain;
	float m_NoiseFreq;
	std::array<int32_t, CHUNKDATA::MAXBLOCKCOUNT> m_NoiseData;
	std::array<uint32_t, CHUNKDATA::MAXCHUNKCOUNT> m_NoiseSeedTable; // working?
	std::array<float, CHUNKDATA::MAXCHUNKCOUNT> m_NoiseFreqTable;

};