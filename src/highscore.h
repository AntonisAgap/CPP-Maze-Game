#ifndef highscore_h
#define	highscore_h

#include <string>
#include <vector>
#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;


class HighScore
{
private:
	string tmpName;
	int tmpScore;
	vector<string> names;
	vector<int> scores;
	void addToTable();
public:
	HighScore();
	HighScore& operator<<(string);
	void operator<<(int);
	void showHighScores();
	void loadHighScores(string);
	void saveHighScores(string);
};

#endif