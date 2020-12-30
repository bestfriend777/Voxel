#pragma once

#include <vector>
#include "VoxelGL.h"
#include "VertexBuffer.h" // sloppy usage?
#include "IndexBuffer.h"

//#include "VoxelLib.h"
#include "CreateCube.h"

struct Quad3Vertex
{
	glm::vec3 Position;
	glm::vec4 Color;
	glm::vec2 TexCoords;
	float TexID;
};

class Cube
{
public:
	Cube(float x, float y, float z, float size, float textureID);
	~Cube();

	inline std::vector<Quad3Vertex> GetMesh() { return m_Mesh; }
	inline glm::vec3 GetPosition() { return m_Position; }
	inline void SetPosition(glm::vec3 position) { m_Position = position; GenerateVectorMesh(); GenerateRawMesh(); }
	inline void SetTextureID(float id) { m_TexID = id; }
	inline void SetSize(float size) { m_Size = size; }

	// TODO: remove (IsActive state is now determined in chunk)
	inline void SetActive(bool state) { m_Active = state; }
	inline bool IsActive() { return m_Active; }

	std::vector<float> GetMeshRaw();
	std::array<Quad3Vertex, 8> GetMeshArray();
	std::vector<unsigned int> GetTrianglesRaw();

private:
	void GenerateVectorMesh();
	void GenerateRawMesh();

	void SendRawMesh(const VertexBuffer& vbo);

private:
	bool m_Active = false;
	std::vector<unsigned int> m_Index;
	float m_Size;
	float m_TexID;
	glm::vec3 m_Position;
	std::vector<Quad3Vertex> m_Mesh;
	std::array<Quad3Vertex, 8> m_ArrayMesh;
	std::vector<float> m_RawMesh;
};