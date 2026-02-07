#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <stb/stb_image.h>

#include <vector>
#include <iostream>
#include <string.h>

GLuint VAO, VBO, EBO, shader, UniformModel, UniformColour, UniformTheTexture;
glm::vec4 colour(1.0f);
glm::mat4 model(1.0f);

const char* vshader = R"(
#version 330 core

layout(location=0) in vec3 aPos;
layout(location=1) in vec2 aTexCoord;
uniform mat4 model;

out vec2 texCoord;

void main() {
    gl_Position = model * vec4(aPos, 1.0);
    texCoord = aTexCoord;
})";
const char* fshader = R"(
#version 330 core

uniform vec4 colourIn;
uniform sampler2D theTexture;

in vec2 texCoord;
out vec4 colour;

void main() {
    if(colourIn.w == 0.0f) {
        colour = texture(theTexture, texCoord);
    } else {
        colour = colourIn;
    }
})";

void addshader(GLuint theProgram, const char* shadercode, GLenum shadertype) {
    GLuint theShader = glCreateShader(shadertype);

    const GLchar* theCode[1] ={0};
    theCode[0] = shadercode;

    int codelength[1] = {0};
    codelength[0] = strlen(shadercode);

    glShaderSource(theShader, 1, theCode, codelength);

    GLchar eLog[1024] = {0};
    int result = 0;

    glCompileShader(theShader);

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if(!result) {
        glGetShaderInfoLog(theShader, 1024, nullptr, eLog);
        std::cout << eLog << "\n\n";
        return;
    }

    glAttachShader(theProgram, theShader);
}

void CompileShaders() {
    shader = glCreateProgram();
    if(!shader) {
        std::cout << "shader error - failed to create shader!\n";
        return;
    }

    addshader(shader, vshader, GL_VERTEX_SHADER);
    addshader(shader, fshader, GL_FRAGMENT_SHADER);

    GLchar eLog[1024] = {0};
    int result = 0;

    glLinkProgram(shader);

    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if(!result) {
        glGetProgramInfoLog(shader, 1024, nullptr, eLog);
        std::cout << eLog << "\n\n";
    }
    
    glValidateProgram(shader);

    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if(!result) {
        glGetProgramInfoLog(shader, 1024, nullptr, eLog);
        std::cout << eLog << "\n\n";
    }

    UniformModel = glGetUniformLocation(shader, "model");
    UniformColour = glGetUniformLocation(shader, "colourIn");
    UniformTheTexture = glGetUniformLocation(shader, "theTexture");
}

struct textStruct {
    int width, height, colorch;
    unsigned char* bytes;
    GLuint texID;
    textStruct() {
        width = 0;
        height = 0;
        colorch = 0;
    }
};
static std::vector<textStruct> textures;

void setupTextures() {
    stbi_set_flip_vertically_on_load(true);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for(int i = 0; i<26; i++) {//                                             REMEMBER TO CHANGE THE FOR LOOP BACK FOR WHEN YOU HAVE CHAR TEXTURES!!!
        std::string filename = "letters/"+std::to_string(i)+".png";
        const char* c_filename = filename.c_str();

        textures.push_back(textStruct());

        glGenTextures(1, &textures.at(i).texID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures.at(i).texID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        textures.at(i).bytes = stbi_load(c_filename, &textures.at(i).width, &textures.at(i).height, &textures.at(i).colorch, 0);

        if(!textures.at(i).bytes) {
            std::cout << "error loading texture into 'bytes'!\n\n";
        }

        GLenum format = (textures.at(i).colorch == 4) ? GL_RGBA : GL_RGB;

        glTexImage2D(GL_TEXTURE_2D, 0, format, textures.at(i).width, textures.at(i).height, 0, format, GL_UNSIGNED_BYTE, textures.at(i).bytes);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(textures.at(i).bytes);
    }
}