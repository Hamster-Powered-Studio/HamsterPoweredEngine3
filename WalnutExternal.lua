-- WalnutExternal.lua


IncludeDir = {}

IncludeDir["glm"] = "../vendor/glm"
IncludeDir["assimp"] = "../vendor/assimp_premake/include"
--IncludeDir["assimpconfig"] = "../vendor/assimp/build/x64/include"

LibraryDir = {}

Library = {}


group "Dependencies"
   include "vendor/imgui"
   include "vendor/glfw"
   include "vendor/assimp_premake"
group ""

group "Core"
include "HamsterPoweredEngine"
group ""