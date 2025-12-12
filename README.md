# scope

A lightweight 3D rendering engine in C++17 using OpenGL 3.3, SDL2 and Dear ImGui. Load different OBJ models, apply Phong lighting, tweak things in real-time via a live UI.
Math library made from scratch, image loader made from scratch.

https://github.com/user-attachments/assets/bfa5aa4d-bfdf-44c0-a7ab-438579b10fa5

## Quick Start

Get started with a single command:

```bash
git clone https://github.com/2czu/scope.git && cd scope
make && ./scop
```

## What it does

Load and render OBJ models with per-material submeshes. Phong lighting with a single point light source. Real-time lighting editing (will definitely upgrade this) via ImGui. Free-look camera with WASD + mouse. Texture support (BMP). Automatic normal computation from geometry.

## Controls

- **W/A/S/D**: Move camera forward / left / back / right.
- **V**: Capture mouse (enable free-look) and hide OS cursor.
- **B**: Release mouse (disable free-look) and show OS cursor.
- **Mouse (when captured)**: Look around (camera rotation is driven by mouse movement while captured).
- **ESC**: Quit the application.
- **I / K**: Move active point light along +Y / -Y.
- **J / L**: Move active point light along -X / +X.
- **U / O**: Move active point light along -Z / +Z.
- **1 / 2**: Toggle texture mode (`renderer.applyTexture = 0` / `1`).

## Architecture

The engine follows a clean modular design with clear separation of concerns:

```
scope/
├── Application
│   ├── SDL2 window + OpenGL context init
│   └── Main loop (events, update, render)
│
├── Renderer
│   ├── renderScene() - draws objects + light cube
│   └── renderImGui() - UI overlay
│
├── Scene
│   ├── Objects (std::vector<Object3D>)
│   ├── Camera
│   └── LightSource
│
├── Object3D
│   ├── Mesh
│   ├── ShaderProgram
│   └── Transform
│
├── Mesh
│   ├── VAO/VBO (vertex data)
│   ├── subMesh[] (per-material index buffers)
│   └── Material pointers
│
├── Parser
│   ├── OBJ loader (vertices, faces)
│   ├── MTL loader (material properties)
│   └── Vertex caching + normal computation
│
├── ShaderProgram
│   ├── Shader (compile)
│   └── Link + uniform management
│
└── Material
    └── MTL properties (Ka, Kd, Ks, Ns)
```

Each component is in its own file (.hpp/.cpp). Two shaders ship with the engine: shader.vs/.fs (per-object Phong), lightCube.vs/.fs (basic shader). ImGui builds as a static library (libimgui.a) and links into the main executable.

## Prerequisites

Linux (Ubuntu/Debian tested). C++17 compiler (GCC 9+, Clang 10+). SDL2 dev headers (`sudo apt-get install libsdl2-dev`). Make.

## Customize

Drop OBJ + MTL in assets/objs/ and assets/mats/, update Application::run() to load them. Edit assets/shaders/shader.fs to tweak lighting. Add new shaders by creating .vs/.fs pairs in assets/shaders/ and instantiating ShaderProgram with the base name.

## Building & Linking

ImGui is built once as libimgui.a, then linked into the main executable. `make fclean` wipes both project and ImGui builds. This avoids recompiling ImGui on every source change.

## What's planned

Enhanced UI. Skybox rendering with cubemaps. Particle system (GPU-driven). Multi-format image loading (PNG, JPEG, TGA). Post-processing (Bloom, FXAA, tone mapping). Deferred rendering pipeline.

## Credits

GLAD (OpenGL loader), Dear ImGui (UI), SDL2 (window/input),

https://github.com/user-attachments/assets/b22d43c8-0e81-4d8f-88f8-a3428680947f