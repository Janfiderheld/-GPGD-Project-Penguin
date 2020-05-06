#include <Game.h>

bool Game::Initialize() {
    // Initialize the GLFW library
    if (!glfwInit()) {
        return false;
    }

    // Create a windowed mode window & its OpenGL context and make the context current
    _window = glfwCreateWindow(_width, _height, TITLE, NULL, NULL);
    if (!_window)
    {
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(_window);

    // Initialize the GLEW library
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return false;
    }

    glViewport(0, 0, _width, _height);
    return true;
}

int Game::getHeight() {
    return _height;
}

int Game::getWidth() {
    return _width;
}

void Game::calculateDeltaTime()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - _lastFrame;
    _lastFrame = currentFrame;
}

GLFWwindow* Game::getWindowPointer() {
    return _window;
}

void Game::processInput(Camera* cam)
{
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(_window, true);
    }

    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        cam->processKeyboardInput(LEFT, deltaTime);
    }

    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        cam->processKeyboardInput(RIGHT, deltaTime);
    }

    if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS) {
        cam->processKeyboardInput(UP, deltaTime);
    }

    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        cam->processKeyboardInput(DOWN, deltaTime);
    }
}