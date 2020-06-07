#ifndef HIGHMAN_HEADER
#define HIGHMAN_HEADER

#include <vector>
#include <string>
#include <algorithm>

struct Highscore {
	int rank;
	int points;
	std::string name;

	/// <summary>
	/// Compares this highscore to the given one based on the points they have
	/// </summary>
	/// <param name="h1">highscore to compare with</param>
	/// <returns>True if this highscore has less points than the given one</returns>
	bool operator<(const Highscore& h1) const {
		return points < h1.points;
	}
};

class HighscoreManager {
private:
	const int MaxHighscores = 10;

	int _currentScore = 0;
	std::vector<Highscore> _highscores;

	bool saveToFile();
	bool loadFromFile();

	void resetCurrentScore();
	bool compareTwoHighscores(const Highscore& h1, const Highscore& h2);
	void sortAndChangeRanks(bool deleteLast);

public:
	HighscoreManager();

	void addToCurrentScore(int val);
	void addNewHighscore(std::string name);
};

#endif // HIGHMAN_HEADER