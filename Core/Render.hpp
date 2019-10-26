//
//  Render.hpp
//  lesson_1
//
//  Created by DeppL on 3/1/19.
//  Copyright © 2019 DeppL. All rights reserved.
//


#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Component/Camera.hpp"
#include "../Component/Shader.hpp"
#include "../Component/Material.hpp"
#include "../Component/LightDirectional.hpp"
#include "../Component/LightPoint.hpp"
#include "../Component/LightSpot.hpp"
#include "../Component/Mesh.hpp"
#include "../Component/Model.hpp"
#include "../Component/stb_image.h"

#include <unistd.h>

class Render {
    
public:
    Render();
    bool shouldClose = false;
    
    void Initialize();
    void FixedUpdate();
    void Destroy();
};
