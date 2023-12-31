﻿#pragma once

#include "Layer.h"

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <glm/vec2.hpp>

#include "Delegate.h"
#include "Graphics/GLHandle.h"
#include "Graphics/RenderTarget2D.h"

struct GLFWwindow;
namespace Hamster
{
        

        struct ApplicationSpecification
        {
            std::string Name = "Walnut App";
            uint32_t Width = 1600;
            uint32_t Height = 900;
        };

        class Application
        {
        public:
            Application(const ApplicationSpecification& applicationSpecification = ApplicationSpecification());
            ~Application();

            static Application& Get();

            void Run();
            void SetMenubarCallback(const std::function<void()>& menubarCallback) { m_MenubarCallback = menubarCallback; }
		
            template<typename T>
            void PushLayer()
            {
                static_assert(std::is_base_of<Layer, T>::value, "Pushed type is not subclass of Layer!");
                m_LayerStack.emplace_back(std::make_shared<T>())->OnAttach();
            }

            void PushLayer(const std::shared_ptr<Layer>& layer) { m_LayerStack.emplace_back(layer); layer->OnAttach(); }

            void Close();

            static float GetTime();
            GLFWwindow* GetWindowHandle() const { return m_WindowHandle; }
            glm::vec2 GetWindowSize() const;
            static void SetVSync(bool enabled);
            
            static void SetViewportOutput(GLHandle<RenderTarget2D> target) { Get().m_ViewportOutput = target; }
            static GLHandle<RenderTarget2D> GetViewportOutput() { return Get().m_ViewportOutput; }

            inline static Delegate<glm::vec2> OnViewportResized;
        
        private:
            void Init();
            void Shutdown();
        private:
            ApplicationSpecification m_Specification;
            GLFWwindow* m_WindowHandle = nullptr;
            bool m_Running = false;

            float m_TimeStep = 0.0f;
            float m_FrameTime = 0.0f;
            float m_LastFrameTime = 0.0f;

            std::vector<std::shared_ptr<Layer>> m_LayerStack;
            std::function<void()> m_MenubarCallback;

            GLHandle<RenderTarget2D> m_ViewportOutput;
        };

        // Implemented by CLIENT
        Application* CreateApplication(int argc, char** argv);
}
