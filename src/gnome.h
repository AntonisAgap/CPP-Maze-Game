#ifndef gnome_h
#define gnome_h

#include "moving.h"
#include "potter.h"
#include <iostream>

using namespace std;

class Gnome: public Moving
{
private:
	Potter* potter;
	char prev_char;
	WINDOW* mapWindow;
	vector<int> findShortestPath(int ,int ,int ,int );
public:
	Gnome(int, int, vector<vector<char>>*, Potter*, WINDOW*);
	void calculateNextPosition();
};

#endif