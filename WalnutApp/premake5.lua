project "WalnutApp"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp", "Resources/**.glsl"  }
   flags { "MultiProcessorCompile"}

   includedirs
   {
      "../vendor/imgui",
      "../vendor/glfw/include",
      "../vendor/glad",
      "../vendor/stb_image",
      "../vendor/slot_map/slot_map",
      "../vendor/entt/single_include/entt",

      "../HamsterPoweredEngine/src",

      "%{IncludeDir.VulkanSDK}",
      "%{IncludeDir.glm}",
      "%{IncludeDir.assimp}"
   }

    links
    {
        "HamsterPoweredEngine",
    }




   targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
   objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

   postbuildcommands
   {
     "{COPYDIR} Resources ../bin/" .. outputdir .. "/%{prj.name}/Resources/"
   }

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
      kind "WindowedApp"
      defines { "WL_DIST" }
      runtime "Release"
      optimize "On"
      symbols "Off"