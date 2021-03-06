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
	std::ifstream in(File, std::ios::in | std::ios::binary);
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
	std::ofstream out(File, std::ios::out | std::ios::binary);
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
/// Reads the localization from a file
/// </summary>
/// <returns>true if reading was successful</returns>
bool SettingsManager::readFromLocalizationFile() {
#if _DEBUG
	std::string tempLocation = LocalizationLocationDebug + (_settings.language == 0 ? EnglishFileName : GermanFileName);
#else
	std::string tempLocation = LocalizationLocationRelease + (_settings.language == 0 ? EnglishFileName : GermanFileName);
#endif

	std::ifstream in(tempLocation.c_str(), std::ios::in);
	if (!in) {
		return false;
	}

	try	{
		std::string line;
		while (std::getline(in, line)) {
			std::istringstream is_line(line);
			std::string key;
			if (std::getline(is_line, key, '=')) {
				std::string value;
				if (std::getline(is_line, value)) {
					_strings[key] = value;
				}
			}
		}
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}	

	in.close();
	return in.good();
}

/// <summary>
/// If a settings file exists, it will be loaded
/// </summary>
SettingsManager::SettingsManager() {
	std::ifstream loadFrom(File);
	if ((bool)loadFrom) {
		loadFromFile();
	}
	readFromLocalizationFile();
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

/// <summary>
/// Returns the index of the currently chosen language
/// (0 for english, 1 for german)
/// </summary>
int SettingsManager::getLanguage() {
	return _settings.language;
}

/// <summary>
/// Sets the language and reloads the localization file accordingly
/// </summary>
void SettingsManager::setLanguage(int lang) {
	if(_settings.language != lang) {
		_settings.language = lang;
		readFromLocalizationFile();
	}
}

/// <summary>
/// Returns the string with the given index as a char
/// </summary>
const char* SettingsManager::getStringForLanguage(int id) {
	return _strings[std::to_string(id)].c_str();
}

/// <summary>
/// Returns the width for the current resolution
/// </summary>
int SettingsManager::getResolutionWidth() {
	return _widths[_settings.resolution];
}

/// <summary>
/// Returns the height for the current resolution
/// </summary>
int SettingsManager::getResolutionHeight() {
	return _heights[_settings.resolution];
}

/// <summary>
/// Returns the current resolutions index
/// </summary>
int SettingsManager::getResolutionIndex() {
	return _settings.resolution;
}

/// <summary>
/// Returns the resolution for a given index as a char to display in combo box
/// </summary>
/// <param name="pos">index to get values for</param>
char* SettingsManager::getResolutionAtPosition(int pos) {
	std::string temp = std::to_string(_widths[pos]) + " x " + std::to_string(_heights[pos]);
	char* toReturn = new char[temp.size() + 1];
	std::copy(temp.begin(), temp.end(), toReturn);
	toReturn[temp.size()] = '\0';
	return toReturn;
}

/// <summary>
/// Sets the index of the currently used resolution to the given parameter
/// </summary>
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