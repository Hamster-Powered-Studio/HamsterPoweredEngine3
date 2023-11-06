#include <iostream>
#include <ostream>

#include "imgui.h"
#include "HamsterPoweredEngine/Application.h"
#include "HamsterPoweredEngine/Layer.h"
#include "HamsterPoweredEngine/Node.h"


class EditorLayer : public Hamster::Layer
{
public:
	virtual void OnUIRender() override
	{
		
		ImGui::Begin("Viewport");
		ImGui::End();

		ImGui::Begin("Inspector");
		ImGui::End();

		ImGui::Begin("SceneTree");
		ImGui::End();

	}
};

Hamster::Application* Hamster::CreateApplication(int argc, char** argv)
{
	Hamster::ApplicationSpecification spec;
	spec.Name = "Hamster Powered Engine";
	
	Hamster::Application* app = new Hamster::Application(spec);
	app->PushLayer<EditorLayer>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}