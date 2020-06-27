#ifndef UI_PARAM_HEADER
#define UI_PARAM_HEADER

#include <imgui.h>
#include <Managers/SettingsManager.h>

class UserInterfaceParameters {
public:
	static int Width;
	static int Height;
	
	static ImVec2 BigWindowPos;
	static ImVec2 SmallWindowPos;
	
	static ImVec2 MainMenuUiSize;
	static ImVec2 SettingsUiSize;
	static ImVec2 SmallUiSize;
	static ImVec2 IngameUiSize;
	
	static ImVec2 MainMenuButtonSize;
	static ImVec2 SaveButtonSize;
	
	static float DifferenceInY;
	static float BigScreenMiddle;
	static float SmallScreenMiddle;
	static float ScreenMiddleFlags;
	static float ScreenMiddleInput;
	
	static ImVec2 HeartTextureSize;
	static ImVec2 LangFlagTextureSize;
	static ImVec2 TextureCoordMin;
	static ImVec2 TextureCoordMax;

	static SettingsManager* SettingsManager;
	static void Recalculate();
};

#endif // UI_PARAM_HEADER
