#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "libs/shader.h"
#include "src/Snake.h"
#include "src/Food.h"

// make sure the viewport matches the new window dimensions; note that width and 
// height will be significantly larger than specified on retina displays.
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow* initWindow(int width, int height) {
    int successInit = glfwInit();

    if(successInit == GLFW_FALSE) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Test", NULL, NULL);

    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window" << std::endl;
        return NULL;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glfwSetCursorPosCallback(window, cursor_callback);

    return window;
}

void initGL(GLFWwindow* window) {
    GLenum err = glewInit();

    if(GLEW_OK != err) {
        printf("Error loading Glew");

        glfwDestroyWindow(window);

        glfwTerminate();
    }
}

int main() {
    int width = 600;
    int height = 600;

    GLFWwindow* window = initWindow(width, height);

    initGL(window);

    Shader myShader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    Snake snake;

    Food food;

    myShader.use();

    glm::mat4 projection(1.0f);
    projection = glm::ortho(0.0f, 600.0f, 0.0f, 600.0f, -1.0f, 1.0f);

    glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glfwSwapInterval(1);

    double FPS = 3.0;

    double FPSInterval = 1000 / FPS;

    double lastFrameTime = glfwGetTime();

    double elapsed = 0.0;

    bool starting = true;

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.3f, 0.4f, 0.6f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        snake.processInput(window);
        
        snake.setSpeed();

        snake.render(myShader);

        food.render(myShader);

        double currentFrameTime = glfwGetTime();
        double delta = currentFrameTime - lastFrameTime;

        elapsed += delta * 1000;

        lastFrameTime = currentFrameTime;

        if(elapsed >= FPSInterval) {
            elapsed = 0;

            snake.update();
        }

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteBuffers(1, &snake.VBO);
    glDeleteVertexArrays(1, &snake.VAO);
    glDeleteProgram(myShader.shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
}