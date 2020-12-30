#include "ChunkBuilder.h"
#include "GLCore/Core/Input.h"

//using namespace GLCore;
//using namespace GLCore::Utils;

struct NeighborsVisible // VisibleFaces
{
	bool xPos, xNeg, yPos, yNeg, zPos, zNeg;
};

ChunkBuilder::ChunkBuilder()
	: m_FirstRender(true), m_RebuildChunk(false), m_ChunkActive(true),
	m_TickCount(0), m_BlocksRendered(0), m_ChunksRendered(0), m_RenderCycleCount(0),
	m_Noise(std::rand()), m_NoiseGain(7), m_NoiseFreq(0.049f), 
	m_Transform(1.0), m_Model(1.0), m_TextureID(0)
{
}

ChunkBuilder::~ChunkBuilder()
{
	delete m_TempShader;
}

void ChunkBuilder::Init(const CameraController& cameraController)
{
	m_CameraController = std::make_unique<CameraController>(cameraController);

	m_ChunkPositionOffset = { 0 };
	m_BlockPositionOffset = { 0 };
	GenerateNoise(); //m_NoiseMap.Generate();

	m_TempShader = new ShaderProgram("assets/shaders/sandbox.vert.glsl", "assets/shaders/sandbox.frag.glsl");
	m_ChunkShader = std::make_unique<ShaderProgram>(*m_TempShader);

	m_VB = std::make_unique<VertexBuffer>(nullptr, CHUNKDATA::VERTICESPERCHUNK * sizeof(CubeVertex));
	m_IB = std::make_unique<IndexBuffer>();
	GenerateIndex(); // doesnt need to be done until after vertex gen?
	GenerateVertices();

	m_VA = std::make_unique<VertexArray>();
	m_Layout = std::make_unique<VertexBufferLayout>();
	m_Layout->Push<float>(3); // Position
	m_Layout->Push<float>(4); // Color
	m_Layout->Push<float>(2); // Tex Coords
	m_Layout->Push<float>(1); // Tex ID
	m_VA->AddBuffer(*m_VB, *m_Layout);

	m_TexDoor = new Texture("assets/textures/door.png");
	m_TexIce = new Texture("assets/textures/ice.png");
	m_TexSand = new Texture("assets/textures/sand.png");
	m_TexDoor->BindUnit(0);
	m_TexIce->BindUnit(1);
	m_TexSand->BindUnit(2);

	m_ChunkRenderer = std::make_unique<Renderer>();
	m_ChunkRenderer->Init(); // sets opengl render options

}

void ChunkBuilder::Update(float ticks)
{
	m_ChunkRenderer->Clear(0.1f, 0.0f, 0.1f, 1.0f);
	m_RenderCycleCount++;
	m_TickCount++;

	if (m_TickCount >= 30) {
		m_TickCount = 0;
		GenerateNoise(); 
		//m_NoiseMap.Generate();
	}

	// create a public camera data struct that voxelLayer can read from
	m_CameraController->OnUpdate(ticks);
	m_CameraRotation = m_CameraController->GetCamera().GetRotation();
	m_ZoomLevel = m_CameraController->GetZoomLevel();
	m_CameraPosition = m_CameraController->GetCamera().GetPosition();
	m_CameraDir = m_CameraController->GetCamera().GetDirection();
	m_CameraFront = m_CameraController->GetCamera().GetFront();
	m_CameraUp = m_CameraController->GetCamera().GetUp();
	m_CursorPos.x = Input::GetMouseX();
	m_CursorPos.y = Input::GetMouseY();
}

void ChunkBuilder::UpdateShader(float textureSlot)
{
	m_TextureID = textureSlot;
	int slots[3] = { 0, 1, 2 };

	/// Calculate Transforms
	m_Transform = glm::mat4(1.0f);
	m_Transform = glm::translate(m_Transform, glm::vec3(-4.0f, -4.0f, -20.0f));
	//m_Transform = glm::rotate(m_Transform, glm::radians(m_RotationIndex.x), m_XAxis);

	// move to UpdateShaders() in Chunk class
	m_ChunkShader->SetUniformMat4f("u_Projection", m_CameraController->GetCamera().GetPerspectiveMatrix());
	m_ChunkShader->SetUniformMat4f("u_View", m_CameraController->GetCamera().GetViewMatrix());
	m_ChunkShader->SetUniformMat4f("u_Transform", m_Transform);
	m_ChunkShader->SetUniformMat4f("u_Model", m_Model);
	m_ChunkShader->SetUniform1i("u_RenderTextures", m_RenderTextures);
	m_ChunkShader->SetUniform1iv("u_Textures", 3, slots);
}

void ChunkBuilder::Render()
{
	ChunkLayout layout;
	int* OffsetTable = layout.Generate(CHUNKLAYOUT::NONE);
	
	for (int x = 0; x < CHUNKDATA::TERRAINSIZE; x++)
	{
		for (int z = 0; z < CHUNKDATA::TERRAINSIZE; z++)
		{
			// sets chunk offset from the origin
			m_ChunkPositionOffset = 
			{
				// chunk position offset. fix:: chunks with offset of 0 broke
				(float)(x * CHUNKDATA::CHUNKSIZE),
				(float)(0 + OffsetTable[m_ChunksRendered]) * CHUNKDATA::CHUNKSIZE ,
				(float)(z * CHUNKDATA::CHUNKSIZE)
			}; 
			
			if (m_FirstRender) {
				m_ChunkList.push_back(Chunk(true, m_ChunkPositionOffset[0], m_ChunkPositionOffset[1], m_ChunkPositionOffset[2]));
				//std::cout << m_ChunkList.size() << "\n";
			}
			if(m_RebuildChunk) {
				// chunk rebuild after change
			}

			GenerateVertices();
			m_ChunkRenderer->Draw(*m_VA, *m_IB, *m_ChunkShader);
			m_ChunksRendered++;
		}
	}

	m_FirstRender = false;
	m_ChunksRendered = 0; // Reset chunk count after each render cycle
	m_RenderCycleCount++;
}

void ChunkBuilder::ReSeedNoise() // maybe remove
{
	m_Noise.SetSeed(std::rand());
	// m_NoiseMap.Reseed(std::rand());
	GenerateNoise();
	// m_NoiseMap.Generate();
}

void ChunkBuilder::GenerateNoise()
{
	m_Noise.SetFrequency(m_NoiseFreq);
	m_Noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

	int index = 0;
	for (int i = 0; i < CHUNKDATA::MAXCHUNKCOUNT; i++)
	{
		// Generates a height value for each block in the current chunk
		for (int x = 0; x < CHUNKDATA::CHUNKSIZE; x++)
		{
			for (int y = 0; y < CHUNKDATA::CHUNKSIZE; y++)
			{
				for (int z = 0; z < CHUNKDATA::CHUNKSIZE; z++)
				{
					float fX = (float)(x + z + i);
					float fZ = (float)(x + i);
					m_NoiseData[index] = (int)(m_NoiseGain * m_Noise.GetNoise(fX, fZ));

					//std::cout << "index: " << index << " == " << m_NoiseData[index] << "\n";
					index++;
				}
			}
		}
	}
}

// Generates an index buffer with indices for 1 chunk
void ChunkBuilder::GenerateIndex()
{
	uint32_t offset = 0;
	uint32_t* target = m_Indices.data();

	for (size_t i = 0; i < CHUNKDATA::INDICESPERCHUNK; i += CHUNKDATA::INDICESPERBLOCK)
	{
		target[i + 0] = 0 + offset; target[i + 1] = 1 + offset; target[i + 2] = 2 + offset;
		target[i + 3] = 2 + offset; target[i + 4] = 3 + offset; target[i + 5] = 0 + offset;
		target[i + 6] = 1 + offset; target[i + 7] = 4 + offset; target[i + 8] = 7 + offset;
		target[i + 9] = 7 + offset; target[i + 10] = 2 + offset; target[i + 11] = 1 + offset;
		target[i + 12] = 4 + offset; target[i + 13] = 5 + offset; target[i + 14] = 6 + offset;
		target[i + 15] = 6 + offset; target[i + 16] = 7 + offset; target[i + 17] = 4 + offset;
		target[i + 18] = 5 + offset; target[i + 19] = 0 + offset; target[i + 20] = 3 + offset;
		target[i + 21] = 3 + offset; target[i + 22] = 6 + offset; target[i + 23] = 5 + offset;
		target[i + 24] = 5 + offset; target[i + 25] = 4 + offset; target[i + 26] = 1 + offset;
		target[i + 27] = 1 + offset; target[i + 28] = 0 + offset; target[i + 29] = 5 + offset;
		target[i + 30] = 3 + offset; target[i + 31] = 2 + offset; target[i + 32] = 7 + offset;
		target[i + 33] = 7 + offset; target[i + 34] = 6 + offset; target[i + 35] = 3 + offset;

		offset += 8; // 8 indices per block
	}

	//m_IB->SetCount(m_Indices.size()); // debug indices.size = 18,432
	m_IB->AddData(m_Indices.data(), m_Indices.size() * sizeof(uint32_t));
}

// Generates a vertex buffer with vertices for 1 chunk
void ChunkBuilder::GenerateVertices()
{
	int offset = 0;
	int noiseIndex = m_ChunksRendered * CHUNKDATA::BLOCKPERCHUNK; // iterates by BLOCKPERCHUNK to track index for TOTAL chunks
	m_BlocksRendered = 0;

	CubeVertex* buffer = m_Vertices.data();
	for (int x = 0; x < CHUNKDATA::CHUNKSIZE; x++)
	{
		for (int y = 0; y < CHUNKDATA::CHUNKSIZE; y++)
		{
			for (int z = 0; z < CHUNKDATA::CHUNKSIZE; z++)
			{

				if (z == 0 || z == 7 || x == 0 || x == 7 || y == 7) {
				//if (y == 0) {
				//if (1) {
					m_BlockPositionOffset[1] = m_NoiseData[noiseIndex];
					noiseIndex++;

					buffer = CreateCube(
						buffer,
						x + m_ChunkPositionOffset[0] + m_BlockPositionOffset[0],
						y + m_ChunkPositionOffset[1] + m_BlockPositionOffset[1],
						z + m_ChunkPositionOffset[2] + m_BlockPositionOffset[2],
						m_TextureID,
						1.0 // make dynamic
					);

					m_BlocksRendered++;
					offset += CHUNKDATA::INDICESPERBLOCK;
				}

				// end block gen
			}
		}
	}

	m_VB->AddSubData(m_Vertices.data(), m_Vertices.size() * (uint32_t)sizeof(CubeVertex), 0);
	m_IB->SetCount(m_Indices.size());
}




