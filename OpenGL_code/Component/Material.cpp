//
//  Material.cpp
//  lesson_1
//
//  Created by DeppL on 2/12/19.
//  Copyright © 2019 DeppL. All rights reserved.
//

#include "Material.hpp"

Material::Material(Shader *_shader,
                   glm::vec3 _ambient,
                   unsigned int _diffuse,
                   unsigned int _specular,
                   unsigned int _emission,
                   unsigned int _normal,
                   float _shininess) : shader(_shader), ambient(_ambient), diffuse(_diffuse), specular(_specular), emission(_emission), normal(_normal), shininess(_shininess)
{
    
}

Material::~Material()
{
}
