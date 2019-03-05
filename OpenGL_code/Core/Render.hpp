//
//  Render.hpp
//  lesson_1
//
//  Created by DeppL on 3/1/19.
//  Copyright © 2019 DeppL. All rights reserved.
//

#ifndef Render_hpp
#define Render_hpp


#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "LightDirectional.hpp"
#include "LightPoint.hpp"
#include "LightSpot.hpp"
#include "Mesh.hpp"
#include "Model.hpp"

#include "stb_image.h"

#include <unistd.h>

class Render {
    
public:
    Render();
    bool shouldClose = false;
    
    void Initialize();
    void FixedUpdate();
    void Destroy();
};

#endif /* Render_hpp */
