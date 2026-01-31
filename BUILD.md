# Building gltf2fbx

## Prerequisites

- CMake 3.15 or higher
- C++ compiler with C++17 support (GCC 7+, Clang 5+, MSVC 2017+)
- Git (to clone the repository)

## Build Instructions

### Linux/macOS

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
```

The resulting binary will be at `build/gltf2fbx`.

### Windows

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
```

The resulting binary will be at `build/Release/gltf2fbx.exe`.

## Usage

```bash
./gltf2fbx <input.gltf>
```

The tool will create an FBX file with the same name as the input file (e.g., `model.gltf` → `model.fbx`).

## Example

```bash
./gltf2fbx my_model.gltf
# Creates: my_model.fbx
```

## Technical Details

- The project uses Assimp 5.4.3 for format conversion
- Only GLTF/GLB import and FBX export are enabled to minimize binary size
- The executable is statically linked with Assimp and the C++ standard library
- Final binary size is approximately 3.6MB on Linux
