#ifndef SETTMAN_HEADER
#define SETTMAN_HEADER

#define ASCII_BIG_A 65
#define ASCII_BIG_Z 90
#define ASCII_SMALL_A 97
#define ASCII_SMALL_Z 122
#define RESOLUTIONS_NO 3
#define STRING_NO 19

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <GL/glfw3.h>

struct Settings {
	int language;
	int resolution;
	int jumpBtn;
	int rightBtn;
	int leftBtn;

	/// <summary>
	/// Sets the setting values to its default values
	/// </summary>
	Settings() {
		language = 0;
		resolution = 2;
		jumpBtn = GLFW_KEY_W;
		rightBtn = GLFW_KEY_D;
		leftBtn = GLFW_KEY_A;
	}

	/// <summary>
	/// Sets the settings to the given parameter values
	/// </summary>
	Settings(int lang, int res, int jump, int right, int left) :
		language(lang), resolution(res), jumpBtn(jump), rightBtn(right), leftBtn(left) {
	}
};

class SettingsManager {
private:
#if _DEBUG
	const std::string File = "Settings.set";
#else
	const std::string File = "./Assets/Settings.set";
#endif
	const std::string LocalizationLocationDebug = "../Assets/Localization/";
	const std::string LocalizationLocationRelease = "./Assets/Localization/";
	const std::string GermanFileName = "Deutsch.loc";
	const std::string EnglishFileName = "English.loc";
	
	Settings _settings;

	int _widths[RESOLUTIONS_NO] = { 1024, 1440, 1920 };
	int _heights[RESOLUTIONS_NO] = { 768, 900, 1080 };

	std::map<std::string, std::string> _strings;
	
	int checkAsciiConversion(int input);
	bool loadFromFile();
	bool saveToFile();
	bool readFromLocalizationFile();
	
public:	
	SettingsManager();
	
	void saveCurrentSettings(int lang, int res, int jump, int right, int left);
	
	int getLanguage();
	void setLanguage(int lang);
	const char* getStringForLanguage(int id);

	int getResolutionWidth();
	int getResolutionHeight();
	int getResolutionIndex();
	char* getResolutionAtPosition(int pos);
	void setResolution(int no);

	int getJumpButton();
	void setJumpButton(int key);
	
	int getRightButton();
	void setRightButton(int key);
	
	int getLeftButton();
	void setLeftButton(int key);
};

#endif // SETTMAN_HEADER