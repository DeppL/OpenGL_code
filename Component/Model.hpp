//
//  Model.hpp
//  lesson_1
//
//  Created by DeppL on 2/23/19.
//  Copyright © 2019 DeppL. All rights reserved.
//

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "Mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model{
public:
    Model(string path);
    
    vector<Mesh> meshes;
    string directory;
    vector<Texture> textures_loaded;
    void Draw(Shader* shader);
    
private:
    
    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(const aiMaterial* mat, aiTextureType type, string typeName);
    unsigned int TextureFromFile(const char* path, const string &dictonary);
};

