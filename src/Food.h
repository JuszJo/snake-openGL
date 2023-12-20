#ifndef FOOD_H
#define FOOD_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../libs/shader.h"
#include "Entity.h"

class Food: public Entity {
    public:
        unsigned int VAO, VBO, EBO;

        float width = 30;
        float height = 30;

        glm::vec3 position = glm::vec3(300.0f, 300.0f, 0.0f);

        glm::mat4 model = glm::mat4(1.0f);

        Food() {
            float vertices[] = {
                position.x, position.y, 0.0f, 0.2f, 0.8f, 0.4f,
                position.x + width, position.y, 0.0f, 0.2f, 0.8f, 0.4f,
                position.x, position.y + height, 0.0f, 0.2f, 0.8f, 0.4f,
                position.x + width, position.y + height, 0.0f, 0.2f, 0.8f, 0.4f
            };

            unsigned int indices[] = {
                0, 1, 2,
                1, 2, 3
            };

            float verticesSize = sizeof(vertices);

            float indicesSize = sizeof(indices);

            genVertexandBuffers(&VAO, &VBO);

            genElementBuffers(&EBO);

            bindVAO(VAO);

            handleVertexBufferObject(VBO, vertices, verticesSize);

            handleElementBuffer(EBO, indices, indicesSize);

            handleVertexArrayObject(VAO);

            cleanupBuffers();
        }

        void updatePosition() {
            model = glm::translate(model, glm::vec3(width, height, 0.0f));

            position += glm::vec3(width, height, 0.0f);
        }

        void render(Shader myShader) {
            glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

            glBindVertexArray(VAO);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

    private:
        void handleVertexArrayObject(unsigned int VAO) {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }
};

#endif