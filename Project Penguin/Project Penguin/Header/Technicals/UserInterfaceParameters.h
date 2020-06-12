#ifndef UI_PARAM_HEADER
#define UI_PARAM_HEADER

#include <imgui.h>
#include <Technicals/UserInterface.h>

class UserInterfaceParameters {
public:
	static ImVec2 UiSize;
	
	static ImVec2 MainMenuButtonSize;
	static float ScreenMiddleButtons;
	static float ScreenMiddleFlags;
	
	static ImVec2 HeartTextureSize;
	static ImVec2 LangFlagTextureSize;
	static ImVec2 TextureCoordMin;
	static ImVec2 TextureCoordMax;
};

#endif // UI_PARAM_HEADER
