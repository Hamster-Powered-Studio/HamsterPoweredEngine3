-- WalnutExternal.lua


IncludeDir = {}

IncludeDir["glm"] = "../vendor/glm"

LibraryDir = {}

Library = {}


group "Dependencies"
   include "vendor/imgui"
   include "vendor/glfw"
group ""

group "Core"
include "HamsterPoweredEngine"
group ""