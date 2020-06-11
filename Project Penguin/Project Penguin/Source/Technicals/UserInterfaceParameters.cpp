#include <Technicals/UserInterfaceParameters.h>

/// <summary>
/// Size of the buttons in the Main Menu
/// </summary>
ImVec2 UserInterfaceParameters::MainMenuButtonSize = ImVec2(150, 50);

/// <summary>
/// Middle of the screen on the x-axis
/// </summary>
float UserInterfaceParameters::ScreenMiddleInX = (float)UserInterface::Width / 4.0f - MainMenuButtonSize.x / 2.0f;;

/// <summary>
/// Size of the heart texture 
/// </summary>
ImVec2 UserInterfaceParameters::HeartTextureSize = ImVec2(25, 25);

/// <summary>
/// Top Left point of the texture
/// </summary>
ImVec2 UserInterfaceParameters::TextureCoordMin = ImVec2(0.0f, 1.0f);

/// <summary>
/// Bottom Right point of the texture
/// </summary>
ImVec2 UserInterfaceParameters::TextureCoordMax = ImVec2(1.0f, 0.0f);