#include <iostream>
#include <ostream>

#include "imgui.h"
#include "HamsterPoweredEngine/Application.h"
#include "HamsterPoweredEngine/Layer.h"
#include "HamsterPoweredEngine/Node.h"
#include "HamsterPoweredEngine/Graphics/Material.h"
#include "HamsterPoweredEngine/Graphics/RenderTarget2D.h"
#include "HamsterPoweredEngine/Graphics/ShaderLoader.h"
#include "HamsterPoweredEngine/Graphics/VertexArray.h"
#include "HamsterPoweredEngine/Graphics/VertexBuffer.h"



class EditorLayer : public Hamster::Layer
{
public:
	ImVec2 viewportSize;
	
	//Render resources
	GLHandle<Hamster::VertexBuffer> Buffer;
	GLHandle<Hamster::VertexArray> Array;
	GLHandle<Hamster::IndexBuffer> Indices;
	GLHandle<Hamster::RenderTarget2D> RenderTarget;
	Hamster::Material Mat;

	//Mesh info
	std::vector<Hamster::Vertex> verts =
		{
		{{-0.5f, -0.5f, 0.0f}, {0, 0, 1}, {0, 0}, {1, 1, 1, 1}},
		{{0.5f, -0.5f, 0.0f}, {0, 0, 1}, {1, 0}, {1, 1, 1, 1}},
		{{0.5f, 0.5f, 0.0f}, {0, 0, 1}, {1, 1}, {1, 1, 1, 1}},
		{{-0.5f, 0.5f, 0.0f}, {0, 0, 1}, {0, 1}, {1, 1, 1, 1}}
		};

	std::vector<uint32_t> indices =
		{
		2, 3, 0,
		0, 1, 2
	};
	
	virtual void OnUIRender() override
	{
		//Viewport window
		ImGui::Begin("Viewport");
		auto size = ImGui::GetContentRegionAvail();
		if (size.x != viewportSize.x || size.y != viewportSize.y)
		{
			viewportSize = size;
			OnViewportResize();
		}
		ImGui::Image(ImTextureID(RenderTarget.Get()->GetTexture().Get()->GetRendererID()), size);
		ImGui::End();

		
		ImGui::Begin("Inspector");
		ImGui::End();

		ImGui::Begin("SceneTree");
		ImGui::End();
	}

	void OnViewportResize()
	{
		RenderTarget.Get()->SetSize({viewportSize.x, viewportSize.y});
	}
	
	virtual void OnAttach() override
	{
		Node parent("Grungle");
		Node child("gringok");
		parent.AddChild(&child);
		
		parent.Destroy();
		std::cout << (child.GetParent() == nullptr) << std::endl;
		
		
		//Construct mesh
		Buffer = GraphicsResourceManager::ConstructObject<Hamster::VertexBuffer>(verts);
		Indices = GraphicsResourceManager::ConstructObject<Hamster::IndexBuffer>(indices);
		Array = GraphicsResourceManager::ConstructObject<Hamster::VertexArray>();
		Array.Get()->SetIndexBuffer(Indices);
		Array.Get()->AddVertexBuffer(Buffer);
		
		//Construct render texture
		RenderTarget = GraphicsResourceManager::ConstructObject<Hamster::RenderTarget2D>(Hamster::Application::Get().GetWindowSize());
		RenderTarget.Get()->AddAttachment(Hamster::RenderTarget2D::AttachmentType::COLOR);
		RenderTarget.Get()->AddAttachment(Hamster::RenderTarget2D::AttachmentType::DEPTH);
		
		//Create material
		Mat = Hamster::Material(Hamster::ShaderLoader::Load("Resources/Shaders/BasicUnlit.glsl"));
		Mat.SetParameter("uColour", glm::vec4(1, 1, 0, 1));
	}
	
	virtual void OnUpdate(float ts) override
	{
		//Bind the square to draw
		Array.Get()->Bind();
		//Update material parameters
		Mat.SetParameter("uTime", Hamster::Application::Get().GetTime());
		Mat.Apply();
		//Bind and clear the render output
		RenderTarget.Get()->Bind();
		glClear(GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, viewportSize.x, viewportSize.y);
		//Draw the render output
		glDrawElements(GL_TRIANGLES, Indices.Get()->GetCount(), GL_UNSIGNED_INT, nullptr);
		//Bind the main window as the render output
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
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