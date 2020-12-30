#pragma once

#include "GLCore/Core/Layer.h"

#include "GLCore/Events/ApplicationEvent.h"
#include "GLCore/Events/KeyEvent.h"
#include "GLCore/Events/MouseEvent.h"

namespace GLCore {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();

		//virtual void ImGuiLayer::OnEvent(Event& event);
		//bool ImGuiLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e);
		//bool ImGuiLayer::OnKeyPressed(KeyPressedEvent& e);

		virtual void OnEvent(Event& event);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
	private:
		float m_Time = 0.0f;
	};

}