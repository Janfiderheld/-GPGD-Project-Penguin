#include <Managers/HighscoreManager.h>

/// <summary>
/// Tries to save the current highscores and how many there are in the Highscore-File
/// </summary>
/// <returns>true if saving was successful</returns>
bool HighscoreManager::saveToFile() {
	std::ofstream out(FileName, std::ios::out | std::ios::binary);
	if(!out) {
		return false;
	}

	std::vector<Highscore>::size_type size = _highscores.size();
	try {
		out.write((char*)&size, sizeof(size));
		out.write((char*)&_highscores[0], _highscores.size() * sizeof(Highscore));
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	out.close();

	return out.good();
}

/// <summary>
/// Tries to load all highscores from the highscore file
/// </summary>
/// <returns>true if loading was successful</returns>
bool HighscoreManager::loadFromFile() {
	std::ifstream in(FileName, std::ios::in | std::ios::binary);
	if(!in)	{
		return false;
	}
	
	try	{
		std::vector<Highscore>::size_type size = 0;
		in.read((char*)&size, sizeof(size));
		_highscores.resize(size);
		in.read((char*)&_highscores[0], _highscores.size() * sizeof(Highscore));		
	} catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
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
	// TODO: Find out why std::sort leads to "read access violation"-error
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

	Highscore newHigh(0, name, _currentScore);
	_highscores.push_back(newHigh);
	sortAndChangeRanks(true);
	resetCurrentScore();
}