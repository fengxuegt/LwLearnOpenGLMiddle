#pragma once
#include "../glframework/core.h"
#include "../glframework/object.h"
#include "../glframework/texture.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class Mesh;

class AssimpLoader {
public:
    AssimpLoader();
    ~AssimpLoader();

    static Object* loadFromFile(const std::string &filepath);

private:
    static void processNode(aiNode* node, Object* parent, const aiScene* scene, const std::string &rootPath);
    static glm::mat4 getMat4(aiMatrix4x4 matrix);
    static Mesh* processMesh(aiMesh* mesh, const aiScene* scene, const std::string &rootPath);
    static Texture* processTexture(aiMaterial* ai_material, const aiTextureType &type, const aiScene* scene, const std::string &rootPath);

};
