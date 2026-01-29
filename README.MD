gltf2fbx
========

This project uses assimp to load and convert a (q3bsp-created) gltf model into fbx, and save it to a file named the exact same as the input, just *.fbx. The goal is to be fast, with as little overhead as possible, and few options.

This replaces an older blender python script that took several seconds to run, because of blender initialization and slow handling of gltf.