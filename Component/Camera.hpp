//
//  Camera.hpp
//  lesson_1
//
//  Created by DeppL on 2/9/19.
//  Copyright © 2019 DeppL. All rights reserved.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup);
    Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp);
    ~Camera();
    
    glm::mat4 GetViewMatrix();
    
    float Pitch;
    float Yaw;
    void ProcessMouseMovement(float deltaX, float deltaY, bool constrainPitch = true);
    
    float SpeedX;
    float SpeedY;
    float SpeedZ;
    void UpdateCameraPos();
    
    glm::vec3 Position;
    glm::vec3 Forward;
    glm::vec3 Right;
    glm::vec3 Up;
    glm::vec3 WorldUp;
    
private:
    void UpdateCameraVectors();
};
