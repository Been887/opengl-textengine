#pragma once

#include <GL/glew.h>
#include "shader.hpp"
#include <vector>

GLfloat textScale = 0.04f, textHeight = 1.4f;


void LoadSquare() {
    GLfloat vertex_data[] = {
        0.0f, 0.0f, 0.0f,     0.0f, 0.0f,//these are texcoords
        1.0f, 0.0f, 0.0f,     1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,     1.0f, 1.0f,
        0.0f, 1.0f, 0.0f,     0.0f, 1.0f
    };
    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*5, nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*5, (void*)(3*sizeof(GLfloat)));
}