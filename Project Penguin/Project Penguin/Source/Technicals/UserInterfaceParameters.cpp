#include <Technicals/UserInterfaceParameters.h>

/// <summary>
/// Current width of the window
/// </summary>
int UserInterfaceParameters::Width = 0;

/// <summary>
/// Current height of the window
/// </summary>
int UserInterfaceParameters::Height = 0;

/// <summary>
/// Position of the top left corner of the big ui windows
/// </summary>
ImVec2 UserInterfaceParameters::BigWindowPos = ImVec2(0, 0);

/// <summary>
/// Position of the top left corner of the small ui windows
/// </summary>
ImVec2 UserInterfaceParameters::SmallWindowPos = ImVec2(0, 0);

/// <summary>
/// Size of the User Interface for the main menu
/// </summary>
ImVec2 UserInterfaceParameters::MainMenuUiSize = ImVec2(0, 0);

/// <summary>
/// Size of the User Interface for the settings menu
/// </summary>
ImVec2 UserInterfaceParameters::SettingsUiSize = ImVec2(0, 0);

/// <summary>
/// Size of the User Interface for the highscore menu and game over screen
/// </summary>
ImVec2 UserInterfaceParameters::SmallUiSize = ImVec2(0, 0);

/// <summary>/// 
/// Size of the User Interface during the game
/// </summary>
ImVec2 UserInterfaceParameters::IngameUiSize = ImVec2(0, 0);

/// <summary>
/// Size of the buttons in the Main Menu
/// </summary>
ImVec2 UserInterfaceParameters::MainMenuButtonSize = ImVec2(150, 50);

/// <summary>
/// Size of the Save Button in the Settings Menu
/// </summary>
ImVec2 UserInterfaceParameters::SaveButtonSize = ImVec2(125, 35);

/// <summary>
/// Difference in y-direction between the different ui objects
/// </summary>
float UserInterfaceParameters::DifferenceInY = MainMenuUiSize.y / 20.0f;

/// <summary>
/// Size of the heart texture 
/// </summary>
ImVec2 UserInterfaceParameters::HeartTextureSize = ImVec2(25, 25);

/// <summary>
/// Size of the flags for choosing a language
/// </summary>
ImVec2 UserInterfaceParameters::LangFlagTextureSize = ImVec2(128, 80);

/// <summary>
/// Top Left point of the texture
/// </summary>
ImVec2 UserInterfaceParameters::TextureCoordMin = ImVec2(0.0f, 1.0f);

/// <summary>
/// Bottom Right point of the texture
/// </summary>
ImVec2 UserInterfaceParameters::TextureCoordMax = ImVec2(1.0f, 0.0f);

/// <summary>
/// Middle of the screen on the x-axis for the big ui
/// </summary>
float UserInterfaceParameters::BigScreenMiddle = 0.0f;

/// <summary>
/// Middle of the screen on the x-axis for the small ui
/// </summary>
float UserInterfaceParameters::SmallScreenMiddle = 0.0f;

/// <summary>
/// Middle of the screen on the x-axis for the flag buttons in settings
/// </summary>
float UserInterfaceParameters::ScreenMiddleFlags = 0.0f;

/// <summary>
/// Middle of the screen on the x-axis for the text input elements
/// </summary>
float UserInterfaceParameters::ScreenMiddleInput = 0.0f;

/// <summary>
/// Settings Manager for updating the resolution
/// </summary>
SettingsManager* UserInterfaceParameters::SettingsManager = nullptr;

/// <summary>
/// Recalculates the UI Parameters after the resolution is changed
/// </summary>
void UserInterfaceParameters::Recalculate() {
	int resolution = SettingsManager->getResolutionIndex();
	Width = SettingsManager->getResolutionWidth();
	Height = SettingsManager->getResolutionHeight();

	switch(resolution) {
	// 800 x 400
	case 0:
		BigWindowPos = ImVec2(180, 50);
		SmallWindowPos = ImVec2(190, 50);
		
		MainMenuUiSize = ImVec2(300, 350);
		SmallUiSize = ImVec2(310,  325);
		SettingsUiSize = ImVec2(380, 420);
		
		BigScreenMiddle = 80;
		SmallScreenMiddle = 55;
		ScreenMiddleFlags = 40;
		ScreenMiddleInput = 20;
		
		break;

	// 1024 x 768
	case 1:
		BigWindowPos = ImVec2(300, 190);
		SmallWindowPos = ImVec2(350, 190);

		MainMenuUiSize = ImVec2(420, 380);
		SmallUiSize = ImVec2(350, 350);
		SettingsUiSize = ImVec2(420, 425);

		BigScreenMiddle = 140;
		SmallScreenMiddle = 75;
		ScreenMiddleFlags = 70;
		ScreenMiddleInput = 34;
		
		break;

	// 1440 x 900
	case 2:
		BigWindowPos = ImVec2(510, 260);
		SmallWindowPos = ImVec2(575, 260);

		MainMenuUiSize = ImVec2(420, 380);
		SmallUiSize = ImVec2(350, 350);
		SettingsUiSize = ImVec2(420, 425);

		BigScreenMiddle = 140;
		SmallScreenMiddle = 75;
		ScreenMiddleFlags = 70;
		ScreenMiddleInput = 34;
		
		break;

	// 1920 x 1080
	case 3:
		BigWindowPos = ImVec2(750, 350);
		SmallWindowPos = ImVec2(800, 350);

		MainMenuUiSize = ImVec2(420, 380);
		SmallUiSize = ImVec2(350, 350);
		SettingsUiSize = ImVec2(420, 425);

		BigScreenMiddle = 140;
		SmallScreenMiddle = 75;
		ScreenMiddleFlags = 70;
		ScreenMiddleInput = 34;
		
		break;
	}

	IngameUiSize = ImVec2(Width - 10, Height / 15.0f);
	DifferenceInY = MainMenuUiSize.y / 20.0f;
}