#include <Technicals/UserInterface.h>

/// <summary>
/// Title of the window
/// </summary>
const char* UserInterface::Title = "Project Penguin";

/// <summary>
/// Facade of the level which is used to reset the level between games
/// </summary>
GridFacade* UserInterface::LevelGrid = nullptr;

/// <summary>
/// Reference to the InputManager, which saves which key is pressed.
/// </summary>
InputManager* UserInterface::InputManager = nullptr;

/// <summary>
/// Reference to the HighscoreManager, which is for everything related to highscores
/// </summary>
HighscoreManager* UserInterface::HighscoreManager = nullptr;

/// <summary>
/// Reference to the CollectableManager, to regenerate the collectables after a level end
/// </summary>
CollectableManager* UserInterface::CollectableManager = nullptr;

/// <summary>
/// Reference to the EnemyManager, to reset & replace the different enemies
/// </summary>
EnemyManager* UserInterface::EnemyManager = nullptr;

/// <summary>
/// Reference to the main character, which is controlled by the player
/// </summary>
Character* UserInterface::PlayerCharacter = nullptr;

/// <summary>
/// Reference to the SettingsManager for loading and changing the settings
/// </summary>
SettingsManager* UserInterface::SettingsManager = nullptr;

/// <summary>
/// Draws the Main Menu
/// </summary>
void UserInterface::drawMainMenu() {
    ImGui::Begin("Project Penguin - Main Menu", nullptr, _windowFlags);
    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::BigScreenMiddle, ImGui::GetCursorPosY() + UserInterfaceParameters::DifferenceInY));
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(44, 32, 148));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor( 22, 177, 103));
    if (ImGui::Button(SettingsManager->getStringForLanguage(0), UserInterfaceParameters::MainMenuButtonSize)) {
        _currentMenu = GAME;
    }
    ImGui::PopStyleColor(2);

    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::BigScreenMiddle, ImGui::GetCursorPosY() + UserInterfaceParameters::DifferenceInY));
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(44, 32, 148));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(22, 177, 103));
	if(ImGui::Button(SettingsManager->getStringForLanguage(1), UserInterfaceParameters::MainMenuButtonSize)) {
        _currentMenu = HIGHSCORE;
	}
    ImGui::PopStyleColor(2);

    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::BigScreenMiddle, ImGui::GetCursorPosY() + UserInterfaceParameters::DifferenceInY));
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(44, 32, 148));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(22, 177, 103));
	if(ImGui::Button(SettingsManager->getStringForLanguage(2), UserInterfaceParameters::MainMenuButtonSize))	{
        _currentMenu = SETTINGS;
	}
    ImGui::PopStyleColor(2);

    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::BigScreenMiddle, ImGui::GetCursorPosY() + UserInterfaceParameters::DifferenceInY));
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(44, 32, 148));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(22, 177, 103));
	if(ImGui::Button(SettingsManager->getStringForLanguage(3), UserInterfaceParameters::MainMenuButtonSize)) {
        closeWindow();
	}
    ImGui::PopStyleColor(2);
    ImGui::End();
}

/// <summary>
/// Draws the Highscore-Menu
/// </summary>
void UserInterface::drawHighscoreMenu() {
    ImGui::Begin("Project Penguin - Highscores", nullptr, _windowFlags);
    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::SmallScreenMiddle, ImGui::GetCursorPosY() + UserInterfaceParameters::DifferenceInY));
    ImGui::Text(SettingsManager->getStringForLanguage(5));

    std::vector<Highscore> _highscores = HighscoreManager->getHighscores();
	for(int i = 0; i < _highscores.size(); i++) {
        if (i == 0) {
            ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor(255, 215, 0));
        }
        if (i == 1) {
            ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor(192, 192, 192));
        }
        if (i == 2) {
            ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor(184, 115, 51));
        }
        ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::SmallScreenMiddle, ImGui::GetCursorPosY()));
        ImGui::Text(formatHighscore(_highscores.at(i)).c_str());
        if (i == 0 || i == 1 || i == 2) {
            ImGui::PopStyleColor(1);
        }
	}
    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::SmallScreenMiddle, ImGui::GetCursorPosY() + 50));
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(44, 32, 148));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(22, 177, 103));
    if (ImGui::Button(SettingsManager->getStringForLanguage(4), UserInterfaceParameters::MainMenuButtonSize)) {
        _currentMenu = MAIN;
    }
    ImGui::PopStyleColor(2);
    ImGui::End();
}

/// <summary>
/// Draws the Settings-Menu
/// </summary>
void UserInterface::drawSettingsMenu() {
    if(_firstSettingsFrame) {
        _language = SettingsManager->getLanguage();
    }
	
	ImGui::Begin("Project Penguin - Settings", nullptr, _windowFlags);		
    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::BigScreenMiddle, ImGui::GetCursorPosY() + UserInterfaceParameters::DifferenceInY));
    ImGui::Text(SettingsManager->getStringForLanguage(6));
	
    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::ScreenMiddleFlags, ImGui::GetCursorPosY()));
    ImVec4 green = ImColor(0.0f, 1.0f, 0.0f);
    ImVec4 red = ImColor(1.0f, 0.0f, 0.0f);
    ImGui::PushStyleColor(ImGuiCol_Button, _language == 0 ? green : red);
	if(ImGui::ImageButton((ImTextureID)(intptr_t)_ukFlag.TextureId, UserInterfaceParameters::LangFlagTextureSize,
        UserInterfaceParameters::TextureCoordMin, UserInterfaceParameters::TextureCoordMax))	{
        _language = 0;
	}
    ImGui::PopStyleColor(1);
    
    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, _language == 1 ? green : red);
	if(ImGui::ImageButton((ImTextureID)(intptr_t)_germanFlag.TextureId, UserInterfaceParameters::LangFlagTextureSize,
        UserInterfaceParameters::TextureCoordMin, UserInterfaceParameters::TextureCoordMax)) {
        _language = 1;
    }
    ImGui::PopStyleColor(1);

    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::BigScreenMiddle, ImGui::GetCursorPosY() + UserInterfaceParameters::DifferenceInY));
    ImGui::Text(SettingsManager->getStringForLanguage(7));
    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::ScreenMiddleInput, ImGui::GetCursorPosY()));
    static int currResolution = SettingsManager->getResolutionIndex();
    if (ImGui::BeginCombo("", SettingsManager->getResolutionAtPosition(currResolution), 0)) {
        for (int i = 0; i < RESOLUTIONS_NO; i++) {
            bool selected = (currResolution == i);
            if (ImGui::Selectable(SettingsManager->getResolutionAtPosition(i), selected)) {
                currResolution = i;
            }
            if (selected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::ScreenMiddleInput, ImGui::GetCursorPosY() + UserInterfaceParameters::DifferenceInY));
    ImGui::Text(SettingsManager->getStringForLanguage(8));
    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::ScreenMiddleInput, ImGui::GetCursorPosY()));
    static char jump[2];
	if(_firstSettingsFrame)	{
        jump[0] = SettingsManager->getJumpButton();
	}
    ImGui::InputText(SettingsManager->getStringForLanguage(9), jump, IM_ARRAYSIZE(jump));
	
    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::ScreenMiddleInput, ImGui::GetCursorPosY()));
    static char left[2];
	if(_firstSettingsFrame) {
        left[0] = SettingsManager->getLeftButton();
	}
    ImGui::InputText(SettingsManager->getStringForLanguage(11), left, IM_ARRAYSIZE(left));
	
    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::ScreenMiddleInput, ImGui::GetCursorPosY()));
    static char right[2];
	if(_firstSettingsFrame)	{
        right[0] = SettingsManager->getRightButton();
	}
    ImGui::InputText(SettingsManager->getStringForLanguage(10), right, IM_ARRAYSIZE(right));

    if(_wrongInput) {
        ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::ScreenMiddleInput, ImGui::GetCursorPosY()));
        ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor(255, 0, 0));
        ImGui::Text(SettingsManager->getStringForLanguage(12));
        ImGui::PopStyleColor(1);
    }
	
    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::BigScreenMiddle + 10, ImGui::GetCursorPosY() + (UserInterfaceParameters::DifferenceInY / 2.0f)));
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(44, 32, 148));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(22, 177, 103));
    if (ImGui::Button(SettingsManager->getStringForLanguage(13), UserInterfaceParameters::SaveButtonSize)) {
        _wrongInput = jump[0] == left[0] || jump[0] == right[0] || left[0] == right[0];
    	if(!_wrongInput) {
            SettingsManager->saveCurrentSettings(_language, currResolution, jump[0], right[0], left[0]);
            UserInterfaceParameters::Recalculate();
            glfwSetWindowSize(_window, UserInterfaceParameters::Width, UserInterfaceParameters::Height);
    	}
    }
    ImGui::PopStyleColor(2);
	
    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::BigScreenMiddle, ImGui::GetCursorPosY() + (UserInterfaceParameters::DifferenceInY / 2.0f)));
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(44, 32, 148));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(22, 177, 103));
    if (ImGui::Button(SettingsManager->getStringForLanguage(4), UserInterfaceParameters::MainMenuButtonSize)) {
        _currentMenu = MAIN;
    }
    ImGui::PopStyleColor(2);	
    ImGui::End();

    _firstSettingsFrame = false;
}

/// <summary>
/// Draws the UI during the Game
/// </summary>
void UserInterface::drawIngameUI() {
    ImGui::Begin("Project Penguin - Game", nullptr, _windowFlags);
    std::string curr = SettingsManager->getStringForLanguage(14);
	curr.append(HighscoreManager->getScoreAsString());
    ImGui::Text(curr.c_str());
    ImGui::SameLine();
    ImGui::Text(SettingsManager->getStringForLanguage(15));
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
    ImGui::Begin("Project Penguin - Game Over", nullptr, _windowFlags);
    std::string curr = SettingsManager->getStringForLanguage(16);
    curr.append(HighscoreManager->getScoreAsString());
    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::SmallScreenMiddle, ImGui::GetCursorPosY() + UserInterfaceParameters::DifferenceInY));
    ImGui::Text(curr.c_str());
    if(HighscoreManager->isNewHighscore())  {
        static char buf[HIGHSCORE_MAX_LENGTH] = "";
        ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::SmallScreenMiddle, ImGui::GetCursorPosY() + 10));
        ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor(255, 255, 255));
        ImGui::Text(SettingsManager->getStringForLanguage(17));
        ImGui::PopStyleColor(1);
        ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::ScreenMiddleInput, ImGui::GetCursorPosY() + 10));
    	ImGui::InputText("", buf, HIGHSCORE_MAX_LENGTH);
    	
        ImGui::SameLine();    	
        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(44, 32, 148));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(22, 177, 103));
    	if(ImGui::Button(SettingsManager->getStringForLanguage(18))){
    		if(buf[0] != '\0') {
                _wrongInput = false;
                HighscoreManager->addNewHighscore(buf);
                buf[0] = '\0';
                _currentMenu = HIGHSCORE;
    		} else {
                _wrongInput = true;
    		}
    	}
        ImGui::PopStyleColor(2);

        if (_wrongInput) {
            ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::ScreenMiddleInput, ImGui::GetCursorPosY()));
            ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor(255, 0, 0));
            ImGui::Text(SettingsManager->getStringForLanguage(19));
            ImGui::PopStyleColor(1);
        }
    }
    ImGui::SetCursorPos(ImVec2(UserInterfaceParameters::SmallScreenMiddle, ImGui::GetCursorPosY() + 10));
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(44, 32, 148));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(22, 177, 103));
    if (ImGui::Button(SettingsManager->getStringForLanguage(4), UserInterfaceParameters::MainMenuButtonSize)) {
        HighscoreManager->resetCurrentScore();
        _currentMenu = MAIN;
    }
    ImGui::PopStyleColor(2);
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
	if(toFormat.rank < 10) {
        temp.append("0");
	}
    temp.append(std::to_string(toFormat.rank) + ". ");
	temp += toFormat.name;
	for(int i = temp.length(); i < HIGHSCORE_MAX_LENGTH + 4; i++) {
        temp.append(" ");
	}
    temp.append("- " + std::to_string(toFormat.points));
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

    UserInterfaceParameters::Recalculate();
    _window = glfwCreateWindow(UserInterfaceParameters::Width, UserInterfaceParameters::Height, Title, 0, NULL);
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
    _ukFlag = Texture("uk_flag.png", GL_RGB);
    _germanFlag = Texture("germany_flag.png", GL_RGB);
	
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

    switch(_currentMenu) {
    case MAIN:
        ImGui::SetNextWindowPos(UserInterfaceParameters::BigWindowPos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(UserInterfaceParameters::MainMenuUiSize, ImGuiCond_Always);
        drawMainMenu();
        break;
    case HIGHSCORE:
        ImGui::SetNextWindowPos(UserInterfaceParameters::SmallWindowPos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(UserInterfaceParameters::SmallUiSize, ImGuiCond_Always);
        drawHighscoreMenu();
        break;
    case SETTINGS:
        ImGui::SetNextWindowPos(UserInterfaceParameters::BigWindowPos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(UserInterfaceParameters::SettingsUiSize, ImGuiCond_Always);
        drawSettingsMenu();
        break;
    case GAME:
        ImGui::SetNextWindowPos(ImVec2(5, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(UserInterfaceParameters::IngameUiSize, ImGuiCond_Always);
        drawIngameUI();
        break;
    case GAME_OVER:
        ImGui::SetNextWindowPos(UserInterfaceParameters::SmallWindowPos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(UserInterfaceParameters::SmallUiSize, ImGuiCond_Always);
        drawGameOverScreen();
        break;
    }

    _firstSettingsFrame = _currentMenu == SETTINGS ? _firstSettingsFrame : true;
	
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

    if(PlayerCharacter->hasDied() || PlayerCharacter->hasReachedEnd()) {
        _currentMenu = GAME_OVER;
        PlayerCharacter->reset();
        cam->reset();
    	
        LevelGrid->generateLevel();
        CollectableManager->generateCollectables();
        EnemyManager->generateEnemies();
    }
	
    if (!PlayerCharacter->hasReachedEnd() && !PlayerCharacter->hasDied() && hasGameStarted()) {
        InputManager->setInputStatus(LEFT, glfwGetKey(_window, SettingsManager->getLeftButton()) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS);
        InputManager->setInputStatus(RIGHT, glfwGetKey(_window, SettingsManager->getRightButton()) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS);
        InputManager->setInputStatus(UP, glfwGetKey(_window, SettingsManager->getJumpButton()) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS);
    }    
}