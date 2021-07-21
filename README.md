# Gradient Engine

 #### Overview

 - Gradient engine provides a set of abstractions above low-level platform dependent things such as working with graphics and input
 - Currently it supports OpenGL rendering
 - Provides forward rendering pipeline with post-processing support and shadow mapping
 - Graphics module provides basic shaders and classes to implement custom rendering pipelines
 - Building process is simple. All dependencies are already included, so all you need is CMake and C++ compiler
 - Doesn't use any Windows-specific libraries, so it builds on Linux as well
 - Has graphics test module with ImGui interface to test graphics features
 
 #### Nearest Goals
 
 - Deffered rendering pipeline
 - Scene model and a simple level-editor
 - Support of 3d formats (.obj, .fbx)
 - Working with network
 - Other graphics API support
 - Android build support
 - Documentation
 
 #### How to build
 1. Install Visual Studio or any other modern C++ environment
 2. Install CMake
 3. Clone the repository
 4. Run CMake and generate makefiles or visual studio solution
 5. Build the solution
 
 > tested on Windows 10 and Visual Studio 2019
