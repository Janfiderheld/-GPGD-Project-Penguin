#include <GLEW/glew.h>
#include <GLEW/wglew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Game {
private:

    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const char TITLE[16] = "Project Penguin";
    GLFWwindow* window;

public:

    GLFWwindow* GetWindowPointer() {
        return window;
    }

    bool Initialize() {
        // Initialize the GLFW library
        if (!glfwInit()) {
            return false;
        }

        // Create a windowed mode window & its OpenGL context and make the context current
        window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE, NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(window);

        // Initialize the GLEW library
        GLenum err = glewInit();
        if (err != GLEW_OK) {
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
            return false;
        }

        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        return true;
    }
};