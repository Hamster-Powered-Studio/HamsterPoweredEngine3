#pragma once

#include "Application.h"

#ifdef WL_PLATFORM_WINDOWS

extern Hamster::Application* Hamster::CreateApplication(int argc, char** argv);
bool g_ApplicationRunning = true;

namespace Hamster {

    int Main(int argc, char** argv)
    {
        while (g_ApplicationRunning)
        {
            Hamster::Application* app = Hamster::CreateApplication(argc, argv);
            app->Run();
            delete app;
        }

        return 0;
    }

}

#ifdef WL_DIST

#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    return Hamster::Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
    return Hamster::Main(argc, argv);
}

#endif // WL_DIST

#endif // WL_PLATFORM_WINDOWS
