cmake_minimum_required(VERSION 3.15)
project(gltf2fbx VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build static executable
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")

# Assimp build options - disable everything we don't need
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)

# Enable only GLTF importer and FBX exporter
# Note: FBX importer must be enabled for FBX exporter to work (shared util code)
set(ASSIMP_BUILD_GLTF_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_FBX_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_FBX_EXPORTER ON CACHE BOOL "" FORCE)

# Static build
set(ASSIMP_BUILD_STATIC_LIB ON CACHE BOOL "" FORCE)

# Disable unnecessary features
set(ASSIMP_NO_EXPORT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)

# Add assimp
add_subdirectory(vendor/assimp)

# Create the executable
add_executable(gltf2fbx main.cpp)

# Link against assimp
target_link_libraries(gltf2fbx PRIVATE assimp)

# Include assimp headers
target_include_directories(gltf2fbx PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/assimp/include
    ${CMAKE_CURRENT_BINARY_DIR}/vendor/assimp/include
)

# Strip the binary in release mode to reduce size
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(UNIX)
        add_custom_command(TARGET gltf2fbx POST_BUILD
            COMMAND ${CMAKE_STRIP} $<TARGET_FILE:gltf2fbx>
            COMMENT "Stripping binary..."
        )
    endif()
endif()
