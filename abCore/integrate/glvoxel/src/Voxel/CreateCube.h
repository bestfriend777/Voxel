#pragma once
#include <array>
//#include "VoxelLib.h"

struct CubeVertex
{
	glm::vec3 Position;
	glm::vec4 Color;
	glm::vec2 TexCoords;
	float TextureID;
};

static CubeVertex* CreateCube(CubeVertex* target, float x, float y, float z, float texID, float size)
{
	target->Position = { x, y, z + size };
	target->Color = { 1.0f, 1.0f, 1.0f, 1.0f };
	target->TexCoords = { 0.0f, 0.0f };
	target->TextureID = texID;
	target++;

	target->Position = { x + size, y, z + size };
	target->Color = { 0.0f, 0.0f, 1.0f, 1.0f };
	target->TexCoords = { 1.0f, 0.0f };
	target->TextureID = texID;
	target++;

	target->Position = { x + size, y + size, z + size };
	target->Color = { 0.0f, 1.0f, 0.0f, 1.0f };
	target->TexCoords = { 1.0f, 1.0f };
	target->TextureID = texID;
	target++;

	target->Position = { x, y + size, z + size };
	target->Color = { 1.0f, 0.0f, 0.0f, 1.0f };
	target->TexCoords = { 0.0f, 1.0f };
	target->TextureID = texID;
	target++;

	target->Position = { x + size, y, z };
	target->Color = { 1.0f, 1.0f, 1.0f, 1.0f };
	target->TexCoords = { 0.0f, 1.0f };
	target->TextureID = texID;
	target++;

	target->Position = { x, y, z };
	target->Color = { 0.0f, 0.0f, 1.0f, 1.0f };
	target->TexCoords = { 1.0f, 1.0f };
	target->TextureID = texID;
	target++;

	target->Position = { x, y + size, z };
	target->Color = { 0.0f, 1.0f, 0.0f, 1.0f };
	target->TexCoords = { 1.0f, 0.0f };
	target->TextureID = texID;
	target++;

	target->Position = { x + size, y + size, z };
	target->Color = { 1.0f, 0.0f, 0.0f, 1.0f };
	target->TexCoords = { 0.0f, 0.0f };
	target->TextureID = texID;
	target++;

	return target;
}

static uint32_t* CreateCubeIndex(uint32_t* target) //const uint32_t count, uint32_t* roffset
{
	//uint32_t* p_Offset = roffset;
	uint32_t offset = 0;
	
	//uint32_t indices[18432] = malloc(18432 * sizeof(uint32_t));

	for (size_t i = 0; i < 18432; i += 36)
	{
		target[i +  0] = 0 + offset; target[i +  1] = 1 + offset; target[i +  2] = 2 + offset;
		target[i +  3] = 2 + offset; target[i +  4] = 3 + offset; target[i +  5] = 0 + offset;
		target[i +  6] = 1 + offset; target[i +  7] = 4 + offset; target[i +  8] = 7 + offset;
		target[i +  9] = 7 + offset; target[i + 10] = 2 + offset; target[i + 11] = 1 + offset;
		target[i + 12] = 4 + offset; target[i + 13] = 5 + offset; target[i + 14] = 6 + offset;
		target[i + 15] = 6 + offset; target[i + 16] = 7 + offset; target[i + 17] = 4 + offset;
		target[i + 18] = 5 + offset; target[i + 19] = 0 + offset; target[i + 20] = 3 + offset;
		target[i + 21] = 3 + offset; target[i + 22] = 6 + offset; target[i + 23] = 5 + offset;
		target[i + 24] = 5 + offset; target[i + 25] = 4 + offset; target[i + 26] = 1 + offset;
		target[i + 27] = 1 + offset; target[i + 28] = 0 + offset; target[i + 29] = 5 + offset;
		target[i + 30] = 3 + offset; target[i + 31] = 2 + offset; target[i + 32] = 7 + offset;
		target[i + 33] = 7 + offset; target[i + 34] = 6 + offset; target[i + 35] = 3 + offset;
		offset += 8;
	}

	return target;
}