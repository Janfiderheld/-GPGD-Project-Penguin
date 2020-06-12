#include <Technicals/UserInterfaceParameters.h>

/// <summary>
/// Size of the User Interface on which the ui is drawn
/// </summary>
ImVec2 UserInterfaceParameters::UiSize = ImVec2(UserInterface::Width / 2.0f, UserInterface::Height / 1.5f);

/// <summary>
/// Size of the buttons in the Main Menu
/// </summary>
ImVec2 UserInterfaceParameters::MainMenuButtonSize = ImVec2(150, 50);

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
/// Middle of the screen on the x-axis for the big buttons
/// </summary>
float UserInterfaceParameters::ScreenMiddleButtons = UiSize.x / 2.0f - MainMenuButtonSize.x / 2.0f;

/// <summary>
/// Middle of the screen on the x-axis for the flag buttons in settings
/// </summary>
float UserInterfaceParameters::ScreenMiddleFlags = UiSize.x / 4.0f - LangFlagTextureSize.x / 6.0f;