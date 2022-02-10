#include "highscore.h"

HighScore::HighScore()
{
	//initialization
	tmpName = "          ";
	tmpScore = 0;

	for (int i=0;i<5;i++)
	{
		names.push_back(tmpName);
		scores.push_back(tmpScore);
	}
}


HighScore& HighScore::operator<<(string _name)
{
	tmpName = _name;
	return *this;
}

void HighScore::operator<<(int _score)
{
	tmpScore = _score;
	addToTable();
}


void HighScore::addToTable()
{
	scores.push_back(tmpScore);
	names.push_back(tmpName);
	int N = names.size();
	int tmpS;
	string tmpN;
	// sorting table
	for (int i = 0; i<N-1; i++)
	{
		for(int j=0; j<N-i-1;j++)
		{
			if (scores[j] < scores[j+1])
			{
				tmpS = scores[j];
				tmpN = names[j];

				scores[j] = scores[j+1];
				names[j] = names[j+1];
				scores[j+1] = tmpS;
				names[j+1] = tmpN;
			}
		}
	}

	// removing last element
	scores.pop_back();
	names.pop_back();

  }


void HighScore::showHighScores()
{
	
	WINDOW* scoreWindow = newwin(20,30,10,10);
	wborder(scoreWindow, 0, 0, 0, 0, 0, 0, 0, 0);
	mvwprintw(scoreWindow,0,5," HIGHSCORES ");
	wrefresh(scoreWindow);
	refresh();
	int line = 1;
	for (int i=0;i<5;i++)
	{
		mvwprintw(scoreWindow,line,1,"%d. %s %d",line,names[i].c_str(),scores[i]);
		line = line + 1;
	}
	mvwprintw(scoreWindow,18,1,"Press ENTER to continue...");
	int key;
	while(1)
	{
		key = wgetch(scoreWindow);
		if (key == 10)
		{
			break;
		}
	}

	werase(scoreWindow);
	wrefresh(scoreWindow);
	delwin(scoreWindow);
}


void HighScore::loadHighScores(string fileName)
{
	string name;
	int score;
	ifstream infile;
	infile.open(fileName, ios::binary | ios::out);
	if(infile){
		for (int i=0; i<5; i++)
		{
			char* buff;
			name = "";
			score = 0;
			infile.read(reinterpret_cast<char *>(&score), sizeof(int));
			scores[i] = score;
			buff = new char[10];
			infile.read(buff, 10);
			name.append(buff, 10);
			names[i] = name;
			delete[] buff;
		}
	}else{
		infile.close();
		endwin();
		throw "Wrong/Missing Scores file";
	}
}


void HighScore::saveHighScores(string fileName)
{
	ofstream outfile;
	outfile.open(fileName, ios::binary | ios::out);

	if(outfile)
	{
		for (int i=0; i<5; i++)
		{
			outfile.write(reinterpret_cast<char *>(&scores[i]), sizeof(int));
			outfile.write(names[i].c_str(), 10);
		}
		outfile.flush();
		outfile.close();
	}else
		{
			outfile.close();
			endwin();
			throw "Wrong/Missing Scores file";
		}
}