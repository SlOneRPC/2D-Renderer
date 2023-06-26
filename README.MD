# 2D Renderer
2D Renderer using OpenGL

## Prerequisites
- CMake (https://cmake.org/download/)
- Visual studio 2022 or later
- C++ 20 or later & .NET 6.0

## Setup
Run the following commands:
- `git clone https://github.com/SlOneRPC/2D-Renderer.git --recursive Renderer2D`
- `cd Renderer2D`
- `build-deps.bat`
- `GenerateVS22.bat`

## Overview

### Renderer2D
- OpenGL based renderer
- Supports custom scenes and entities
- Saving and loading from disk using yaml
- A space invaders themed demo called space raiders, and a few other demos avaliable.

### Screenshot testing
- Screenshot comparision testing
- Run in "IntegrationTest" mode! This will compile the renderer correctly for testing.

### Google testing
- Google unit testing
- Covers various aspects of the system
- Run in "UnitTest" mode! This will compile the renderer as a static library to be used for testing.

## External Libraries/Tools
- glew (https://glew.sourceforge.net/)
- glfw (https://www.glfw.org/)
- glm (https://github.com/g-truc/glm)
- premake (https://premake.github.io/)
- stb (https://github.com/nothings/stb)
- yaml-cpp (https://github.com/jbeder/yaml-cpp)
- imgui (https://github.com/ocornut/imgui)