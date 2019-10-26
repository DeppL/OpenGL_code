//
//  Mesh.hpp
//  lesson_1
//
//  Created by DeppL on 2/23/19.
//  Copyright © 2019 DeppL. All rights reserved.
//

#pragma once

#include <string>
#include <vector>

#include "Shader.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <GL/glew.h>

using namespace std;

struct Vertex {
    glm::vec3 Postion;
    glm::vec3 Normal;
    glm::vec2 TexCoord;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh{

public:
    // mesh data
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    
//    Mesh(float vertices[]);
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    
    void Draw(Shader* shader);
    
    unsigned int VAO;
private:
    
    unsigned int VBO, EBO;
    void setupMesh();
    
};

