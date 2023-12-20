#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../libs/shader.h"
#include "Entity.h"

class Snake: public Entity {
    public:
        unsigned int VAO, VBO, EBO;

        float width = 30;
        float height = 30;

        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

        glm::vec3 speed = glm::vec3(0.0f, 0.0f, 0.0f);

        float acceleration = width;

        glm::mat4 model = glm::mat4(1.0f);

        enum STATE {
            UP,
            DOWN,
            LEFT,
            RIGHT,
        };

        STATE currentState = UP;

        Snake() {
            float vertices[] = {
                0.0f, 0.0f, 0.0f, 0.6f, 0.3f, 0.3f,
                width, 0.0f, 0.0f, 0.6f, 0.3f, 0.3f,
                0.0f, height, 0.0f, 0.6f, 0.3f, 0.3f,
                width, height, 0.0f, 0.6f, 0.3f, 0.3f
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

        void processInput(GLFWwindow* window) {
            if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, true);
            }
            if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                if(currentState != UP) currentState = UP;
            }
            if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                if(currentState != DOWN) currentState = DOWN;
            }
            if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                if(currentState != LEFT) currentState = LEFT;
            }
            if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                if(currentState != RIGHT) currentState = RIGHT;
            }
        }

        void setSpeed() {
            switch (currentState) {
                case UP:
                    speed = glm::vec3(0.0f, acceleration, 0.0f);

                    break;

                case DOWN:
                    speed = glm::vec3(0.0f, -acceleration, 0.0f);
                    
                    break;

                case LEFT:
                    speed = glm::vec3(-acceleration, 0.0f, 0.0f);
                    
                    break;

                case RIGHT:
                    speed = glm::vec3(acceleration, 0.0f, 0.0f);
                    
                    break;
            
            default:
                break;
            }
        }

        void move() {
            position += speed;
        }

        void update() {
            model = glm::translate(model, speed);

            move();
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