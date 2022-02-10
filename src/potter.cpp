#include "potter.h"


Potter::Potter (int _xLoc, int _yLoc, vector<vector<char>>* _map, WINDOW* _mapWindow, int* _score, bool* _scroll, int* _diamonds) : Moving(_xLoc, _yLoc, _map)
{
	esc_pressed = false;
	mapWindow = _mapWindow;
	alive = true;
	score = _score;
	scroll = _scroll;
	diamonds = _diamonds;
}

void Potter::setAlive(bool alive)
{
	this->alive = alive;
}

bool Potter::mvup()
{

	if ((map->at(yLoc-1)[xLoc]) != '*')
	{
		if ((map->at(yLoc-1)[xLoc]) == 'J')
		{
			(*score) = (*score) + 10;
			(*diamonds) = (*diamonds) + 1;
		}
		if ((map->at(yLoc-1)[xLoc]) == 'S')
		{
			(*score) = (*score) + 100;
			(*scroll) = true;
		}
		mvwaddch(mapWindow, yLoc, xLoc, ' ');
		map->at(yLoc)[xLoc] = ' ';
		yLoc = yLoc - 1;
		map->at(yLoc)[xLoc] = 'P';
		wattron(mapWindow,COLOR_PAIR(1));
		mvwaddch(mapWindow, yLoc, xLoc, 'P');
		wattroff(mapWindow,COLOR_PAIR(1));
		return true;
	}else
	{
		return false;
	}
}


bool Potter::mvdown()
{

	if ((map->at(yLoc+1)[xLoc]) != '*')
	{
		if ((map->at(yLoc+1)[xLoc]) == 'J')
		{
			(*score) = (*score) + 10;
			(*diamonds) = (*diamonds) + 1;

		}
		if ((map->at(yLoc+1)[xLoc]) == 'S')
		{
			(*score) = (*score) + 100;
			(*scroll) = true;
		}
		mvwaddch(mapWindow, yLoc, xLoc, ' ');
		map->at(yLoc)[xLoc] = ' ';
		yLoc = yLoc + 1;
		map->at(yLoc)[xLoc] = 'P';
		wattron(mapWindow,COLOR_PAIR(1));
		mvwaddch(mapWindow, yLoc, xLoc, 'P');
		wattroff(mapWindow,COLOR_PAIR(1));
		return true;
	}else
	{
		return false;
	}
}

bool Potter::mvleft()
{

	if ((map->at(yLoc)[xLoc-1]) != '*')
	{
		if ((map->at(yLoc)[xLoc-1]) == 'J')
		{
			(*score) = (*score) + 10;
			(*diamonds) = (*diamonds) + 1;
		}
		if ((map->at(yLoc)[xLoc-1]) == 'S')
		{
			(*score) = (*score) + 100;
			(*scroll) = true;
		}
		mvwaddch(mapWindow, yLoc, xLoc, ' ');
		map->at(yLoc)[xLoc] = ' ';
		xLoc = xLoc - 1;
		map->at(yLoc)[xLoc] = 'P';
		wattron(mapWindow,COLOR_PAIR(1));
		mvwaddch(mapWindow, yLoc, xLoc, 'P');
		wattroff(mapWindow,COLOR_PAIR(1));
		return true;
	}else
	{
		return false;
	}
}


bool Potter::mvright()
{

	if ((map->at(yLoc)[xLoc+1]) != '*')
	{
		if ((map->at(yLoc)[xLoc+1]) == 'J')
		{
			(*score) = (*score) + 10;
			(*diamonds) = (*diamonds) + 1;
		}
		if ((map->at(yLoc)[xLoc+1]) == 'S')
		{
			(*score) = (*score) + 100;
			(*scroll) = true;
		}
		mvwaddch(mapWindow, yLoc, xLoc, ' ');
		map->at(yLoc)[xLoc] = ' ';
		xLoc = xLoc + 1;
		map->at(yLoc)[xLoc] = 'P';
		wattron(mapWindow,COLOR_PAIR(1));
		mvwaddch(mapWindow, yLoc, xLoc, 'P');
		wattroff(mapWindow,COLOR_PAIR(1));
		return true;
	}else
	{
		return false;
	}
}



void Potter::calculateNextPosition()
{
	while(true)
	{
		bool valid = false;
		int choice = wgetch(mapWindow);
		if (choice == 27)
		{
			esc_pressed = true;
			break;
		}
		switch(choice)
		{
			case KEY_UP:
				if(mvup())
					valid = true;
				break;
			case KEY_DOWN:
				if(mvdown())
					valid = true;
				break;
			case KEY_LEFT:
				if(mvleft())
					valid = true;
				break;
			case KEY_RIGHT:
				if(mvright())
					valid = true;
				break;
			case 32:
				valid = true;
				break;
		}

		if (valid)
			break;
	}
}