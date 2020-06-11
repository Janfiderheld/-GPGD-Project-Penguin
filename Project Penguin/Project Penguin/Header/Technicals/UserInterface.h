#ifndef UI_HEADER
#define UI_HEADER

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <MenuType.h>
#include <Managers/InputManager.h>
#include <Managers/HighscoreManager.h>
#include <Managers/CollectableManager.h>
#include <Gameplay/Character.h>
#include <Gameplay/Camera.h>
#include <Technicals/UserInterfaceParameters.h>

class UserInterface {
private:
    const char TITLE[16] = "Project Penguin";
    const char* glsl_version = "#version 330";

    GLFWwindow* _window;
    MenuType _currentMenu = MAIN;
    ImGuiWindowFlags _windowFlags = 0;
    Texture _heartFill;
    Texture _heartUnfill;
	
    float _lastFrame = 0.0f;
    float _deltaTime = 0.0f;
    bool _initStatus = false;

    void drawMainMenu();
    void drawHighscoreMenu();
    void drawSettingsMenu();
    void drawIngameUI();
    void drawGameOverScreen();
	
    void closeWindow();	
    std::string formatHighscore(Highscore toFormat);

public:
    static int Width;
    static int Height;

    static GridFacade* LevelGrid;
    static InputManager* InputManager;
    static HighscoreManager* HighscoreManager;
    static CollectableManager* CollectableManager;
    static Character* PlayerCharacter;

    UserInterface();

    bool getInitStatus();
    GLFWwindow* getWindowPointer();

    void drawUI();
    void cleanUp();

    void processInput(Camera* cam);
    float calculateDeltaTime();
    bool hasGameStarted();
};

#endif // UI_HEADER