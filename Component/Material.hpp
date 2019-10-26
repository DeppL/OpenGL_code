//
//  Material.hpp
//  lesson_1
//
//  Created by DeppL on 2/12/19.
//  Copyright © 2019 DeppL. All rights reserved.
//

#pragma once

#include "Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Material
{
public:
    Material(Shader *_shader,
             glm::vec3 _ambient = glm::vec3(1.0f),
             unsigned int _diffuse = 0,
             unsigned int _specular = 0,
             unsigned int _emission = 0,
             unsigned int _normal = 0,
             float _shininess = 1.0f);
    ~Material();
    
    Shader *shader;
    glm::vec3 ambient;
    unsigned int diffuse;
    unsigned int specular;
    unsigned int emission;
    unsigned int normal;
    float shininess = 1.0f;
};
