#ifndef potter_h
#define potter_h

#include "moving.h"
#include <ncurses.h>

using namespace std;

class Potter : public Moving
{
private:
	bool mvup();
	bool mvdown();
	bool mvleft();
	bool mvright();
	bool esc_pressed;
	WINDOW* mapWindow;
	int* score;
	bool* scroll;
	int* diamonds;
	bool alive;
public:
	bool getEscPressed(){return esc_pressed;}
	bool getAlive(){return alive;}
	void setAlive(bool);
	Potter(int, int, vector<vector<char>>*, WINDOW*, int*, bool*, int*);
	void calculateNextPosition();
};

#endif