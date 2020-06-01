#ifndef GAME_HEADER
#define GAME_HEADER

#include <GLEW/glew.h>
#include <GLEW/wglew.h>
#include <GLFW/glfw3.h>
#include <InputManager.h>
#include <Character.h>
#include <iostream>

class Game {
private:
    const char TITLE[16] = "Project Penguin";
    const int _width = 1024;
    const int _height = 900;

    GLFWwindow* _window; 
    float _lastFrame = 0.0f;
    float _deltaTime = 0.0f;
    bool _initStatus = false;

public:
    static InputManager* InputManager;

    Game();

    bool getInitStatus();
    GLFWwindow* getWindowPointer();
    int getHeight();
    int getWidth();

    void processInput(Character* character);
    float calculateDeltaTime();
};

#endif // GAME_HEADER