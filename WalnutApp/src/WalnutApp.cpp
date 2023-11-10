#include <iostream>
#include <ostream>

#include "GameLayer.h"
#include "imgui.h"
#include "HamsterPoweredEngine/Application.h"
#include "HamsterPoweredEngine/Layer.h"
#include "HamsterPoweredEngine/World.h"
#include "HamsterPoweredEngine/Graphics/Material.h"
#include "HamsterPoweredEngine/Graphics/Model.h"
#include "HamsterPoweredEngine/Graphics/RenderTarget2D.h"
#include "HamsterPoweredEngine/Graphics/RenderPipeline.h"



class EditorLayer : public Hamster::Layer
{
public:
	ImVec2 viewportSize;
	
	//Render resources
	
	std::shared_ptr<Hamster::Material> Mat;
	std::shared_ptr<Hamster::Material> DesatMat;
	
	virtual void OnUIRender() override
	{
		//Viewport window
		ImGui::Begin("Viewport");
		auto size = ImGui::GetContentRegionAvail();
		if (size.x != viewportSize.x || size.y != viewportSize.y)
		{
			viewportSize = size;
			Hamster::Application::OnViewportResized.Emit({viewportSize.x, viewportSize.y});
			OnViewportResize();
		}
		if (auto img = Hamster::Application::GetViewportOutput().Get())
		{
			ImGui::Image(ImTextureID(img->GetTexture().Get()->GetRendererID()), size, {0, 1}, {1, 0});
		}
		
		ImGui::End();

		
		ImGui::Begin("Inspector");
		ImGui::End();

		ImGui::Begin("SceneTree");
		ImGui::End();
	}

	void OnViewportResize()
	{
		
	}

	std::unique_ptr<Hamster::RenderPass> pass;
	std::unique_ptr<Hamster::RenderPass> desaturate;

	
	virtual void OnAttach() override
	{
	}
	
	virtual void OnUpdate(float ts) override
	{
		Timestep timestep(ts);


	}
};

Hamster::Application* Hamster::CreateApplication(int argc, char** argv)
{
	Hamster::ApplicationSpecification spec;
	spec.Name = "Hamster Powered Engine";
	
	Hamster::Application* app = new Hamster::Application(spec);
	app->PushLayer<GameLayer>();
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