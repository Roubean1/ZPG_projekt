# ZPG Project

Semester project for ZPG created in C++ and OpenGL. The project contains several 3D scenes, camera controls, lights, shaders, textures, models, and simple animations.

## Requirements

- Visual Studio 2022
- Windows 10/11
- `x64` platform

All required libraries are included directly in the project:

- GLEW
- GLFW
- GLM
- stb
- tinyobjloader

## How to Run

1. Open the `zpg_tok_novy.sln` file in Visual Studio 2022.
2. In the top toolbar, select the `Debug` configuration and the `x64` platform.
3. Build the project using `Build > Build Solution` or the `Ctrl+Shift+B` shortcut.
4. Run the project using `Local Windows Debugger` or the `F5` key.

After a successful launch, an OpenGL window with the application will open.

## Controls

- `W`, `A`, `S`, `D` - move the camera
- right mouse button + mouse movement - look around with the camera
- `1` to `6` - switch scenes
- left mouse button - select an object / interact with objects depending on the current scene
- `F` - toggle the spotlight in scenes where it is available
- `Delete` - delete the selected object
- `M` - move the selected object
- `B` - enable/disable spline point drawing
- `N` - start movement along the spline
- `C` - clear spline points
- `Esc` - cancel the current action or close the application

## Scenes

The project contains the following scenes:

- Triangle scene
- Spheres scene
- Forest scene
- Solar system scene
- Meteor scene
- Race track scene

Scenes can be switched using keys `1` to `6`.

## Project Structure

- `zpg_tok_novy.sln` - Visual Studio 2022 solution file
- `zpg_tok_novy/` - project source files
- `zpg_tok_novy/assets/` - 3D models, textures, and other assets
- `zpg_tok_novy/shaders/` and `zpg_tok_novy/ShaderSource/` - shader files
- `zpg_tok_novy/Libraries/` - included external libraries
- `zpg_tok_novy/Models/` - header files with models

## Notes

The project is prepared mainly for running through Visual Studio 2022. Simply open the `.sln` file, build the solution, and run the application.
