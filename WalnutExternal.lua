-- WalnutExternal.lua


IncludeDir = {}

IncludeDir["glm"] = "../vendor/glm"
IncludeDir["assimp"] = "../vendor/assimp_premake/include"

LibraryDir = {}

Library = {}


group "Dependencies"
   include "vendor/imgui"
   include "vendor/glfw"
   include "vendor/assimp_premake"
   include "vendor/entt"
group ""

group "Core"
include "HamsterPoweredEngine"
group ""