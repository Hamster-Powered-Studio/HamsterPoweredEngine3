# Hamster Powered Engine 3

Hamster Powered Engine 3 is a full rewrite of past iterations of Hamster Powered Engine. It is based on OpenGL 4.6, utilising Dear ImGui for the editor. 
Currently supports Windows. Setup scripts support Visual Studio 2022 by default.

This project is based off of Studio Cherno's [Walnut](https://github.com/StudioCherno/Walnut) template, however has been heavily modified to use an OpenGL backend.

## Requirements
- [Visual Studio 2022](https://visualstudio.com) (not strictly required, however included setup scripts only support this)


## Getting Started
Once you've cloned, run `scripts/Setup.bat` to generate Visual Studio 2022 solution/project files. Once you've opened the solution, you can run the WalnutApp project to see a basic example (code in `WalnutApp.cpp`).

### 3rd party libaries
- [Dear ImGui](https://github.com/ocornut/imgui)
- [GLFW](https://github.com/glfw/glfw)
- [stb_image](https://github.com/nothings/stb)
- [GLM](https://github.com/g-truc/glm)

### Additional
- Hamster Powered Engine 3 uses the [Roboto](https://fonts.google.com/specimen/Roboto) font ([Apache License, Version 2.0](https://www.apache.org/licenses/LICENSE-2.0))
