//
//  LightDirectional.cpp
//  lesson_1
//
//  Created by DeppL on 2/13/19.
//  Copyright © 2019 DeppL. All rights reserved.
//

#include "LightDirectional.hpp"
LightDirectional::LightDirectional(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
        position(_position),
        angles(_angles),
        color(_color)
{
    UpdateDirection();
}

LightDirectional::~LightDirectional()
{
}


void LightDirectional::UpdateDirection()
{
    direction = glm::vec3(0, 0, 1.0f);
    direction = glm::rotateZ(direction, angles.z);
    direction = glm::rotateX(direction, angles.x);
    direction = glm::rotateY(direction, angles.y);
    direction = -1.0f * direction;
};
