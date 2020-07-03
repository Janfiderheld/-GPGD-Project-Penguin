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
#include <Managers/EnemyManager.h>
#include <Managers/SettingsManager.h>
#include <Managers/ThemeChangingManager.h>
#include <Gameplay/Character.h>
#include <Gameplay/Camera.h>
#include <Technicals/UserInterfaceParameters.h>

class UserInterface {
private:
    static const char* Title;
    const char* glsl_version = "#version 330 core";

    GLFWwindow* _window;
    MenuType _currentMenu = MAIN;
    ImGuiWindowFlags _windowFlags = 0;
	
    Texture _heartFill;
    Texture _heartUnfill;
    Texture _ukFlag;
    Texture _germanFlag;
	
    float _lastFrame = 0.0f;
    float _deltaTime = 0.0f;
    int _language = 0;
	
    bool _initStatus = false;
    bool _firstSettingsFrame = true;
    bool _wrongInput = false;

    void drawMainMenu();
    void drawHighscoreMenu();
    void drawSettingsMenu();
    void drawIngameUI();
    void drawGameOverScreen();
    void drawTutorialMenu();
	
    void closeWindow();	
    std::string formatHighscore(Highscore toFormat);

public:
    static GridFacade* LevelFacade;
    static InputManager* InputManager;
    static HighscoreManager* HighscoreManager;
    static CollectableManager* CollectableManager;
    static EnemyManager* EnemyManager;
    static Character* PlayerChar;
    static SettingsManager* SettingsManager;
    static ThemeChangingManager* ThemeChangingManager;
	
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