project "HamsterPoweredEngine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"
   flags { "MultiProcessorCompile" }

   files { "src/**.h", "src/**.cpp", "../vendor/glad/src/gl.c", "../vendor/imgui/backends/imgui_impl_opengl3.cpp"}

   includedirs
   {
      "src",

      "../vendor/glfw/include",
      "../vendor/stb_image",
      "../vendor/imgui",
      "../vendor/glad",
      "../vendor/slot_map/slot_map",
      "../vendor/entt/single_include/entt",

      "%{IncludeDir.glm}",
      "%{IncludeDir.assimp}",
      "%{IncludeDir.assimpconfig}"
   }

   links
   {
       "ImGui",
       "GLFW",
       "opengl32",
       "assimp"
   }



   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

   filter "system:windows"
      systemversion "latest"
      defines { "WL_PLATFORM_WINDOWS" }

   filter "configurations:Debug"
      defines { "WL_DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      defines { "WL_RELEASE" }
      runtime "Release"
      optimize "On"
      symbols "On"

   filter "configurations:Dist"
      defines { "WL_DIST" }
      runtime "Release"
      optimize "On"
      symbols "Off"