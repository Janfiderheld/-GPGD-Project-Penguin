#ifndef SETTMAN_HEADER
#define SETTMAN_HEADER

#define ASCII_BIG_A 65
#define ASCII_BIG_Z 90
#define ASCII_SMALL_A 97
#define ASCII_SMALL_Z 122

#include <string>
#include <iostream>
#include <fstream>
#include <GL/glfw3.h>

struct Settings {
	int language;
	int resolution;
	int jumpBtn;
	int rightBtn;
	int leftBtn;

	Settings() {
		language = 0;
		resolution = 0;
		jumpBtn = GLFW_KEY_W;
		rightBtn = GLFW_KEY_D;
		leftBtn = GLFW_KEY_A;
	}
	
	Settings(int lang, int res, int jump, int right, int left) :
		language(lang), resolution(res), jumpBtn(jump), rightBtn(right), leftBtn(left) {
	}
};

class SettingsManager {
private:
	const std::string FileName = "Settings.set";
	
	Settings _settings;

	int checkAsciiConversion(int input);
	bool loadFromFile();
	bool saveToFile();
	
public:
	SettingsManager();

	void saveCurrentSettings(int lang, int res, int jump, int right, int left);
	
	int getLanguage();
	void setLanguage(int lang);
	
	int getResolutionWidth();
	int getResolutionHeight();
	void setResolution(int no);

	int getJumpButton();
	void setJumpButton(int key);
	
	int getRightButton();
	void setRightButton(int key);
	
	int getLeftButton();
	void setLeftButton(int key);
};

#endif // SETTMAN_HEADER