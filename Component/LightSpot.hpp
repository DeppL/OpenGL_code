//
//  LightSpot.hpp
//  lesson_1
//
//  Created by DeppL on 2/21/19.
//  Copyright © 2019 DeppL. All rights reserved.
//

#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

class LightSpot
{
public:
    
    LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f));
    ~LightSpot();
    
    glm::vec3 position;
    glm::vec3 angles;
    glm::vec3 direction = glm::vec3(0, 0, 1.0f);
    glm::vec3 color;
    
    void UpdateDirection();
    
    float cosInnerPhy = 0.95f;
    float cosOutterPhy = 0.9f;
    
    float constant;
    float linear;
    float quadratic;
    
};
