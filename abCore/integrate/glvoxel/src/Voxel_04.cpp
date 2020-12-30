#include "Voxel_04.h"

#include "GLCore/Core/KeyCodes.h"
#include "GLCore/Core/Input.h"

using namespace GLCore;
using namespace GLUtils;

// ChunkSize = 8 || BlockCount = 512 || VerticesPerChunk = 4096 || IndicesPerChunk = 18,432
// GlobalMaxChunks = 64 || GlobalMaxBlockCount = 32,768 || GlobalMaxVertexCount = 262,144 || GlobalMaxIndexCount = 1,179,648

Voxel_04::Voxel_04(float appWidth, float appHeight)

	: m_TickCount(0), m_Width(appWidth), m_Height(appHeight), m_TextureSlot(0),
	m_CameraController(45.0f, appWidth, appHeight, 0.1f, 10.0f), m_Camera(m_CameraController.GetCamera())
{
	// TODO: REMOVE vvvv
	noisefreq = 0.045f;
	noisegain = 14;
	m_CameraController.SetZoomLevel(1.0);
	m_CameraController.SetRotationSpeed(0.1f);
	m_CameraController.SetTranslationSpeed(20.0f);
	m_CameraPosition = m_CameraController.GetCamera().GetPosition();
	m_CameraRotation = m_CameraController.GetCamera().GetRotation();
	m_CameraFront = m_CameraController.GetCamera().GetFront();
	m_CameraController.SetPerspective(45.0f, m_Width, m_Height, 0.1f, 2000.0f); // already initalized..
}

Voxel_04::~Voxel_04()
{
}

void Voxel_04::OnAttach()
{
	EnableGLDebugging();

	m_ChunkBuilder = std::make_unique<ChunkBuilder>();
	m_ChunkBuilder->Init(m_CameraController);
} 
 
void Voxel_04::OnDetach()
{
}

void Voxel_04::OnEvent(Event& event)
{
	m_CameraController.OnEvent(event);

	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<MouseButtonPressedEvent>(
		[&](MouseButtonPressedEvent& e)
		{
			return false;
		});
	dispatcher.Dispatch<MouseButtonReleasedEvent>(
		[&](MouseButtonReleasedEvent& e)
		{
			return false;
		});
	dispatcher.Dispatch<KeyPressedEvent>(
		[&](KeyPressedEvent& e)
		{
			return false;
		});
	dispatcher.Dispatch<KeyReleasedEvent>(
		[&](KeyReleasedEvent& e)
		{
			return false;
		});
}

void Voxel_04::OnUpdate(Timestep ts)
{
	//////// PRERENDER
	UpdateInfo(ts);

	//////////////////////////////////////////////////////////////////////////////////
	//					RENDER START
	//////////////////////////////////////////////////////////////////////////////////

	m_ChunkBuilder->Update(ts);
	m_ChunkBuilder->UpdateShader((float)m_TextureSlot); // redundant
	m_ChunkBuilder->Render();

	//////////////////////////////////////////////////////////////////////////////////
    //					RENDER END
	//////////////////////////////////////////////////////////////////////////////////

}

void Voxel_04::OnImGuiRender()
{

	ImGui::Begin("Controls");

	ImGui::Text("\n\n");
	ImGui::InputFloat2("Cursor -> ScreenPos ", &m_CursorPos.x);
	ImGui::Text("\n\n");

	if (ImGui::Button("Reset Camera", ImVec2(200, 50))) {
		m_CameraController.SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));
		m_CameraController.SetZoomLevel(1.0f);
		m_CameraController.ResetCamRotation();
	}
	ImGui::InputFloat3("Camera -> Position", &m_CameraPosition.x);
	//ImGui::InputFloat("Camera -> Rotation ", &m_CameraRotation);
	//ImGui::InputFloat("Camera -> Zoom Level ", &m_ZoomLevel);
	ImGui::Text("\n\n");

	if (ImGui::Button("Reset Model", ImVec2(200, 50))) {
		m_RotationIndex = glm::vec3(0.0f);
	}
	ImGui::SliderFloat3("Model -> Rotate", &m_RotationIndex.x, 0.0f, 360.0f);
	//ImGui::Checkbox("Render Textures", &m_RenderTextures);
	//ImGui::Checkbox("Render Faces", &m_RenderFaces);

	ImGui::Text("\n\n");
	ImGui::InputFloat3("Camera -> Camera Up ", &m_CameraUp.x);
	ImGui::InputFloat3("Camera -> Front", &m_CameraFront.x);
	ImGui::InputFloat3("Camera -> X Dir ", &m_CameraDir.x);
	
	if (ImGui::Button("ReSeed Noise", ImVec2(200, 50))) {
		m_ChunkBuilder->ReSeedNoise();
		m_ChunkBuilder->GenerateNoise();
	}
	ImGui::SliderFloat("Noise -> Frequency", &noisefreq, 0.001f, 0.1f); 
	ImGui::SliderInt("Noise -> Gain", &noisegain, 1, 50);

	ImGui::Text("\n\n");
	ImGui::SliderInt("Texture ID", &m_TextureSlot, 0, 3);

	ImGui::End();
}

void Voxel_04::UpdateInfo(Timestep ts)
{
	m_ChunkBuilder->SetNoiseFreq(noisefreq);
	m_ChunkBuilder->SetNoiseGain(noisegain);

	// move all the cam/screen/cursor stuff to its own update function
	m_CameraController.OnUpdate(ts);
	m_CameraPosition = m_CameraController.GetCamera().GetPosition();
	m_CameraRotation = m_CameraController.GetCamera().GetRotation();
	m_ZoomLevel = m_CameraController.GetZoomLevel();
	m_CameraDir = m_CameraController.GetCamera().GetDirection();
	m_CameraFront = m_CameraController.GetCamera().GetFront();
	m_CameraUp = m_CameraController.GetCamera().GetUp();
	m_CursorPos.x = Input::GetMouseX();
	m_CursorPos.y = Input::GetMouseY();
}

