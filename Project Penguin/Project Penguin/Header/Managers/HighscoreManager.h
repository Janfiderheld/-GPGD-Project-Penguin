#ifndef HIGHMAN_HEADER
#define HIGHMAN_HEADER
#define HIGHSCORE_MAX_LENGTH 17

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

struct Highscore {
	int rank;
	char name[HIGHSCORE_MAX_LENGTH];
	int points;

	/// <summary>
	/// Empty constructor, which does nothing
	/// </summary>
	Highscore() {}

	/// <summary>
	/// Constructs a highscore by setting the values by the given parameters
	/// </summary>
	/// <param name="r">rank of this highscore</param>
	/// <param name="n">name of the person holding this highscore</param>
	/// <param name="p">points of this highscore</param>
	Highscore(int r, char n[HIGHSCORE_MAX_LENGTH], int p) : rank(r), points(p) {
		strcpy_s(name, n);
	}
	
	/// <summary>
	/// Compares this highscore to the given one based on the points they have
	/// </summary>
	/// <param name="h1">highscore to compare with</param>
	/// <returns>True if this highscore has less points than the given one</returns>
	bool operator<(const Highscore& h1) const {
		return h1.points < points;
	}
};

class HighscoreManager {
private:
	const int MaxHighscores = 10;
	const std::string FileName = "Highscore.hsc";
	
	int _currentScore = 0;
	std::vector<Highscore> _highscores;

	bool loadFromFile();
	void resetCurrentScore();
	void sortAndChangeRanks();

public:
	HighscoreManager();

	void addToCurrentScore(int val);
	void addNewHighscore(char* name);
	bool isNewHighscore();
	bool saveToFile();
	
	std::string getScoreAsString();
	std::vector<Highscore> getHighscores();
};

#endif // HIGHMAN_HEADER