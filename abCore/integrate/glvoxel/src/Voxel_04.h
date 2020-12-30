#pragma once

//#include <iostream>
//#include <memory>
//#include <cstdio>

#include "glpch.h"

#include "ABUtils/Logger.h"

#include "GLCore.h"
#include "GLCoreUtils.h"

//#include "VoxelGL.h"
#include "ChunkBuilder.h"	 // to VoxGLCore?

class Voxel_04 : public GLCore::Layer
{
public:
	Voxel_04(float width, float height);
	virtual ~Voxel_04();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(GLCore::Event& event) override;
	virtual void OnUpdate(GLCore::Timestep ts) override;
	virtual void OnImGuiRender() override;
private:
	void UpdateInfo(GLCore::Timestep ts);

private:
	float m_Width, m_Height;
	uint32_t m_TickCount;

	// opengl objs
	GLUtils::Camera m_Camera;
	GLUtils::CameraController m_CameraController;
	std::unique_ptr<ChunkBuilder> m_ChunkBuilder; // move to chunk controller

	// misc variables 
	int noisegain;
	float noisefreq;
	int m_TextureSlot;
	float m_ZoomLevel, m_CameraRotation;
	glm::vec2 m_CursorPos;
	glm::vec3 m_CameraPosition, m_CameraFront, m_CameraDir, m_CameraUp;

	// matrix variables
	float m_DegreesX, m_DegreesY, m_DegreesZ = (0.0f); // move  GlobalData	or CameraController
	glm::vec3 m_XAxis = glm::vec3(1.0f, 0.0f, 0.0f); // move to GlobalData	or CameraController
	glm::vec3 m_YAxis = glm::vec3(0.0f, 1.0f, 0.0f); // move to GlobalData	or CameraController
	glm::vec3 m_ZAxis = glm::vec3(0.0f, 0.0f, 1.0f); // move to GlobalData	or CameraController
	glm::vec3 m_RotationIndex = glm::vec3(0.0f, 0.0f, 0.0f); // GlobalData	or CameraController
};