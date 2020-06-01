#include <Game.h>

/// <summary>
/// Reference to the InputManager, which saves which key is pressed.
/// </summary>
InputManager* Game::InputManager = nullptr;

/// <summary>
/// Initializes the Game by creaing a window and starting GLFW & GLEW
/// </summary>
Game::Game() {
    if (!glfwInit()) {
        _initStatus = false;
        return;
    }

    _window = glfwCreateWindow(_width, _height, TITLE, NULL, NULL);
    if (!_window)
    {
        glfwTerminate();
        _initStatus = false;
        return;
    }
    glfwMakeContextCurrent(_window);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        _initStatus = false;
        return;
    }

    glViewport(0, 0, _width, _height);
    _initStatus = true;
}

/// <summary>
/// Returns true if the initialization in the constructor was successful
/// </summary>
bool Game::getInitStatus() {
    return _initStatus;
}

/// <summary>
/// Returns the height of the game resolution
/// </summary>
int Game::getHeight() {
    return _height;
}

/// <summary>
/// Returns the width of the game resolution
/// </summary>
int Game::getWidth() {
    return _width;
}

/// <summary>
/// Calculates & returns the time between the current and the last frame
/// </summary>
float Game::calculateDeltaTime() {
    float currentFrame = glfwGetTime();
    _deltaTime = currentFrame - _lastFrame;
    _lastFrame = currentFrame;
    return _deltaTime;
}

/// <summary>
/// Returns the pointer to the GLFW window object
/// </summary>
GLFWwindow* Game::getWindowPointer() {
    return _window;
}

/// <summary>
/// Processes Keyboard inputs to either close the window (ESC) or save them in the InputManager,
/// if the player character hasn't reached the end yet.
/// </summary>
/// <param name="character">Reference to the player character</param>
void Game::processInput(Character* character) {
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(_window, true);
    }

    if (!character->hasReachedEnd() && !character->diedInPit()) {
        InputManager->setInputStatus(LEFT, glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS);
        InputManager->setInputStatus(RIGHT, glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS);
        InputManager->setInputStatus(UP, glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS);
    }    
}