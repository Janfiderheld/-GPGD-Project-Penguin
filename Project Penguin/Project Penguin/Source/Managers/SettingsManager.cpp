#include <Managers/SettingsManager.h>

/// <summary>
/// Checks if the given input is a legit character and converts a small letter to a capital one
/// </summary>
/// <param name="input">int of the key</param>
/// <returns>the changed input or -1 if the default value should be used</returns>
int SettingsManager::checkAsciiConversion(int input) {
	if (input < ASCII_BIG_A || input > ASCII_SMALL_Z ||
		input > ASCII_BIG_Z && input < ASCII_SMALL_A) {
		return -1;
	}

	if (input >= ASCII_SMALL_A && input <= ASCII_SMALL_Z) {
		return input - ASCII_SMALL_A + ASCII_BIG_A;
	}

	return input;
}

/// <summary>
/// Loads the settings from the Settings.set-File
/// </summary>
/// <returns>true if the settings could be loaded</returns>
bool SettingsManager::loadFromFile() {
	std::ifstream in(FileName, std::ios::in | std::ios::binary);
	if (!in) {
		return false;
	}

	try {
		int l, r;
		int ju, ri, le;
		in.read((char*)&l, sizeof(int));
		in.read((char*)&r, sizeof(int));
		in.read((char*)&ju, sizeof(int));
		in.read((char*)&ri, sizeof(int));
		in.read((char*)&le, sizeof(int));
		_settings = Settings(l, r, ju, ri, le);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	in.close();
	return in.good();
}

/// <summary>
/// Saves the current settings to the Settings.set file
/// </summary>
/// <returns>true if saving was successful</returns>
bool SettingsManager::saveToFile() {
	std::ofstream out(FileName, std::ios::out | std::ios::binary);
	if (!out) {
		return false;
	}

	try {
		out.write((char*)&_settings.language, sizeof(int));
		out.write((char*)&_settings.resolution, sizeof(int));
		out.write((char*)&_settings.jumpBtn, sizeof(int));
		out.write((char*)&_settings.rightBtn, sizeof(int));
		out.write((char*)&_settings.leftBtn, sizeof(int));
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	
	out.close();
	return out.good(); 
}

/// <summary>
/// If a settings file exists, it will be loaded
/// </summary>/// <returns></returns>
SettingsManager::SettingsManager() {
	std::ifstream loadFrom(FileName);
	if ((bool)loadFrom) {
		loadFromFile();
	} 
}

/// <summary>
/// saves the given parameters as the settings in the file
/// </summary>
/// <param name="lang">language</param>
/// <param name="res">resolution</param>
/// <param name="jump">jump button</param>
/// <param name="right">right button</param>
/// <param name="left">left button</param>
void SettingsManager::saveCurrentSettings(int lang, int res, int jump, int right, int left) {
	setLanguage(lang);
	setResolution(res);
	setJumpButton(jump);
	setRightButton(right);
	setLeftButton(left);
	saveToFile();
}

int SettingsManager::getLanguage() {
	return _settings.language;
}

void SettingsManager::setLanguage(int lang) {
	_settings.language = lang;
}

int SettingsManager::getResolutionWidth() {
	return 0;
}

int SettingsManager::getResolutionHeight() {
	return 0;
}

void SettingsManager::setResolution(int no) {
	_settings.resolution = no;
}

/// <summary>
/// Returns the button used for jumping
/// </summary>
int SettingsManager::getJumpButton() {
	return _settings.jumpBtn;
}

/// <summary>
/// Sets the button for jumping to the given key, if it is an acceptable key.
/// If not, the default key is used
/// </summary>
void SettingsManager::setJumpButton(int key) {
	int toSet = checkAsciiConversion(key);
	_settings.jumpBtn = toSet == -1 ? GLFW_KEY_W : toSet;
}

/// <summary>
/// Returns the button used for walking right
/// </summary>
int SettingsManager::getRightButton() {
	return _settings.rightBtn;
}

/// <summary>
/// Sets the button for walking right to the given key, if it is an acceptable key.
/// If not, the default key is used
/// </summary>
void SettingsManager::setRightButton(int key) {
	int toSet = checkAsciiConversion(key);
	_settings.rightBtn = toSet == -1 ? GLFW_KEY_D : toSet;
}

/// <summary>
/// Returns the button used for walking left
/// </summary>
int SettingsManager::getLeftButton() {
	return _settings.leftBtn;
}

/// <summary>
/// Sets the button for walking left to the given key, if it is an acceptable key.
/// If not, the default key is used
/// </summary>
void SettingsManager::setLeftButton(int key) {
	int toSet = checkAsciiConversion(key);
	_settings.leftBtn = toSet == -1 ? GLFW_KEY_A : toSet;
}