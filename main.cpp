#include <iostream>
#include <string>
#include <filesystem>
#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input.gltf>" << std::endl;
        return 1;
    }

    std::string inputPath = argv[1];
    
    // Check if input file exists
    if (!std::filesystem::exists(inputPath)) {
        std::cerr << "Error: Input file does not exist: " << inputPath << std::endl;
        return 1;
    }

    // Create output path by changing extension to .fbx
    std::filesystem::path path(inputPath);
    std::string outputPath = path.parent_path().string();
    if (!outputPath.empty()) {
        outputPath += "/";
    }
    outputPath += path.stem().string() + ".fbx";

    // Import the GLTF file
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(inputPath, 
        aiProcess_Triangulate | 
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Error loading file: " << importer.GetErrorString() << std::endl;
        return 1;
    }

    // Export to FBX
    Assimp::Exporter exporter;
    aiReturn result = exporter.Export(scene, "fbx", outputPath);

    if (result != AI_SUCCESS) {
        std::cerr << "Error exporting to FBX: " << exporter.GetErrorString() << std::endl;
        return 1;
    }

    std::cout << "Successfully converted " << inputPath << " to " << outputPath << std::endl;
    return 0;
}
