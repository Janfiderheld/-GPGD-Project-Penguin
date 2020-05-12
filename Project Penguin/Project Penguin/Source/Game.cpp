#include <Game.h>

// Initializes the Window using the GLFW library
bool Game::Initialize() {
    if (!glfwInit()) {
        return false;
    }

    _window = glfwCreateWindow(_width, _height, TITLE, NULL, NULL);
    if (!_window)
    {
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(_window);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return false;
    }

    glViewport(0, 0, _width, _height);
    return true;
}

// returns the height of the game
int Game::getHeight() {
    return _height;
}

// returns the width of the game
int Game::getWidth() {
    return _width;
}

// calculates the time between the last two frames
void Game::calculateDeltaTime()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - _lastFrame;
    _lastFrame = currentFrame;
}

// returns the pointer to the current window
GLFWwindow* Game::getWindowPointer() {
    return _window;
}

// processes keyboard inputs 
void Game::processInput(Camera* cam)
{
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(_window, true);
    }

    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        cam->calculatePosition(LEFT, deltaTime);
    }

    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        cam->calculatePosition(RIGHT, deltaTime);
    }

    if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS) {
        cam->calculatePosition(UP, deltaTime);
    }

    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        cam->calculatePosition(DOWN, deltaTime);
    }
}