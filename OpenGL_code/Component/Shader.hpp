//
//  Shader.hpp
//  lesson_1
//
//  Created by DeppL on 1/27/19.
//  Copyright © 2019 DeppL. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <string>
#include <glm/glm.hpp>

class Shader {
    
public:
    
    unsigned int ID; // Shader Program ID;
    
    Shader(const char* vertexPath, const char* fragmentPath);
    
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    
    
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    // ----------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    // ----------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w);
    // ----------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    // ----------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    // ----------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
//    ~Shader();
    
private:
    void checkCompileErrors(unsigned int ID, std::string type);
};

#endif /* Shader_hpp */
