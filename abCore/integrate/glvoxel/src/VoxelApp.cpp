
#include "Voxel_04.h"

#include <GlCore.h>
#include <GLFW/glfw3.h>
#include "GLCore/Core/KeyCodes.h"
#include "GLCore/Core/Input.h"


using namespace GLCore;

class VoxelApp : public Application
{
	using Application::Application;

	// It makes sense to set window size in the app constructor. These values are independent of our projection though
		// their aspect ratio is useful to have
public:
	VoxelApp() : Application("ULTIMATE LIFEFORM", 1900, 1000)
	{
		window = static_cast<GLFWwindow*>(GetWindow().GetNativeWindow());
		PushLayer(new Voxel_04(m_AppWidth, m_AppHeight));
	}
	
	// Attempt to hide and lock cursor using glfwcore
	void OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(
			[&](KeyPressedEvent& e)
			{
				std::cout << " YOU REACHED THE APP CLASS!\n";
				if (Input::IsKeyPressed(HZ_KEY_LEFT_SHIFT)) { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }
				return false;
			});
	}
private:
	GLFWwindow* window; 
};

int main()
{
	std::unique_ptr<VoxelApp> app = std::make_unique<VoxelApp>();
	app->Run();
}