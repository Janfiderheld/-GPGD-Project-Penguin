#include <Technicals/UserInterface.h>

/// <summary>
/// Width of the application
/// </summary>
int UserInterface::Width = 1024;

/// <summary>
/// Height of the application
/// </summary>
int UserInterface::Height = 900;

/// <summary>
/// Reference to the InputManager, which saves which key is pressed.
/// </summary>
InputManager* UserInterface::InputManager = nullptr;

/// <summary>
/// Reference to the HighscoreManager, which is for everything related to highscores
/// </summary>
HighscoreManager* UserInterface::HighscoreManager = nullptr;

/// <summary>
/// Reference to the main character, which is controlled by the player
/// </summary>
Character* UserInterface::PlayerCharacter = nullptr;

/// <summary>
/// Draws the Main Menu
/// </summary>
void UserInterface::drawMainMenu() {
    float differenceInY = Height / 20.0;
	
    ImGui::Begin("Project Penguin - Main Menu", nullptr, _windowFlags | ImGuiWindowFlags_NoBackground);
    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::ScreenMiddleInX, ImGui::GetCursorPosY() + differenceInY));
    if (ImGui::Button("New Game", UserInterfaceParameters::MainMenuButtonSize)) {
        _currentMenu = GAME;
    }

    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::ScreenMiddleInX, ImGui::GetCursorPosY() + differenceInY));
	if(ImGui::Button("Highscores", UserInterfaceParameters::MainMenuButtonSize)) {
        _currentMenu = HIGHSCORE;
	}

    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::ScreenMiddleInX, ImGui::GetCursorPosY() + differenceInY));
	if(ImGui::Button("Settings", UserInterfaceParameters::MainMenuButtonSize))	{
        _currentMenu = SETTINGS;
	}

    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::ScreenMiddleInX, ImGui::GetCursorPosY() + differenceInY));
	if(ImGui::Button("Quit", UserInterfaceParameters::MainMenuButtonSize)) {
        closeWindow();
	}
    ImGui::End();
}

/// <summary>
/// Draws the Highscore-Menu
/// </summary>
void UserInterface::drawHighscoreMenu() {
    ImGui::Begin("Project Penguin - Highscores", nullptr, _windowFlags | ImGuiWindowFlags_NoBackground);
    std::vector<Highscore> _highscores = HighscoreManager->getHighscores();
	for(int i = 0; i < _highscores.size(); i++) {
        ImGui::Text(formatHighscore(_highscores.at(i)).c_str());
	}
    if (ImGui::Button("Back to Main Menu", UserInterfaceParameters::MainMenuButtonSize)) {
        _currentMenu = MAIN;
    }
    ImGui::End();
}

/// <summary>
/// Draws the Settings-Menu
/// </summary>
void UserInterface::drawSettingsMenu() {
    ImGui::Begin("Project Penguin - Settings", nullptr, _windowFlags | ImGuiWindowFlags_NoBackground);
    if (ImGui::Button("Back to Main Menu", UserInterfaceParameters::MainMenuButtonSize)) {
        _currentMenu = MAIN;
    }
    ImGui::End();
}

/// <summary>
/// Draws the UI during the Game
/// </summary>
void UserInterface::drawIngameUI() {
    ImGui::Begin("Project Penguin - Game", nullptr, _windowFlags);
    std::string curr = "Current Score: ";
	curr.append(HighscoreManager->getScoreAsString());
    ImGui::Text(curr.c_str());
    ImGui::SameLine();
    ImGui::Text("Health:");
    for(int i = 0; i < PlayerCharacter->getCurrentHealth(); i++) {
        ImGui::SameLine();
        ImGui::Image((ImTextureID)(intptr_t)_heartFill.TextureId, UserInterfaceParameters::HeartTextureSize,
            UserInterfaceParameters::TextureCoordMin, UserInterfaceParameters::TextureCoordMax);
    }
	for(int i = 0; i < PlayerCharacter->getMaxHealth() - PlayerCharacter->getCurrentHealth(); i++) {
        ImGui::SameLine();
        ImGui::Image((ImTextureID)(intptr_t)_heartUnfill.TextureId, UserInterfaceParameters::HeartTextureSize,
            UserInterfaceParameters::TextureCoordMin, UserInterfaceParameters::TextureCoordMax);
	}	
    ImGui::End();
}

/// <summary>
/// Draws a game over screen
/// </summary>
void UserInterface::drawGameOverScreen() {
    ImGui::Begin("Project Penguin - Game Over", nullptr, _windowFlags | ImGuiWindowFlags_NoBackground);
    std::string curr = "Your Score: ";
    curr.append(HighscoreManager->getScoreAsString());
    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::ScreenMiddleInX, ImGui::GetCursorPosY()));
    ImGui::Text(curr.c_str());
    if(HighscoreManager->isNewHighscore())  {
        static char buf[64] = "";
        ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::ScreenMiddleInX, ImGui::GetCursorPosY() + 10));
        ImGui::Text("Enter Your Name");
        ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::ScreenMiddleInX - 120, ImGui::GetCursorPosY() + 10));
    	ImGui::InputText("", buf, 64);
        ImGui::SameLine();
        ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::ScreenMiddleInX + 200, ImGui::GetCursorPosY()));
    	if(ImGui::Button("Confirm")){
            HighscoreManager->addNewHighscore(std::string(buf));
            _currentMenu = HIGHSCORE;
    	}        
    }
    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::ScreenMiddleInX, ImGui::GetCursorPosY() + 10));
    if (ImGui::Button("Back to Main Menu", UserInterfaceParameters::MainMenuButtonSize)) {
        _currentMenu = MAIN;
    }
    ImGui::End();
}

/// <summary>
/// Closes the window and ends the application
/// </summary>
void UserInterface::closeWindow() {
    glfwSetWindowShouldClose(_window, true);
    HighscoreManager->saveToFile();
}

/// <summary>
/// Returns the given Highscore formated into a single string to display in the highscore menu
/// </summary>
/// <param name="toFormat">Highscore to format</param>
/// <returns>string of format "rank. name - points"</returns>
std::string UserInterface::formatHighscore(Highscore toFormat) {
    std::string temp;
    temp.append(std::to_string(toFormat.rank) + ".");
    temp.append(" " + toFormat.name);
    temp.append(" - " + std::to_string(toFormat.points));
    return temp;
}

/// <summary>
/// Initializes the UserInterface by creating a window and starting GLFW, GLEW & imGUI
/// </summary>
UserInterface::UserInterface() {
    if (!glfwInit()) {
        _initStatus = false;
        return;
    }

    _window = glfwCreateWindow(Width, Height, TITLE, NULL, NULL);
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    _windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
    _heartFill = Texture("HeartFilled.png", GL_RGBA);
    _heartUnfill = Texture("HeartUnfilled.png", GL_RGBA);
	
    _initStatus = true;
}

/// <summary>
/// Returns true if the initialization in the constructor was successful
/// </summary>
bool UserInterface::getInitStatus() {
    return _initStatus;
}

/// <summary>
/// Calculates & returns the time between the current and the last frame
/// </summary>
float UserInterface::calculateDeltaTime() {
    float currentFrame = glfwGetTime();
    _deltaTime = currentFrame - _lastFrame;
    _lastFrame = currentFrame;
    return _deltaTime;
}

/// <summary>
/// Returns true if the game has started by selecting "New Game" in the main menu
/// </summary>
bool UserInterface::hasGameStarted() {
    return _currentMenu == GAME;
}

/// <summary>
/// Returns the pointer to the GLFW window object
/// </summary>
GLFWwindow* UserInterface::getWindowPointer() {
    return _window;
}

/// <summary>
/// Draws the UI with ImGUI every frame
/// </summary>
void UserInterface::drawUI() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (hasGameStarted()) {
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(Width, Height / 20), ImGuiCond_Always);
    } else {
        ImGui::SetNextWindowPos(ImVec2(Width / 4, Height / 4), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(Width / 2, Height / 2), ImGuiCond_Always);
    }
	
    switch(_currentMenu) {
    case MAIN:
        drawMainMenu();
        break;
    case HIGHSCORE:
        drawHighscoreMenu();
        break;
    case SETTINGS:
        drawSettingsMenu();
        break;
    case GAME:
        drawIngameUI();
        break;
    case GAME_OVER:
        drawGameOverScreen();
        break;
    }
	
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

/// <summary>
/// Clean up the used objects after the application is closed
/// </summary>
void UserInterface::cleanUp() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(_window);
    glfwTerminate();
}

/// <summary>
/// Processes Keyboard inputs to either close the window (ESC) or save them in the InputManager,
/// if the player character hasn't reached the end yet.
/// </summary>
/// <param name="character">Reference to the player character</param>
void UserInterface::processInput(Camera* cam) {
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        closeWindow();
    }

    if(PlayerCharacter->hasDied()) {
        _currentMenu = GAME_OVER;
        PlayerCharacter->reset();
        cam->reset();
    }
	
    if (!PlayerCharacter->hasReachedEnd() && !PlayerCharacter->hasDied() && hasGameStarted()) {
        InputManager->setInputStatus(LEFT, glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS);
        InputManager->setInputStatus(RIGHT, glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS);
        InputManager->setInputStatus(UP, glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS);
    }    
}