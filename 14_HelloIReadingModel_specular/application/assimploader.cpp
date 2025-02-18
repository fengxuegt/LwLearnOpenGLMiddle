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

Object * AssimpLoader::loadFromFile(const std::string &filepath) {

	//拿出模型路径
	std::size_t lastIndex = filepath.find_last_of("\\/");
	auto rootPath = filepath.substr(0, lastIndex + 1);
	std::cout << rootPath << std::endl;

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_GenNormals); // 生成法线
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return nullptr;
    }
    Object * rootNode = new Object();
	processNode(scene->mRootNode, rootNode, scene, rootPath);
    return rootNode;
}

void AssimpLoader::processNode(aiNode *ainode, Object *parent, const aiScene *scene, const std::string &rootPath) {
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
		auto  mesh = processMesh(ai_mesh, scene, rootPath);
		node->addChild(mesh);
	}

	for (int i = 0; i < ainode->mNumChildren; i++) {
		processNode(ainode->mChildren[i], node, scene, rootPath);
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

Mesh * AssimpLoader::processMesh(aiMesh *mesh, const aiScene* scene, const std::string &rootPath) {
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

		// uv数据 一般关注第0号uv，这是贴图
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

	// 处理材质
	if (mesh->mMaterialIndex >= 0) {
		Texture * diffuse = nullptr;
		aiMaterial *aimaterial = scene->mMaterials[mesh->mMaterialIndex];
		diffuse = processTexture(aimaterial, aiTextureType_DIFFUSE, scene, rootPath);
		if (!diffuse) {
			diffuse = Texture::createTexture("assets/textures/awesomeface.png", 0);
		}
		material->mDiffuse = diffuse;

		Texture * specular = nullptr;
		diffuse = processTexture(aimaterial, aiTextureType_SPECULAR, scene, rootPath);
		if (!specular) {
			specular = Texture::createTexture("assets/textures/awesomeface.png", 0);
		}
		material->mSpecularMask = specular;

	} else {
		material->mDiffuse = new Texture("assets/textures/awesomeface.png", 0);
	}
	return new Mesh(geometry, material);
}

Texture * AssimpLoader::processTexture(aiMaterial *aimaterial, const aiTextureType &type, const aiScene *scene,
	const std::string &rootPath) {
	Texture * texture = nullptr;
	aiString aipath;
	aimaterial->Get(AI_MATKEY_TEXTURE(type, 0), aipath);

	// 判断是否是内嵌图片
	const aiTexture* ai_texture = scene->GetEmbeddedTexture(aipath.C_Str());
	if (ai_texture) {
		// 内嵌
		unsigned char* dataIn = reinterpret_cast<unsigned char*>(ai_texture->pcData);
		auto width = ai_texture->mWidth;
		auto height = ai_texture->mHeight;
		texture = Texture::createTexture(aipath.C_Str(), 0, dataIn, height, width);
	} else {
		// 硬盘上
		std::string fullPath = rootPath + aipath.C_Str();
		std::cout << fullPath << std::endl;
		texture = Texture::createTexture(fullPath, 0);
	}
	return texture;
}
