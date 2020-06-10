#ifndef GAME_HEADER
#define GAME_HEADER

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <Managers/InputManager.h>
#include <Gameplay/Character.h>

class Game {
private:
    const char TITLE[16] = "Project Penguin";
    const int _width = 1024;
    const int _height = 900;
    const char* glsl_version = "#version 130";

    GLFWwindow* _window; 
    float _lastFrame = 0.0f;
    float _deltaTime = 0.0f;
    bool _initStatus = false;

public:
    static InputManager* InputManager;

    Game();

    bool getInitStatus();
    int getHeight();
    int getWidth();
    GLFWwindow* getWindowPointer();

    void drawUI();
    void cleanUp();

    void processInput(Character* character);
    float calculateDeltaTime();
};

#endif // GAME_HEADER