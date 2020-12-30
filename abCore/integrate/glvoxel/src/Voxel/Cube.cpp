#include "Cube.h"

Cube::Cube(float x, float y, float z, float size, float textureID)
	: m_Size(size), m_TexID(textureID), m_Position(x, y, z)
{
	m_Index = {
		0, 1, 2, 2, 3, 0,
		1, 4, 7, 7, 2, 1,
		4, 5, 6, 6, 7, 4,
		5, 0, 3, 3, 6, 5,
		5, 4, 1, 1, 0, 5,
		3, 2, 7, 7, 6, 3
	};

	GenerateVectorMesh();
	GenerateRawMesh();
}

Cube::~Cube()
{
}

// Experiment with altering which vertices summed with m_Size
// There are a lot of detailed variations of geometry available from doing this

void Cube::GenerateVectorMesh()
{
	Quad3Vertex v0 = {
		glm::vec3(m_Position.x, m_Position.y, m_Position.z + m_Size),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		m_TexID
	};
		
	Quad3Vertex v1 = {
		glm::vec3(m_Position.x + m_Size, m_Position.y, m_Position.z + m_Size),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		m_TexID
	};
	
	Quad3Vertex v2 = {
		glm::vec3(m_Position.x + m_Size, m_Position.y + m_Size, m_Position.z + m_Size),
		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		m_TexID

	};
	
	Quad3Vertex v3 = {
		glm::vec3(m_Position.x, m_Position.y + m_Size, m_Position.z + m_Size),
		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		m_TexID
	};

	Quad3Vertex v4 = {
		glm::vec3(m_Position.x + m_Size, m_Position.y, m_Position.z),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		m_TexID
	};
	
	Quad3Vertex v5 = {
		glm::vec3(m_Position.x, m_Position.y, m_Position.z),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		m_TexID
	};
	
	Quad3Vertex v6 = {
		glm::vec3(m_Position.x, m_Position.y + m_Size, m_Position.z),
		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		m_TexID
	};
	
	Quad3Vertex v7 = {
		glm::vec3(m_Position.x + m_Size, m_Position.y + m_Size, m_Position.z),
		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		m_TexID
	};
	
	m_ArrayMesh = { v0, v1, v2, v3, v4, v5, v6, v7 };

	m_Mesh.push_back(v0);
	m_Mesh.push_back(v1);
	m_Mesh.push_back(v2);
	m_Mesh.push_back(v3);
	m_Mesh.push_back(v4);
	m_Mesh.push_back(v5);
	m_Mesh.push_back(v6);
	m_Mesh.push_back(v7);

}

//glm::vec3 Position; //glm::vec4 Color; //glm::vec2 TexCoords; //float TexID;
void Cube::GenerateRawMesh()
{
	m_RawMesh = { 
		// 0-3
		m_Position.x,          m_Position.y,          m_Position.z + m_Size,	1.0, 1.0, 1.0, 1.0,  0.0, 0.0,  m_TexID,
		m_Position.x + m_Size, m_Position.y,          m_Position.z + m_Size,	1.0, 1.0, 1.0, 1.0,  1.0, 0.0,  m_TexID,
		m_Position.x + m_Size, m_Position.y + m_Size, m_Position.z + m_Size,	1.0, 1.0, 1.0, 1.0,  1.0, 1.0,  m_TexID,
		m_Position.x,          m_Position.y + m_Size, m_Position.z + m_Size,	1.0, 1.0, 1.0, 1.0,  0.0, 1.0,  m_TexID,
		// 4-7																					    		   	
		m_Position.x + m_Size, m_Position.y,          m_Position.z,				1.0, 1.0, 1.0, 1.0,  0.0, 1.0,  m_TexID,
		m_Position.x,		   m_Position.y,          m_Position.z,				1.0, 1.0, 1.0, 1.0,  1.0, 1.0,  m_TexID,
		m_Position.x,		   m_Position.y + m_Size, m_Position.z,				1.0, 1.0, 1.0, 1.0,  1.0, 0.0,  m_TexID,
		m_Position.x + m_Size, m_Position.y + m_Size, m_Position.z,				1.0, 1.0, 1.0, 1.0,  0.0, 0.0,  m_TexID,
	};
}

void Cube::SendRawMesh(const VertexBuffer& vbo)
{
	// vbo->AddVertexToMesh(v0)
	// vbo->AddVertexToMesh(v1)
	// vbo->AddVertexToMesh(v2)
	// vbo->AddVertexToMesh(v3)
	// vbo->AddVertexToMesh(v4)
	// vbo->AddVertexToMesh(v5)
	// vbo->AddVertexToMesh(v6)
	// vbo->AddVertexToMesh(v7)

	// ibo->AddTriangleToMesh(0-5)
	// ibo->AddTriangleToMesh(6-12)
	// ibo->AddTriangleToMesh(13-18)
	// ibo->AddTriangleToMesh(19-24)
	// ibo->AddTriangleToMesh(25-30)
	// ibo->AddTriangleToMesh(31-36)
}

std::vector<float> Cube::GetMeshRaw()
{
	return m_RawMesh;
}

std::array<Quad3Vertex, 8> Cube::GetMeshArray()
{
	return m_ArrayMesh;
}

std::vector<unsigned int> Cube::GetTrianglesRaw()
{
	return m_Index;
}





























































