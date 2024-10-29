//
// Created by 心心旺旺 on 2024/10/28.
//

#include "assimploader.h"

#include <iostream>
#include <ostream>

#include "../glframework/util/util.h"
#include "../glframework/mesh.h"
#include "../glframework/material/phonematerial.h"
#include "../glframework/material/material.h"

AssimpLoader::AssimpLoader() {
}

AssimpLoader::~AssimpLoader() {
}

Object * AssimpLoader::loadFromFile(const char *filepath) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_GenNormals); // 生成法线
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return nullptr;
    }
    Object * rootNode = new Object();
	processNode(scene->mRootNode, rootNode, scene);
    return rootNode;
}

void AssimpLoader::processNode(aiNode *ainode, Object *parent, const aiScene *scene) {
    Object * node = new Object();
	parent->addChild(node);

    glm::mat4 localMatrix = getMat4(ainode->mTransformation);
    // 旋转、平移、缩放
    glm::vec3 position, rotation, scale;
    Util::decompose(localMatrix, position, rotation, scale);
	node->setPosition(position);
	node->setScale(scale);
	node->setAngleX(rotation.x);
	node->setAngleY(rotation.y);
	node->setAngleZ(rotation.z);

	// 检查是否有mesh，并且解析
	for (int i =0; i < ainode->mNumMeshes; i++) {
		int meshID = ainode->mMeshes[i];
		aiMesh *ai_mesh = scene->mMeshes[meshID];
		auto  mesh = processMesh(ai_mesh);
		node->addChild(mesh);
	}

	for (int i = 0; i < ainode->mNumChildren; i++) {
		processNode(ainode->mChildren[i], node, scene);
	}
}

glm::mat4 AssimpLoader::getMat4(aiMatrix4x4 matrix) {
    	glm::mat4 to(
		matrix.a1, matrix.a2, matrix.a3, matrix.a4,
		matrix.b1, matrix.b2, matrix.b3, matrix.b4,
		matrix.c1, matrix.c2, matrix.c3, matrix.c4,
		matrix.d1, matrix.d2, matrix.d3, matrix.d4
	);

	return to;
}

Mesh * AssimpLoader::processMesh(aiMesh *mesh, const aiScene* scene) {
	std::vector<float> vertices; // 位置
	std::vector<unsigned int> indices; // 索引
	std::vector<float> normals; // 法线
	std::vector<float> texCoords; // uvs

	for (int i = 0; i < mesh->mNumVertices; i++) {
		// 位置数据
		vertices.push_back(mesh->mVertices[i].x);
		vertices.push_back(mesh->mVertices[i].y);
		vertices.push_back(mesh->mVertices[i].z);

		// 法线数据
		normals.push_back(mesh->mNormals[i].x);
		normals.push_back(mesh->mNormals[i].y);
		normals.push_back(mesh->mNormals[i].z);

		// uv数据
		if (mesh->mTextureCoords[0]) {
			texCoords.push_back(mesh->mTextureCoords[0][i].x);
			texCoords.push_back(mesh->mTextureCoords[0][i].y);
		} else {
			texCoords.push_back(0.0f);
			texCoords.push_back(0.0f);
		}
	}
	// 解析mesh中的索引值
	for (int j = 0; j < mesh->mNumFaces; j++) {
		auto face = mesh->mFaces[j];
		for (int k = 0; k < face.mNumIndices; k++) {
			indices.push_back(face.mIndices[k]);
		}
	}
	auto geometry = new Geometry(vertices, normals, texCoords, indices);
	auto material = new Phonematerial();
	material->mDiffuse = new Texture("assets/textures/awesomeface.png", 0);

	// 处理材质
	if (mesh->mMaterialIndex) {
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		aiString aipath;
		material->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), aipath);

	}

	return new Mesh(geometry, material);
}
