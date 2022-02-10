#ifndef moving_h
#define moving_h

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class Moving
{
protected:
	vector<vector<char>>* map;
	int xLoc;
	int yLoc;
public:
	Moving(int, int,vector<vector<char>>*);
	int get_xLoc(){return xLoc;}
	int get_yLoc(){return yLoc;}
	void set_xLoc(int);
	void set_yLoc(int);
	virtual void calculateNextPosition() = 0;
};
#endif