//
//  Camera.cpp
//  lesson_1
//
//  Created by DeppL on 2/9/19.
//  Copyright © 2019 DeppL. All rights reserved.
//

#include "Camera.hpp"
using namespace glm;

Camera::Camera(vec3 position, vec3 target, vec3 worldUp) {
    Position = position;
    WorldUp = worldUp;
    Forward = normalize(target - position);
    Right = normalize(cross(Forward, WorldUp));
    Up = normalize(cross(Right, Forward));
    Pitch = asin(Forward.y);
    Yaw = asin(Forward.x / acos(Pitch));
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp) {
    Position = position;
    Pitch = pitch;
    Yaw = yaw;
    WorldUp = worldUp;
    Forward.x = cos(Pitch) * sin(Yaw);
    Forward.y = sin(Pitch);
    Forward.z = cos(Pitch) * cos(Yaw);
    Right = normalize(cross(Forward, WorldUp));
    Up = normalize(cross(Right, Forward));
}

Camera::~Camera() {
}

mat4 Camera::GetViewMatrix() {
    return lookAt(Position, Position + Forward, WorldUp);
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY, bool constrainPitch) {
    Pitch += deltaY * 0.01;
    Yaw   += deltaX * 0.01;
    
    if (constrainPitch) {
        if (Pitch > glm::radians(89.0f))
            Pitch = glm::radians(89.0f);
        if (Pitch < glm::radians(-89.0f))
            Pitch = glm::radians(-89.0f);
    }
    
    UpdateCameraVectors();
}

void Camera::UpdateCameraPos() {
    Position += Forward * SpeedZ * 0.01f + Right * SpeedX * 0.01f + Up * SpeedY * 0.01f;
}

void Camera::UpdateCameraVectors() {
    Forward.x = cos(Pitch) * sin(Yaw);
    Forward.y = sin(Pitch);
    Forward.z = cos(Pitch) * cos(Yaw);
    Right     = normalize(cross(Forward, WorldUp));
    Up        = normalize(cross(Right, Forward));
}


