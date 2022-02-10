#include "gnome.h"

Gnome::Gnome(int _xLoc, int _yLoc, vector<vector<char>>* _map, Potter* _potter, WINDOW* _mapWindow) : Moving(_xLoc, _yLoc, _map)
{
	potter = _potter;
	mapWindow = _mapWindow;
	prev_char = ' ';

}

void Gnome::calculateNextPosition()
{

	vector<int> path;

	path = findShortestPath(this->yLoc,this->xLoc,potter->get_yLoc(),potter->get_xLoc());
	int newY,newX;

	newY = path[0];
	newX = path[1];

	map->at(yLoc)[xLoc] = prev_char;
	
	if (prev_char == 'J')
	{
		wattron(mapWindow,COLOR_PAIR(2));
		mvwaddch(mapWindow, yLoc, xLoc, prev_char);
		wattroff(mapWindow,COLOR_PAIR(2));
	}else if (prev_char == 'S')
	{
		wattron(mapWindow, COLOR_PAIR(3));
		mvwaddch(mapWindow, yLoc, xLoc, prev_char);
		wattroff(mapWindow, COLOR_PAIR(3));
	}else
		mvwaddch(mapWindow, yLoc, xLoc, prev_char);

	yLoc = newY;
	xLoc = newX;
	prev_char = map->at(yLoc)[xLoc];

	if ((xLoc == potter->get_xLoc()) and (yLoc == potter->get_yLoc()))
	{
		potter->setAlive(false);
	}

	map->at(yLoc)[xLoc] = 'G';

	wattron(mapWindow,COLOR_PAIR(4));
	mvwaddch(mapWindow, yLoc, xLoc, 'G');
	wattroff(mapWindow,COLOR_PAIR(4));
}


vector<int> Gnome::findShortestPath(int sr,int sc,int fr,int fc)
{

	vector<vector<int>> path;
	vector<int> next_step;
	if(sr==fr and sc==fc)
	{
		next_step.push_back(sr);
		next_step.push_back(sc);
		return next_step;
	}

	int dr[4] = {-1, 1, 0, 0};
	int dc[4] = {0, 0, 1, -1};

	int R = map->size();
	int C = map->at(0).size();
	bool reached_end = false;
	
	bool visited[R][C];
	for (int i=0;i<R;i++){
		for(int j=0;j<C;j++){
			visited[i][j] = false;
		}
	}

	vector<int> rorder;
	vector<int> corder;
	vector<int> prev;

	queue<int> rq;
	queue<int> cq;

	rq.push(sr);
	cq.push(sc);
	visited[sr][sc] = true;
	rorder.push_back(sr);
	corder.push_back(sc);
	prev.push_back(-1);
	int prev_num = 0;

	while(!rq.empty()){
		int r = rq.front();
		rq.pop();
		int c = cq.front();
		cq.pop();
	

		if ((r == fr) and (c == fc)){
			reached_end = true;
			break;
		}

		for (int i=0; i<4; i++){

			int rr = r + dr[i];
			int cc = c + dc[i];

			if (rr<0 or cc<0)
				continue;
			if (rr>=R or cc>=C)
				continue;
			if (visited[rr][cc])
				continue;
			// same as the traal, chooses shortest path to surround the
			// player.
			if ((map->at(rr)[cc] == '*') or (map->at(rr)[cc] == 'T'))
				continue;
			rq.push(rr);
			cq.push(cc);

			rorder.push_back(rr);
			corder.push_back(cc);
			prev.push_back(prev_num);

			visited[rr][cc] = true;
		}
		prev_num = prev_num + 1;

	}

	if (reached_end)
		{
			while (prev_num != -1){
				vector<int> node(2);
				node = {rorder[prev_num],corder[prev_num]};
				path.push_back(node);
				prev_num = prev[prev_num];
			}

			next_step.push_back(path[path.size()-2][0]);
			next_step.push_back(path[path.size()-2][1]);
		}
	else
	{
		next_step.push_back(sr);
		next_step.push_back(sc);
	}

	return next_step;
}

