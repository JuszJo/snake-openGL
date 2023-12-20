#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Entity.h"

class Food: public Entity {
    public:
        unsigned int VAO, VBO, EBO;
        
        float width = 30;
        float height = 30;

        glm::vec3 position = glm::vec3(300.0f, 300.0f, 0.0f);

        Food() {
            float vertices[] = {
                position.x, position.y, 0.0f,
                position.x + width, position.y, 0.0f,
                position.x, position.y + height, 0.0f,
                position.x + width, position.y + height, 0.0f
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

        void render() {
            glBindVertexArray(VAO);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
};