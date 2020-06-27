#include <Technicals/UserInterfaceParameters.h>

/// <summary>
/// Current width of the window
/// </summary>
int UserInterfaceParameters::Width = 1920;

/// <summary>
/// Current height of the window
/// </summary>
int UserInterfaceParameters::Height = 1080;

/// <summary>
/// Position of the top left corner of the big ui windows
/// </summary>
ImVec2 UserInterfaceParameters::BigWindowPos = ImVec2(Width / 4.0f, Height / 4.0f);

/// <summary>
/// Position of the top left corner of the small ui windows
/// </summary>
ImVec2 UserInterfaceParameters::SmallWindowPos = ImVec2(Width / 3.0f, Height / 4.0f);

/// <summary>
/// Size of the User Interface for the main and settings menu
/// </summary>
ImVec2 UserInterfaceParameters::BigUiSize = ImVec2(Width / 2.0f, Height / 1.85f);

/// <summary>
/// Size of the User Interface for the highscore menu and game over screen
/// </summary>
ImVec2 UserInterfaceParameters::SmallUiSize = ImVec2(Width / 2.5f, Height / 2.7f);

/// <summary>/// 
/// Size of the User Interface during the game
/// </summary>
ImVec2 UserInterfaceParameters::IngameUiSize = ImVec2(Width, Height / 20.0f);

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
float UserInterfaceParameters::DifferenceInY = BigUiSize.y / 20.0f;

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
float UserInterfaceParameters::BigScreenMiddle = BigUiSize.x / 2.0f - MainMenuButtonSize.x / 2.0f;

/// <summary>
/// Middle of the screen on the x-axis for the small ui
/// </summary>
float UserInterfaceParameters::SmallScreenMiddle = SmallUiSize.x / 2.0f - MainMenuButtonSize.x / 2.0f;

/// <summary>
/// Middle of the screen on the x-axis for the flag buttons in settings
/// </summary>
float UserInterfaceParameters::ScreenMiddleFlags = BigUiSize.x / 4.0f - LangFlagTextureSize.x / 6.0f;

/// <summary>
/// Settings Manager for updating the resolution
/// </summary>
SettingsManager* UserInterfaceParameters::SettingsManager = nullptr;

/// <summary>
/// Recalculates the UI Parameters after the resolution is changed
/// </summary>
void UserInterfaceParameters::Recalculate() {
	Width = SettingsManager->getResolutionWidth();
	Height = SettingsManager->getResolutionHeight();
	
	BigWindowPos = ImVec2(Width / 4.0f, Height / 4.0f);
	SmallWindowPos = ImVec2(Width / 3.0f, Height / 4.0f);
	
	IngameUiSize = ImVec2(Width, Height / 20.0f);
	BigUiSize = ImVec2(Width / 2.0f, Height / 1.85f);
	SmallUiSize = ImVec2(Width / 2.5f, Height / 2.7f);
	
	DifferenceInY = BigUiSize.y / 20.0f;
	BigScreenMiddle = BigUiSize.x / 2.0f - MainMenuButtonSize.x / 2.0f;
	SmallScreenMiddle = SmallUiSize.x / 2.0f - MainMenuButtonSize.x / 2.0f;
	ScreenMiddleFlags = BigUiSize.x / 4.0f - LangFlagTextureSize.x / 6.0f;
}