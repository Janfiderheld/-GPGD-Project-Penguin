#include <Managers/HighscoreManager.h>

bool HighscoreManager::saveToFile() {
	// TODO: Save into simple text file (Encryption?) 
	return false;
}

bool HighscoreManager::loadFromFile() {
	// TODO: Load from simple text file (Encryption?) 
	return false;
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
/// 
/// </summary>
HighscoreManager::HighscoreManager() {
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