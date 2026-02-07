#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb/stb_image.h>

#include "window.hpp"
#include "graphics.hpp"
#include "shader.hpp"

glm::vec2 letterPos(0.0f);
int letter = 0;

int main() {
    WindowSetup();
    CompileShaders();
    setupTextures();
    LoadSquare();

    bool rightdown = false;

    glfwSetKeyCallback(window, key_callback);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && !rightdown) {
            letter++;
            rightdown = true;
        }  
        if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE) {
            rightdown = false;
        }        


        glClearColor(0.2, 0.2, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(VAO);
        
        letterPos = glm::vec2(-1*(1.0f/textScale), 1.0f/(textHeight*textScale));
        for(int i = 0; i<mytext.length(); i++) {
            //letterPos.x++;
            //if(letters.at(i)==" ") continue;
            if(mytext.at(i) == ' ') {
                letterPos.x++;
                continue;
            }
            if(mytext.at(i) ==  '\n') {
                letterPos.y--;
                letterPos.x = -1*(1.0f/textScale);
                continue;
            }

            colour = glm::vec4(1.0, 0.2, 0.2, 0.0);
            glUniform4fv(UniformColour, 1, glm::value_ptr(colour));
            glBindTexture(GL_TEXTURE_2D, textures.at(mytext.at(i)-65).texID);
            glUniform1i(UniformTheTexture, 0);

            model = glm::mat4(1.0f);
            model = glm::scale(model, glm::vec3(textScale, textScale*1.3, textScale));
            model = glm::translate(model, glm::vec3(letterPos.x, letterPos.y, 0.0f));
            glUniformMatrix4fv(UniformModel, 1, GL_FALSE, glm::value_ptr(model));
            
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            letterPos.x++;
        }

        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(window);
    }
    std::cout << "bye\n";
    return 0;
}