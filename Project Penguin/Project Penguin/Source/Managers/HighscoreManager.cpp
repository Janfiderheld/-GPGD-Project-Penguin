#include <Managers/HighscoreManager.h>

/// <summary>
/// Saves the current highscores in the Highscore-File
/// </summary>
/// <returns>true if saving was successful</returns>
bool HighscoreManager::saveToFile() {
	std::ofstream out(FileName, std::ios::out | std::ios::binary);
	if(!out) {
		return false;
	}
	
	for(const auto &h : _highscores) {
		out.write((char*) &h, sizeof(Highscore));
	}
	out.close();

	return out.good();
}

/// <summary>
/// Returns the number of Highscores (= number of lines) in the file
/// </summary>
int HighscoreManager::getNumberOfHighscores() {
	std::ifstream in(FileName, std::ios::in | std::ios::binary);
	if(!in)	{
		return 0;
	}
	
	int numLines = 0;
	std::string unused;
	while (std::getline(in, unused)) {
		++numLines;
	}
	in.close();
	return numLines;
}

/// <summary>
/// Loads all highscores from the highscore file
/// </summary>
/// <returns>true if loading was successful</returns>
bool HighscoreManager::loadFromFile() {
	std::ifstream in(FileName, std::ios::in | std::ios::binary);
	if(!in)	{
		return false;
	}

	int numLines = getNumberOfHighscores();
	for(int i = 0; i < numLines; i++) {
		Highscore temp;
		in.read((char*)&temp, sizeof(Highscore));
		_highscores.push_back(temp);
		// TODO: Find out why crash when this line is finished
	}
	in.close();

	return in.good();
}

/// <summary>
/// Resets the current score back to zero.
/// </summary>
void HighscoreManager::resetCurrentScore() {
	_currentScore = 0;
}

/// <summary>
/// Sorts the Highscores based on their scores and changes the ranks accordingly.
/// If the parameter is set to true, the last highscore after the sorting is deleted
/// </summary>
void HighscoreManager::sortAndChangeRanks(bool deleteLast) {
	std::sort(_highscores.begin(), _highscores.end());
	if (deleteLast && _highscores.size() > MaxHighscores) {
		_highscores.pop_back();
	}

	for (int i = 1; i <= _highscores.size(); i++) {
		_highscores.at(i).rank = i;
	}
}

/// <summary>
/// Loads the highscores from a highscore file, if one exists
/// </summary>
HighscoreManager::HighscoreManager() {
	std::ifstream loadFrom(FileName);
	if((bool)loadFrom) {
		loadFromFile();
	}
}

/// <summary>
/// Adds the given value to the current score.
/// </summary>
void HighscoreManager::addToCurrentScore(int val) {
	_currentScore += val;
}

/// <summary>
/// Adds the current points to the highscores, if they exceed the currently lowest score.
/// Afterwards the highscores are sorted and the smallest score is deleted.
/// </summary>
/// <param name="name">name of the player which belongs to the highscore</param>
void HighscoreManager::addNewHighscore(std::string name) {	
	if (_currentScore <= _highscores.back().points) {
		return;
	}

	Highscore newHigh;
	newHigh.name = name;
	newHigh.points = _currentScore;
	_highscores.push_back(newHigh);
	sortAndChangeRanks(true);
	resetCurrentScore();
}