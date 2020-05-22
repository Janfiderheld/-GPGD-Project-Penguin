#ifndef GAME_HEADER
#define GAME_HEADER

#include <GLEW/glew.h>
#include <GLEW/wglew.h>
#include <GLFW/glfw3.h>
#include <Character.h>
#include <Camera.h>
#include <iostream>

class Game {
private:
    const char TITLE[16] = "Project Penguin";
    GLFWwindow* _window;

    int _width = 1024;
    int _height = 900;    
    
    float _lastFrame = 0.0f;

public:
    float deltaTime = 0.0f;

    bool Initialize();

    void processInput(Camera* cam, Character* character);

    GLFWwindow* getWindowPointer();
    int getHeight();
    int getWidth();

    float calculateDeltaTime();
};

#endif // GAME_HEADER