#include "gameEngine.h"
#include "highscore.h"

using namespace std;

int main(int argc, char* argv[]){

	try{
		if (argc != 3)
			{
				throw "Game requires two arguments (map file),(scores file)" ;
			}
		
		string mapFile(argv[1]);
		string scoreFile(argv[2]);

		GameEngine mazeGame;
		mazeGame.Init(mapFile,scoreFile);
	}catch(const char* msg){
		cerr << msg << endl;
	}


}