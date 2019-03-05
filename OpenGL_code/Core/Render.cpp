//
//  Render.cpp
//  lesson_1
//
//  Created by DeppL on 3/1/19.
//  Copyright © 2019 DeppL. All rights reserved.
//

#include "Render.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xPos, double yPos);
//uint LoadImage2GPU(char const* imagePath);
void fixedUpdate(GLFWwindow* window);

const uint SCR_WIDTH = 1600;
const uint SCR_HEIGHT = 1200;

#pragma mark model data

GLfloat vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
    
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
    
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
    
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
//unsigned int indices[] = {
//    0, 1, 2,
//    2, 3, 0
//};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    //    glm::vec3( 2.0f,  5.0f, -15.0f),
    //    glm::vec3(-1.5f, -2.2f, -2.5f),
    //    glm::vec3(-3.8f, -2.0f, -12.3f),
    //    glm::vec3( 2.4f, -0.4f, -3.5f),
    //    glm::vec3(-1.7f,  3.0f, -7.5f),
    //    glm::vec3( 1.3f, -2.0f, -2.5f),
    //    glm::vec3( 1.5f,  2.0f, -2.5f),
    //    glm::vec3( 1.5f,  0.2f, -1.5f),
    //    glm::vec3(-1.3f,  1.0f, -1.5f),
    //    glm::vec3(10.0f, 10.0f, -5.0f)
};

// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3( 0.7f,  0.2f,  2.0f),
    glm::vec3( 2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3( 0.0f,  0.0f, -3.0f)
};

// Instantiate Camera Class
// Camera camera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0));
Camera camera(glm::vec3(5.0f, 15.0f, 10.0f),
              glm::radians(-15.0f),
              glm::radians(200.0f),
              glm::vec3(0, 1.0f, 0)
              );

// Instantiate Light Class
LightDirectional lightD(glm::vec3(0),
                        glm::vec3(glm::radians(-90.0f), glm::radians(45.0f), 0),
                        glm::vec3(1.0f, 1.0f, 1.0f)
                        );
LightPoint lightP(glm::vec3(-3.0f, 12.0f, 3.0f),
                  glm::vec3(0),
                  glm::vec3(2.0f, 0, 0)
                  );
//glm::vec3(4.0f, 13.0f, 2.0f) glm::radians(45.0f)
LightSpot lightS(glm::vec3(-3.0f, 12.0f, 3.0f),
                 glm::vec3(0, glm::radians(135.0f), 0),
                 glm::vec3(0, 2.0f, 0)
                 );

GLFWwindow* window;
Material* material;
Model* model;

struct CoordinateSpace {
    glm::mat4 transMat;
    glm::mat4 modelMat;
    glm::mat4 viewMat;
    glm::mat4 projMat;
};
CoordinateSpace space;


Render::Render() {
    
}

void Render::Initialize() {
    
    const int MAXPATH=250;
    char buffer[MAXPATH];
    getcwd(buffer, MAXPATH);
    printf("The current directory is: %s \n", buffer);
    
    // Init Window
    glfwInit();
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    int versions[] = {
        460, 450, 440, 430, 420, 410, 400,
        330, 320, 310, 300,
        210, 200,
    };
    window = NULL;
    for (int i = 0; i < (sizeof(versions) / sizeof(versions[0])); i++) {
        int majorHint = versions[i] / 100;
        int minorHint = (versions[i] % 100) / 10;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorHint);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorHint);
        window = glfwCreateWindow(SCR_WIDTH * 0.5, SCR_HEIGHT * 0.5, "Test Window", NULL, NULL);
        if (window != NULL) {
            printf("OpenGL_CORE_VERSION = %d \n", majorHint * 100 + minorHint * 10);
            break;
        }
    }
    
    if (window == NULL) {
        glfwTerminate();
        throw "open windows failed \n";
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    
    glewExperimental = true;
    
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw "init glew failed \n";
    }
    
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    //    glEnable(GL_CULL_FACE);
    //    glCullFace(GL_BACK);
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    
    
    // Init Shaders
    Shader* myShader = new Shader("Assets/Shader/vertexSource.vert", "Assets/Shader/fragmentSource.frag");
    // Init Materilas
    material = new Material(myShader);
    material->shininess = 32.0f;
    
    //    Mesh box(vertices);
    model = new Model("Assets/Model/nanosuit/nanosuit.obj");
    
    // Prepare MVP matrics
//    space.transMat = glm::mat4(1.0f);
    space.modelMat = glm::mat4(1.0f);
    space.viewMat = glm::mat4(1.0f);
    space.projMat = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/SCR_HEIGHT, 0.1f, 100.0f);
    
    //    transMat = glm::translate(transMat, glm::vec3(0.5f, -0.5f, 0)); // trans
    //    transMat = glm::scale(transMat, glm::vec3(0.5f, 0.5f, 0.5f)); // scale
    //    transMat = glm::rotate(transMat, (float)glfwGetTime(), glm::vec3(0, 0, 1.0)); // rotation
}

void Render::FixedUpdate() {

    processInput(window);
    
    // Clear screen
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    space.viewMat = camera.GetViewMatrix();
    
    // Set Material -> Shader
    Shader* myShader = material->shader;
    myShader->use();
    
    space.modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(0));
    // Set Material -> Uniforms
    myShader->setMat4("transform", space.transMat);
    myShader->setMat4("modelMat", space.modelMat);
    myShader->setMat4("viewMat", space.viewMat);
    myShader->setMat4("projMat", space.projMat);
    myShader->setVec3("cameraPos", camera.Position);
    
    myShader->setVec3("objColor", glm::vec3(1.0f));
    myShader->setVec3("ambientColor", glm::vec3(0.1f));
    
    float b = sin((float)glfwGetTime()) * SCR_WIDTH;
    myShader->setFloat("time", b);
    
    myShader->setVec3 ("material.ambient",    material->ambient);
    myShader->setInt  ("material.diffuseMap", material->diffuse);
    myShader->setInt  ("material.specularMap",material->specular);
    myShader->setInt  ("material.normalMap",  material->normal);
    myShader->setFloat("material.shininess",  material->shininess);
    
    myShader->setVec3("lightD.pos",          lightD.position);
    myShader->setVec3("lightD.dirToLight",   lightD.direction);
    myShader->setVec3("lightD.color",        lightD.color);
    
    myShader->setVec3 ("lightP.pos",         lightP.position);
    myShader->setVec3 ("lightP.dirToLight",  lightP.direction);
    myShader->setVec3 ("lightP.color",       lightP.color);
    myShader->setFloat("lightP.constant",    lightP.constant);
    myShader->setFloat("lightP.linear",      lightP.linear);
    myShader->setFloat("lightP.quadratic",   lightP.quadratic);
    
    myShader->setVec3 ("lightS.pos",          lightS.position);
    myShader->setVec3 ("lightS.dirToLight",   lightS.direction);
    myShader->setVec3 ("lightS.color",        lightS.color);
    myShader->setFloat("lightS.cosInnerPhy",  lightS.cosInnerPhy);
    myShader->setFloat("lightS.cosOutterPhy", lightS.cosOutterPhy);
    myShader->setFloat("lightS.constant",     lightS.constant);
    myShader->setFloat("lightS.linear",       lightS.linear);
    myShader->setFloat("lightS.quadratic",    lightS.quadratic);
    
    
    // DrawCall
    model->Draw(material->shader);
    
    // Clean up, prepare for next reder loop
    glfwSwapBuffers(window);
    glfwPollEvents();
    camera.UpdateCameraPos();
    
    shouldClose = glfwWindowShouldClose(window);
}

void Render::Destroy() {
    
    // Exit
    //    glDeleteVertexArrays(1, &VAO);
    //    glDeleteBuffers(1, &VAO);
    //    glDeleteBuffers(1, &VBO);
    delete material->shader;
    delete material;
    delete model;
    glfwTerminate();
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

void processInput(GLFWwindow *window) {
    
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.SpeedZ = 1.0f;
    }
    else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.SpeedZ = -1.0f;
    }
    else {
        camera.SpeedZ = 0;
    }
    
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.SpeedX = 1.0f;
    }
    else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.SpeedX = -1.0f;
    }
    else {
        camera.SpeedX = 0;
    }
    
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.SpeedY = 1.0f;
    }
    else if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.SpeedY = -1.0f;
    }
    else {
        camera.SpeedY = 0;
    }
    
//    std::cout << "x = " << camera.Position.x << "; y = " << camera.Position.y << "; z = " << camera.Position.z  << std::endl;
//    std::cout << "pitch = " << camera.Pitch * 180 / M_PI << "; yaw = " <<  camera.Yaw * 180 / M_PI << std::endl;
    
}

float mouse_last_x;
float mouse_last_y;
bool first_mouse = true;

void mouse_callback(GLFWwindow *window, double xPos, double yPos) {
    
    if (first_mouse == true) {
        mouse_last_x = xPos;
        mouse_last_y = yPos;
        first_mouse = false;
    }
    
    float deltaX, deltaY;
    deltaX = mouse_last_x - xPos;
    deltaY = mouse_last_y - yPos;
    mouse_last_x = xPos;
    mouse_last_y = yPos;
    
    camera.ProcessMouseMovement(deltaX, deltaY);
}

