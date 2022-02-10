#include "gameEngine.h"
GameEngine::GameEngine()
{
	score = 0;
	scroll = false;
	diamonds = 0;
	alive = true;
	esc_pressed = false;
}


// method to load the map to the vector<vector<char>>
void GameEngine::loadMap()
{
	string line;
	string fileName;
	ifstream file;
	file.open(mapFile);

	if (!file)
	{
		endwin();
		throw "Wrong/Missing Map File!";
	}

	while(getline(file, line))
	{
		vector<char> row;
		for (char &c: line)
			row.push_back(c);
		map.push_back(row);
	}
} 

// method tp create the map window in ncurses
void GameEngine::createMapWindow()
{	

	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	mapWindow = newwin(map.size(),map[0].size(),5,10);

	for(int i=0;i<map.size();i++)
	{
		for(int j=0;j<map[0].size();j++)
		{
			if (map[i][j] == '*')
				mvwprintw(mapWindow, i, j, "*");
			else
				mvwprintw(mapWindow, i, j, " ");
		}
	}
}

// method to add the scroll to the game
void GameEngine::addScroll()
{
	srand((unsigned) time(0));
	int x,y;
	while (true)
	{
		x = (rand()%(map[0].size()-1)) + 1;
		y = (rand()%(map.size()-1)) + 1;
		if (map[y][x] == ' ')
		{
			map[y][x] = 'S';
			wattron(mapWindow,COLOR_PAIR(3));
			mvwprintw(mapWindow, y, x, "S");
			wattroff(mapWindow,COLOR_PAIR(3));
			break;
		}
	}

	wattron(statWindow,COLOR_PAIR(3));
	mvwprintw(statWindow,5,1,"The degree scroll");
	mvwprintw(statWindow,6,1,"has just appeared!");
	wattroff(statWindow,COLOR_PAIR(3));
}

// method to add the jewels to the game
void GameEngine::addJewels()
{
	srand((unsigned) time(0));
	int x,y;
	for (int i = 0; i<10; i++)
	{	
		while (true)
		{
			x = (rand()%(map[0].size()-1)) + 1;
			y = (rand()%(map.size()-1)) + 1;
			if (map[y][x] == ' ')
			{
				map[y][x] = 'J';
				wattron(mapWindow,COLOR_PAIR(2));
				mvwprintw(mapWindow, y, x, "J");
				wattroff(mapWindow,COLOR_PAIR(2));
               	break;
			}
		}
	}
}

// method to add the player to the game
void GameEngine::addPotter()
{
	srand((unsigned) time(0));
	int x,y;
	while (true)
	{
		x = (rand()%(map[0].size()-1)) + 1;
		y = (rand()%(map.size()-1)) + 1;
		if (map[y][x] == ' ')
		{
			map[y][x] = 'P';
			wattron(mapWindow, COLOR_PAIR(1));
			mvwprintw(mapWindow, y, x, "P");
			wattroff(mapWindow, COLOR_PAIR(1));
			potter = new Potter(x,y, &map, mapWindow, &score, &scroll, &diamonds);
			break;
		}
	}
}

// method to add the Traal to the game
void GameEngine::addTraal()
{
	srand((unsigned) time(0));
	int x,y;
	while (true)
	{
		x = (rand()%(map[0].size()-1)) + 1;
		y = (rand()%(map.size()-1)) + 1;
		if (map[y][x] == ' ')
		{
			map[y][x] = 'T';
			wattron(mapWindow,COLOR_PAIR(4));
			mvwprintw(mapWindow, y, x, "T");
			wattroff(mapWindow,COLOR_PAIR(4));
			traal = new Traal(x, y, &map, potter, mapWindow);
			break;
		}
	}
}

// method to add the Gnome to the game
void GameEngine::addGnome()
{
	srand((unsigned) time(0));
	int x,y;
	while (true)
	{
		x = (rand()%(map[0].size()-1)) + 1;
		y = (rand()%(map.size()-1)) + 1;
		if (map[y][x] == ' ')
		{
			map[y][x] = 'G';
			wattron(mapWindow,COLOR_PAIR(4));
			mvwprintw(mapWindow, y, x, "G");
			wattroff(mapWindow,COLOR_PAIR(4));
			gnome = new Gnome(x,y, &map, potter, mapWindow);
			break;
		}
	}

}

// method to initialize NCurses
void GameEngine::initNcurses()
{
	initscr();
	set_escdelay(0);
	noecho();
	signal (SIGWINCH, NULL);
	cbreak();
	curs_set(0);
	start_color();
	use_default_colors();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);

}

// method to start each round,
// if difficulty is Normal the two monsters will appear,
// else only the gnome will appear
void GameEngine::startRound(string difficulty)
{
	map.clear();
	loadMap();
	createMapWindow();
	addJewels();
	addPotter();
	if (difficulty == "Normal")
		addTraal();
	addGnome();
	keypad(mapWindow, true);
	refresh();
	wrefresh(mapWindow);
	bool scroll_spawned = false;
	do
	{
		potter -> calculateNextPosition();
		esc_pressed = potter->getEscPressed();
		if (difficulty == "Normal")
			traal->calculateNextPosition();
		gnome->calculateNextPosition();
		if (diamonds == 10 and !scroll_spawned)
		{
			addScroll();
			scroll_spawned = true;
		}
		wrefresh(mapWindow);
		refreshStatWindow();
	}while(potter->getAlive() and !scroll and !esc_pressed);
	clearStatWindow();
	if (!potter->getAlive())
		this->alive = false;
	delete gnome;
	if (difficulty == "Normal")
		delete traal;
	delete potter;
	scroll = false;
	scroll_spawned = false;
	diamonds = 0;
} 

// clearing stat window
void GameEngine::clearStatWindow()
{
	wattron(statWindow,COLOR_PAIR(2));
	mvwprintw(statWindow,3,2,"Diamonds:%d/10  ",0);
	wattroff(statWindow,COLOR_PAIR(2));
	mvwprintw(statWindow,5,1,"                  ");
	mvwprintw(statWindow,6,1,"                  ");
	wrefresh(statWindow);
}

// method to add text to the stat window when player dies
void GameEngine::deadStatWindow()
{
	wattron(statWindow,COLOR_PAIR(4));
	mvwprintw(statWindow,3,2,"YOU DIED!        ");
	mvwprintw(statWindow,4,2,"Gmele killed you!");
	mvwprintw(statWindow,5,2,"Press Enter to   ");
	mvwprintw(statWindow,6,2,"continue...      "); 
	wattroff(statWindow,COLOR_PAIR(4));
	wrefresh(statWindow);
	while(true){
		if (getch() == 10)
			break;
	}	
}


// method to refrest statwindow when diamonds or score change
void GameEngine::refreshStatWindow()
{
 	mvwprintw(statWindow,2,2,"Score:%d",score);

 	wattron(statWindow,COLOR_PAIR(2));
	mvwprintw(statWindow,3,2,"Diamonds:%d/10  ",diamonds);
	wattroff(statWindow,COLOR_PAIR(2));

	wrefresh(statWindow);
}


// method to create statwindow
void GameEngine::createStatWindow()
{
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	statWindow = newwin(10,20,5,10+map[0].size());
	wborder(statWindow, 0, 0, 0, 0, 0, 0, 0, 0);
	mvwprintw(statWindow,0,2,"Run Potter Run!");
	mvwprintw(statWindow,2,2,"Score:%d",score);
	wattron(statWindow,COLOR_PAIR(2));
	mvwprintw(statWindow,3,2,"Diamonds:%d/10  ",diamonds);
	wattroff(statWindow,COLOR_PAIR(2));
	refresh(); 
	wrefresh(statWindow);
}

// method to start the game when chosen by the menu
void GameEngine::startGame(string difficulty)
{

	loadMap();
	createStatWindow();

	// the game keeps going until player dies or escape is pressed
	while(alive and !esc_pressed){
		startRound(difficulty);
	}

	if (!esc_pressed)
		deadStatWindow();
	werase(statWindow);
	werase(mapWindow);
	wrefresh(statWindow);
	wrefresh(mapWindow);
	delwin(statWindow);
	delwin(mapWindow);

	// when escape is pressed there is no need to get the score
	if (!esc_pressed){
		string name;
		name = getName();
		highscore<<name<<score;
		highscore.saveHighScores(scoreFile);
	}

	score = 0;
	alive = true;
	esc_pressed = false;	

}


// method to show the main menu and its options
string GameEngine::startMenu()
{

	
	menuWindow = newwin(10,12,10,10);
	wborder(menuWindow, 0, 0, 0, 0, 0, 0, 0, 0);
	mvwprintw(menuWindow,0,3," Menu ");
	refresh() ;
	wrefresh(menuWindow);

	string choices[3] = {"Start Game", "HighScores", "Exit"};
	int choice;
	int highlight = 0;
	keypad(menuWindow, true);

	while(true)
	{
		for(int i=0; i<3; i++)
		{
			if(i == highlight)
				wattron(menuWindow, A_REVERSE);
			mvwprintw(menuWindow, i+1, 1, choices[i].c_str());
			wattroff(menuWindow, A_REVERSE);
		}

		choice = wgetch(menuWindow);

		switch(choice)
		{
			case KEY_UP:
				highlight--;
				if(highlight == -1)
					highlight = 0;
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight == 3)
					highlight = 2;
				break;
			default:
				break;
		}
		if (choice == 10)
			break;
	}
	werase(menuWindow);
	wrefresh(menuWindow);
	return choices[highlight];
}


// when the game starts, the player can choose difficulty
string GameEngine::startDifficultyMenu()
{

	
	difficultyWindow = newwin(5,20,10,10);
	wborder(difficultyWindow, 0, 0, 0, 0, 0, 0, 0, 0);
	mvwprintw(difficultyWindow,0,3," Difficulty ");
	refresh() ;
	wrefresh(difficultyWindow);

	string choices[2] = {"Easy", "Normal"};
	int choice;
	int highlight = 0;
	keypad(difficultyWindow, true);

	while(true)
	{
		for(int i=0; i<2; i++)
		{
			if(i == highlight)
				wattron(difficultyWindow, A_REVERSE);
			mvwprintw(difficultyWindow, i+1, 1, choices[i].c_str());
			wattroff(difficultyWindow, A_REVERSE);
		}

		choice = wgetch(difficultyWindow);

		switch(choice)
		{
			case KEY_UP:
				highlight--;
				if(highlight == -1)
					highlight = 0;
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight == 2)
					highlight = 1;
				break;
			default:
				break;
		}
		if (choice == 10)
			break;
	}
	werase(difficultyWindow);
	wrefresh(difficultyWindow);
	return choices[highlight];
}


// initilization method for the GameEngine, everything happens in here
void GameEngine::Init(string _mapFile,string _scoreFile)
{
	mapFile = _mapFile;
	scoreFile = _scoreFile;
	initNcurses();
	highscore.loadHighScores(scoreFile);
	string choice;
	while(choice != "Exit")
	{
		choice = startMenu();
		if(choice == "Start Game")
		{
			startGame(startDifficultyMenu());
		}else if (choice == "HighScores")
		{
			highscore.showHighScores();
		}
	}
	endwin();

}


// show the window to get the name of the player like an arcade game
string GameEngine::getName()
{
	nameWindow = newwin(5,30,10,10);
	wborder(nameWindow, 0, 0, 0, 0, 0, 0, 0, 0);
	mvwprintw(nameWindow,1,1,"Score: %d",score);
	mvwprintw(nameWindow,2,1,"Enter name:");
	mvwprintw(nameWindow,3,1,"Press ENTER to continue...");
	wrefresh(nameWindow);
	refresh();

	string name;
	int position = 13;
	wattron(nameWindow, A_REVERSE);
	mvwprintw(nameWindow, 2, position," ");
	wattroff(nameWindow, A_REVERSE);
	int choice;
	char letter;
	while(true)
	{
		choice = wgetch(nameWindow);
		if(position != 23)
			{
				if(isalpha(choice))
				{
					letter = choice;
					string printableS(1,letter);
					name.push_back(letter);
					mvwprintw(nameWindow, 2, position,printableS.c_str());
					position = position + 1;
					wattron(nameWindow, A_REVERSE);
					mvwprintw(nameWindow, 2, position," ");
					wattroff(nameWindow, A_REVERSE);
				}
			}

		if (choice==10)
			break;
	}

	if (name.size()< 10)
	{
		int i = name.length() -1;
		for(i;i<9;i++)
		{
			name = name + " ";
		}
	}

	werase(nameWindow);
	wrefresh(nameWindow);
	delwin(nameWindow);
	
	return name;
}

