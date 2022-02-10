#include "moving.h"
//TODO: maybe do map with pointers

Moving::Moving(int _xLoc, int _yLoc, vector<vector<char>>* _map)
{
	xLoc = _xLoc;
	yLoc = _yLoc;
	map = _map;
}

void Moving::set_xLoc(int _xLoc)
{
	xLoc = _xLoc;
}

void Moving::set_yLoc(int _yLoc)
{
	yLoc = _yLoc;
}

