# GloomZ

GloomZ is an early-stage game/graphics engine for Windows, written in C++17. It provides a reusable engine library (DLL) and a sandbox application that demonstrates how to build on top of the engine. The project is built with [Premake5](https://premake.github.io/) and targets Visual Studio 2019.

---

## Table of Contents

- [Features](#features)
- [Architecture Overview](#architecture-overview)
- [Project Structure](#project-structure)
- [Prerequisites](#prerequisites)
- [Getting Started](#getting-started)
  - [1. Clone the Repository](#1-clone-the-repository)
  - [2. Generate Visual Studio Projects](#2-generate-visual-studio-projects)
  - [3. Build the Solution](#3-build-the-solution)
  - [4. Run the Sandbox](#4-run-the-sandbox)
- [Build Configurations](#build-configurations)
- [Usage](#usage)
  - [Creating a GloomZ Application](#creating-a-gloomz-application)
  - [Logging API](#logging-api)
- [Dependencies](#dependencies)
- [Roadmap](#roadmap)
- [Contributing](#contributing)

---

## Features

- **DLL-based engine library** — the engine is compiled as a shared library (`GloomZ.dll`) and linked into client applications.
- **Application framework** — a base `GloomZ::Application` class that client code inherits to define their own application.
- **Dual logging system** — separate loggers for engine internals (Core) and client code (Client), backed by [spdlog](https://github.com/gabime/spdlog).
- **Macro logging API** — convenient, level-based logging macros for both the engine and the client.
- **Automated entry point** — `EntryPoint.h` provides the `main()` function automatically; client code only needs to implement `CreateApplication()`.
- **Three build configurations** — Debug (debug symbols), Release (optimized), and Dist (distribution-optimized).
- **Premake5 build system** — reproducible project generation for Visual Studio 2019.

---

## Architecture Overview

```
┌──────────────────────────────────────────────────────────┐
│                      Client Application                  │
│   (inherits GloomZ::Application, implements features)    │
│                      e.g., Sandbox                       │
└──────────────────────┬───────────────────────────────────┘
                       │  links against
┌──────────────────────▼───────────────────────────────────┐
│                    GloomZ Engine (DLL)                   │
│                                                          │
│  ┌─────────────────┐   ┌────────────────────────────┐   │
│  │  Application    │   │  Log (Core & Client)        │   │
│  │  (base class)   │   │  (spdlog wrapper)           │   │
│  └─────────────────┘   └────────────────────────────┘   │
│                                                          │
│  ┌─────────────────┐   ┌────────────────────────────┐   │
│  │  EntryPoint     │   │  Core (platform macros,     │   │
│  │  (main / init)  │   │  GLOOMZ_API dllexport)      │   │
│  └─────────────────┘   └────────────────────────────┘   │
└──────────────────────────────────────────────────────────┘
```

The engine is distributed as a **shared library**. Client applications include only `<GloomZ.h>` and link against the DLL — they never need to touch engine internals directly.

---

## Project Structure

```
GloomZ/
├── GloomZ/                          # Engine library (DLL)
│   ├── src/
│   │   ├── GloomZ.h                 # Public include — use this in client code
│   │   └── GloomZ/
│   │       ├── Application.h/.cpp   # Base Application class
│   │       ├── Core.h               # Platform macros (GLOOMZ_API, etc.)
│   │       ├── EntryPoint.h         # Defines main(), initialises engine
│   │       └── Log.h/.cpp           # Logging system (spdlog wrapper)
│   ├── vendor/
│   │   └── spdlog/                  # spdlog (git submodule)
│   └── GloomZ.vcxproj
├── Sandbox/                         # Sample client application
│   ├── src/
│   │   └── SandboxApp.cpp           # Minimal GloomZ app example
│   └── Sandbox.vcxproj
├── premake5.lua                     # Premake build configuration
├── GenerateProject.bat              # Generates VS projects on Windows
├── GloomZ.sln                       # Visual Studio solution
└── .gitmodules                      # spdlog submodule reference
```

---

## Prerequisites

| Requirement | Version |
|---|---|
| Operating System | Windows 10 / 11 (x64) |
| Visual Studio | 2019 or later (with **Desktop development with C++** workload) |
| Premake5 | Bundled at `vendor/bin/premake/premake5.exe` |
| Git | Any recent version (for submodule initialisation) |

> **Note:** GloomZ currently targets **Windows only**. Building on other platforms will result in a compile-time error (`#error GloomZ: only windows is supported!`).

---

## Getting Started

### 1. Clone the Repository

Clone the repository along with all git submodules (spdlog):

```bash
git clone --recurse-submodules https://github.com/mouradism/GloomZ.git
```

If you already cloned without submodules, initialise them separately:

```bash
git submodule update --init --recursive
```

### 2. Generate Visual Studio Projects

Run the provided batch script from the repository root:

```batch
GenerateProject.bat
```

This executes:

```batch
vendor\bin\premake\premake5.exe vs2019
```

and produces `GloomZ.sln` together with the `.vcxproj` files for both projects.

### 3. Build the Solution

1. Open `GloomZ.sln` in Visual Studio.
2. Select the desired configuration (**Debug**, **Release**, or **Dist**) and platform (**x64**).
3. Build the solution (**Build → Build Solution** or `Ctrl+Shift+B`).

Build output is placed under:

```
bin/{Config}-windows-x86_64/
├── GloomZ/
│   └── GloomZ.dll          # Engine shared library
└── Sandbox/
    ├── Sandbox.exe          # Client executable
    └── GloomZ.dll           # Automatically copied by post-build step
```

Intermediate object files go to `bin-int/`.

### 4. Run the Sandbox

- Set **Sandbox** as the startup project (right-click → *Set as Startup Project*).
- Press **F5** (Start Debugging) or **Ctrl+F5** (Start Without Debugging).
- Expected console output:

```
[HH:MM:SS] GloomZ:  --- Logging Initialized ---
[HH:MM:SS] GloomZ:  Welcome To GloomZ
[HH:MM:SS] GloomZ:  --- new Sandbox App created // constuctor call ----:
```

---

## Build Configurations

| Configuration | Preprocessor Define | Description |
|---|---|---|
| `Debug` | `GL_DEBUG` | Debug symbols enabled, no optimisation. Use for development. |
| `Release` | `GL_RELEAS` | Optimisations enabled, symbols stripped. Use for testing performance. |
| `Dist` | `GL_DIST` | Maximum optimisation. Use for final distribution builds. |

---

## Usage

### Creating a GloomZ Application

Include only the top-level engine header and inherit from `GloomZ::Application`. Implement the `CreateApplication()` factory function — the engine's `EntryPoint.h` calls it automatically before entering the run loop.

```cpp
#include <GloomZ.h>

class MyGame : public GloomZ::Application {
public:
    MyGame() {
        GL_CLNT_INFO("MyGame initialised!");
    }

    ~MyGame() {}
};

GloomZ::Application* GloomZ::CreateApplication() {
    return new MyGame();
}
```

That is all the boilerplate needed. `main()` is provided by the engine via `EntryPoint.h`.

### Logging API

GloomZ exposes two independent loggers through a set of macros:

#### Core Logger (engine internals)

| Macro | spdlog level |
|---|---|
| `GL_CORE_TRACE(...)` | trace |
| `GL_CORE_INFO(...)` | info |
| `GL_CORE_WARN(...)` | warn |
| `GL_CORE_ERROR(...)` | error |
| `GL_CORE_FATAL(...)` | critical |

#### Client Logger (your application)

| Macro | spdlog level |
|---|---|
| `GL_CLNT_TRACE(...)` | trace |
| `GL_CLNT_INFO(...)` | info |
| `GL_CLNT_WARN(...)` | warn |
| `GL_CLNT_ERROR(...)` | error |
| `GL_CLNT_FATAL(...)` | critical |

All macros accept `printf`-style format strings thanks to spdlog's [fmt](https://github.com/fmtlib/fmt) integration:

```cpp
int health = 42;
GL_CLNT_INFO("Player health: {}", health);
GL_CORE_WARN("Low memory: {} MB remaining", freeMemoryMB);
```

---

## Dependencies

| Library | Version | Purpose |
|---|---|---|
| [spdlog](https://github.com/gabime/spdlog) | submodule (latest) | Fast, header-only C++ logging library |

spdlog is included as a **git submodule** under `GloomZ/vendor/spdlog/`. No additional installation is required beyond running `git submodule update --init --recursive`.

---

## Roadmap

The following features are planned for future development:

- [ ] Window creation and management (Win32 / GLFW)
- [ ] Event system (keyboard, mouse, window events)
- [ ] Rendering abstraction layer (OpenGL / Vulkan / DirectX)
- [ ] Layer stack for application layers and overlays
- [ ] ImGui integration for runtime debugging UI
- [ ] Input polling system
- [ ] Math library integration (GLM)
- [ ] Cross-platform support (Linux / macOS)
- [ ] Entity Component System (ECS)
- [ ] Asset management and resource loading

---

## Contributing

Contributions, issues and feature requests are welcome. To contribute:

1. Fork the repository.
2. Create a feature branch: `git checkout -b feature/my-feature`.
3. Commit your changes: `git commit -m "Add my feature"`.
4. Push to the branch: `git push origin feature/my-feature`.
5. Open a pull request against `main`.
