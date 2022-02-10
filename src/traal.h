#ifndef traal_h
#define traal_h

#include "moving.h"
#include "potter.h"
#include <iostream>

using namespace std;

class Traal : public Moving
{
private:
	char prev_char;
	WINDOW* mapWindow;
	Potter* potter;
	vector<int> findShortestPath(int ,int ,int ,int );
public:
	Traal(int, int, vector<vector<char>>*, Potter*, WINDOW*);
	void calculateNextPosition();
};

#endif