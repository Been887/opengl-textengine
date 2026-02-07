#pragma once

#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <iostream>

const unsigned int WINDOW_WIDTH = 1000, WINDOW_HEIGHT = 1000;
GLFWwindow* window;
int WINDOW_BUFFERWIDTH, WINDOW_BUFFERHEIGHT;
std::string mytext = "";

bool keysdown[26];

bool WindowSetup() {
    if(!glfwInit()) {
        std::cout << "error in windowsetup - GLFW failed to initialise!\n";
        return false;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Ben's text window", nullptr, nullptr);
    if(!window) {
        std::cout << "error in windowsetup - failed to create window!\n";
        return false;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK) {
        std::cout << "error in windowsetup - GLEW failed to initialise!\n";
        return false;
    }

    glfwGetFramebufferSize(window, &WINDOW_BUFFERWIDTH, &WINDOW_BUFFERHEIGHT);
    glViewport(0, 0, WINDOW_BUFFERWIDTH, WINDOW_BUFFERHEIGHT);

    return true;
}

bool keys[1024]; // GLFW defines key codes up to ~350, so 1024 is safe

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            if(!keys[key]) {
                if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z) {
                    char c = 'A' + (key - GLFW_KEY_A); // gives 'A'..'Z'
                    mytext+=c;
                }
                if (key == GLFW_KEY_SPACE) {
                    char c = ' ';
                    mytext+=c;
                }
                if (key == GLFW_KEY_BACKSPACE) {
                    mytext.pop_back();
                }
                if(key == GLFW_KEY_ENTER) {
                    mytext+="\n";
                }
            }
            keys[key] = true;
        } else if (action == GLFW_RELEASE) {
            keys[key] = false;
        }
    }
}