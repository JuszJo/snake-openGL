#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Snake {
    public:
        unsigned int VAO, VBO, EBO;

        float width = 30;
        float height = 30;

        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

        glm::vec3 speed = glm::vec3(0.0f, 0.0f, 0.0f);

        float acceleration = width;

        enum STATE {
            UP,
            DOWN,
            LEFT,
            RIGHT,
        };

        STATE currentState = UP;

        Snake() {
            float vertices[] = {
                0.0f, 0.0f, 0.0f,
                width, 0.0f, 0.0f,
                0.0f, height, 0.0f,
                width, height, 0.0f
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
            move();
        }

        void render() {
            glBindVertexArray(VAO);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

    private:
        void genVertexandBuffers(unsigned int* VAO, unsigned int* VBO) {
            glGenVertexArrays(1, VAO);
            glGenBuffers(1, VBO);
        }

        void genElementBuffers(unsigned int* EBO) {
            glGenBuffers(1, EBO);
        }

        void bindVAO(unsigned int VAO) {
            glBindVertexArray(VAO);
        }

        void handleVertexBufferObject(unsigned int VBO, float* vertices, float size) {
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
        }

        void handleElementBuffer(unsigned int EBO, unsigned int* indices, float size) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_DYNAMIC_DRAW);
        }

        void handleVertexArrayObject(unsigned int VAO) {
            
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);
        }

        void cleanupBuffers() {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
};