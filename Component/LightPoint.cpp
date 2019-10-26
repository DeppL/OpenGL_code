//
//  LightPoint.cpp
//  lesson_1
//
//  Created by DeppL on 2/21/19.
//  Copyright © 2019 DeppL. All rights reserved.
//

#include "LightPoint.hpp"

LightPoint::LightPoint(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
        position(_position),
        angles(_angles),
        color(_color)
{
    constant = 1.0f;
    linear = 0.09f;
    quadratic = 0.032f;
}

LightPoint::~LightPoint()
{
    
    
}
