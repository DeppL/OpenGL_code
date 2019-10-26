//
//  Mesh.cpp
//  lesson_1
//
//  Created by DeppL on 2/23/19.
//  Copyright © 2019 DeppL. All rights reserved.
//

#include "Mesh.hpp"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    
    setupMesh();
}


void Mesh::Draw(Shader* shader) {
    
    for (int i = 0; i < textures.size(); i++)
    {
        int slot;
        if (textures[i].type == "texture_diffuse")
        {
            slot = 0;
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
            shader->setInt("material.diffuseMap", slot);
        }
        else if (textures[i].type == "texture_specular")
        {
            slot = 1;
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
            shader->setInt("material.specularMap", slot);
        }
        else if (textures[i].type == "texture_normal")
        {
            slot = 2;
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
            shader->setInt("material.normalMap", slot);
        }
    }
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
//    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
//    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh() {
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Postion));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));
    
    glBindVertexArray(0);
}
