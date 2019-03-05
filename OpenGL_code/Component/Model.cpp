//
//  Model.cpp
//  lesson_1
//
//  Created by DeppL on 2/23/19.
//  Copyright © 2019 DeppL. All rights reserved.
//

#include "Model.hpp"
#include "stb_image.h"


Model::Model(string path) {
    loadModel(path);
}

void Model::Draw(Shader* shader) {
    
    for (int i = 0; i < meshes.size(); i++) {
        meshes[i].Draw(shader);
    }
}

void Model::loadModel(string path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "Assimp error" << std::endl;
        return;
    }
    
    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
    
    std::cout << node->mName.data << std::endl;
    
    for (int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* curMesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(curMesh, scene));
    }
    
    for (int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}



Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
    
    std::vector<Vertex> tempVertices;
    std::vector<unsigned int> tempIndices;
    std::vector<Texture> tempTextures;
    
    Vertex tempVertex;
    for (int i = 0; i < mesh->mNumVertices; i++) {
        
        tempVertex.Postion.x = mesh->mVertices[i].x;
        tempVertex.Postion.y = mesh->mVertices[i].y;
        tempVertex.Postion.z = mesh->mVertices[i].z;
        
        tempVertex.Normal.x = mesh->mNormals[i].x;
        tempVertex.Normal.y = mesh->mNormals[i].y;
        tempVertex.Normal.z = mesh->mNormals[i].z;
        
        if (mesh->mTextureCoords[0]) {
            tempVertex.TexCoord.x = mesh->mTextureCoords[0][i].x;
            tempVertex.TexCoord.y = mesh->mTextureCoords[0][i].y;
        }
        else {
            tempVertex.TexCoord = glm::vec2(0);
        }
        
        tempVertices.push_back(tempVertex);
    }
    
    for (int i = 0; i < mesh->mNumFaces; i++) {
        for (int j = 0; j < mesh->mFaces[i].mNumIndices; j ++) {
            tempIndices.push_back(mesh->mFaces[i].mIndices[j]);
        }
    }
    
    const aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
    vector<Texture> diffuseMaps = loadMaterialTextures(mat, aiTextureType_DIFFUSE, "texture_diffuse");
    tempTextures.insert(tempTextures.end(), diffuseMaps.begin(), diffuseMaps.end());
    
    vector<Texture> specularMaps = loadMaterialTextures(mat, aiTextureType_SPECULAR, "texture_specular");
    tempTextures.insert(tempTextures.end(), specularMaps.begin(), specularMaps.end());
    
    vector<Texture> normalMaps = loadMaterialTextures(mat, aiTextureType_HEIGHT, "texture_normal");
    tempTextures.insert(tempTextures.end(), normalMaps.begin(), normalMaps.end());
    
    vector<Texture> heightMaps = loadMaterialTextures(mat, aiTextureType_AMBIENT, "texture_height");
    tempTextures.insert(tempTextures.end(), heightMaps.begin(), heightMaps.end());
    
    return Mesh(tempVertices, tempIndices, tempTextures);
}

vector<Texture> Model::loadMaterialTextures(const aiMaterial* mat, aiTextureType type, string typeName) {
    vector<Texture> textures;
    for (int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        
        bool skip = false;
        for (int j = 0; j < textures_loaded.size(); j++) {
            if (strcmp(str.C_Str(), textures_loaded[j].path.data()) == 0) {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if (skip) continue;
        Texture texture;
        texture.id = TextureFromFile(str.C_Str(), this->directory);
        texture.type = typeName;
        texture.path = str.C_Str();
        textures.push_back(texture);
        textures_loaded.push_back(texture);
    }
    return textures;
}

unsigned int Model::TextureFromFile(const char* path, const string &dictonary) {
    
    string fileName = string(path);
    fileName = dictonary + '/' + fileName;
    
    unsigned int textureID;
    glGenTextures(1, &textureID);
    
    int width, height, numChannel;
    unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &numChannel, 0);
    if (data) {
        GLenum format;
        
        if (numChannel == 1) format = GL_RED;
        else if (numChannel == 3) format = GL_RGB;
        else if (numChannel == 4) format = GL_RGBA;
        else throw "format error";
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        stbi_image_free(data);
    }
    else printf("Load Image Failed\n");
    
    return textureID;
}

