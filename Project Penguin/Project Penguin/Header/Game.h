#ifndef GAME_HEADER
#define GAME_HEADER

#include <GLEW/glew.h>
#include <GLEW/wglew.h>
#include <GLFW/glfw3.h>
#include <Camera.h>
#include <iostream>

class Game {
private:
    const char TITLE[16] = "Project Penguin";
    GLFWwindow* _window;

    int _width = 800;
    int _height = 600;    
    
    float _lastFrame = 0.0f;

public:
    float deltaTime = 0.0f;

    bool Initialize();

    void processInput(Camera* cam);

    GLFWwindow* getWindowPointer();
    int getHeight();
    int getWidth();

    void calculateDeltaTime();
};

#endif // GAME_HEADER