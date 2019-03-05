#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

//uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

//out vec4 VertexColor;
// out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
    // VertexColor = vec4(aColor, 1.0);
    TexCoord = aTexCoord;
    Normal = mat3(transpose(inverse(modelMat))) * aNormal;
    FragPos = vec3(modelMat * vec4(aPos, 1.0));
    
//    gl_Position = projMat * viewMat * vec4(FragPos, 1.0f);
    gl_Position = projMat * viewMat * vec4(FragPos, 1.0f);
}
