#ifndef UI_HEADER
#define UI_HEADER

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <Managers/InputManager.h>
#include <Gameplay/Character.h>
#include <MenuType.h>
#include <Technicals/UserInterfaceParameters.h>
#include <Managers/HighscoreManager.h>

class UserInterface {
private:
    const char TITLE[16] = "Project Penguin";
    const int _width = 1024;
    const int _height = 900;
    const char* glsl_version = "#version 330";

    GLFWwindow* _window;
    MenuType _currentMenu = MAIN;
    ImGuiWindowFlags _windowFlags = 0;
	
    float _lastFrame = 0.0f;
    float _deltaTime = 0.0f;
    bool _initStatus = false;

    void drawMainMenu();
    void drawHighscoreMenu();
    void drawSettingsMenu();
    void drawIngameUI();

    std::string formatHighscore(Highscore toFormat);

public:
    static InputManager* InputManager;
    static HighscoreManager* HighscoreManager;

    UserInterface();

    bool getInitStatus();
    int getHeight();
    int getWidth();
    GLFWwindow* getWindowPointer();

    void drawUI();
    void cleanUp();

    void processInput(Character* character);
    float calculateDeltaTime();
    bool hasGameStarted();
};

#endif // UI_HEADER