#pragma once
#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <Model/Mesh.h>
#include <Shader.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

//#include <Shader.h>
//#include <vector>
//#include <Model/Mesh.h>
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//#include <stb_image.h>

using namespace  std;

class Model
{
public:
	Model(string const& path, bool gamma = false) : gammaCorrection(gamma)
	{
		loadModel(path);
	}
	void Draw(Shader& shader)
	{
		for (unsigned int i = 0; i < meshes.size(); i++)
			meshes[i].Draw(shader);
	}

private:
	vector < Mesh> meshes;
	string directoryPath;
	bool gammaCorrection;
	void loadModel(string const& path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
			return;
		}

		directoryPath = path.substr(0, path.find_last_of('/'));
		processNode(scene->mRootNode, scene);
	}
	/// <summary>
	/// 递归地处理每个节点，取得网格信息
	/// </summary>
	/// <param name="node"></param>
	/// <param name="scene"></param>
	void processNode(aiNode* node, const aiScene* scene)
	{
		// 处理当前节点的网格
		for (size_t i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}
		// 处理子节点
		for (size_t i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	Mesh processMesh(aiMesh* mesh, const aiScene* scene)
	{
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;

		for (size_t i = 0; i < mesh->mNumVertices; i++)
		{
			// 处理顶点属性（位置、法线、纹理坐标）
			Vertex vertex;
			vertex.Position = glm::vec3(
				mesh->mVertices[i].x,
				mesh->mVertices[i].y,
				mesh->mVertices[i].z);
			vertex.Normal = glm::vec3(
				mesh->mNormals[i].x,
				mesh->mNormals[i].y,
				mesh->mNormals[i].z);
			// 目前只处理第一套纹理坐标
			vertex.TexCoords = glm::vec3(
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y,
				mesh->mTextureCoords[0][i].z);
			vertices.push_back(vertex);
		}
		// 处理索引（所有face的所有index按顺序存储到indices里即可）
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		// 处理材质
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			vector<Texture> diffuseMaps = loadMaterialTextures(material,
				aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			vector<Texture> specularMaps = loadMaterialTextures(material,
				aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		return Mesh(vertices, indices, textures);
	}

	vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, string typeName)
	{
		vector<Texture> textures;
		for (size_t i = 0; i < material->GetTextureCount(type); i++)
		{
			aiString str;
			// material存储的texture路径
			material->GetTexture(type, i, &str);
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), directoryPath);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
		}
		return textures;
	}

	unsigned int TextureFromFile(const char* path, const string& directoryPath, bool gamma = false)
	{
		string filename = string(path);
		filename = directoryPath + '/' + filename;
		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			GLenum format;
			if (nrChannels == 1)format = GL_RED;
			else if (nrChannels == 3)format = GL_RGB;
			else if (nrChannels == 4)format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << path << std::endl;
		}
		stbi_image_free(data);
		return textureID;
	}
};