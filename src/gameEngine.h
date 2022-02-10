#ifndef gameEngine_h
#define gameEngine_h

#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include "moving.h"
#include "potter.h"
#include "gnome.h"
#include "traal.h"
#include <signal.h>
#include <stdio.h>
#include <ctype.h>
#include "highscore.h"
#include <dirent.h>
#include <ctime>
using namespace std;


class GameEngine
{
private:
	HighScore highscore;
	vector<vector<char>> map;
	Gnome* gnome;
	Traal* traal;
	Potter* potter;
	int score;
	WINDOW* scoreWindow;
	WINDOW* mapWindow;
	WINDOW* statWindow;
	WINDOW* menuWindow;
	WINDOW* difficultyWindow;
	WINDOW* nameWindow;
	bool scroll;
	int diamonds;
	bool alive;
	bool esc_pressed;
	string mapFile;
	string scoreFile;
	void createMapWindow();
	void createStatWindow();
	void refreshStatWindow();
	void loadMap();
	void addJewels();
	void addScroll();
	void addPotter();
	void addGnome();
	void addTraal();
	void initNcurses();
	void startRound(string);
	void deadStatWindow();
	void clearStatWindow();
	string startMenu();
	string startDifficultyMenu();
	void startGame(string);
	string getName();
	void startHighScoreMenu();
	string pickRandomMap();
public:
	GameEngine();
	void Init(string,string);
};


#endif