#include "Tetris.h"

Tetris::Tetris(SDL_Window* win,SDL_Renderer* ren):quitGame(false),soundOn(true),levelEasy(true),playerName(NULL),music(NULL),window(win),renderer(ren),score(0){
    fileOut.open("Player Data.txt",std::ios::app);
}

Tetris::~Tetris(){
    fileOut.close();
}

void Tetris::startGame(){
    resetGame();
	while(!game.isTopFilled() && !quitGame){
        SDL_Event event;
        bool dropDown=false;
		int rotateCount=0;
		game.randomBlock();
		game.nextBlock();
		game.draw(window,renderer,score);
		while(game.isMovePossible() && !quitGame){
			game.updateBoard();
			game.getBlockPtr()->moveDown();
			game.putBlock();
			if(!dropDown)
			game.draw(window,renderer,score);
			if(GetAsyncKeyState(VK_LEFT)){
				if(!game.leftObstacleCheck())
					game.getBlockPtr()->moveLeft();
			}
			if(GetAsyncKeyState(VK_RIGHT)){
				if(!game.rightObstacleCheck())
					game.getBlockPtr()->moveRight();
			}
			if(GetAsyncKeyState(VK_SPACE)){
				if(rotateCount==0){
					if(game.isRotationPossible(game.getBlockPtr()->getBlock(),game.getBlockPtr()->get_xPos(),game.getBlockPtr()->get_yPos(),rotateCount)){
                        game.getBlockPtr()->rotateRight();
                        rotateCount++;
					}
				}
				else if(rotateCount==1){
					if(game.isRotationPossible(game.getBlockPtr()->getBlock(),game.getBlockPtr()->get_xPos(),game.getBlockPtr()->get_yPos(),rotateCount)){
                        game.getBlockPtr()->rotateDown();
                        rotateCount++;
					}
				}
				else if(rotateCount==2){
					if(game.isRotationPossible(game.getBlockPtr()->getBlock(),game.getBlockPtr()->get_xPos(),game.getBlockPtr()->get_yPos(),rotateCount)){
                        game.getBlockPtr()->rotateLeft();
                        rotateCount++;
					}
				}
				else if(rotateCount==3){
					if(game.isRotationPossible(game.getBlockPtr()->getBlock(),game.getBlockPtr()->get_xPos(),game.getBlockPtr()->get_yPos(),rotateCount)){
                        game.getBlockPtr()->rotateUp();
                        rotateCount=0;
					}
				}
			}
			if(GetAsyncKeyState(VK_DOWN))
				dropDown=true;

            while(SDL_PollEvent(&event)){
                switch(event.type){
                case SDL_QUIT:
                    quitGame=true;
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym==SDLK_ESCAPE)
                        quitGame=true;
                    break;
                }
            }
		}
		game.updateBoard();
		game.putBlock();
		game.fixBlock();
		if(levelEasy)game.gravityFall();
		score+=10*game.clearLine();
		if(!quitGame)game.draw(window,renderer,score);
		delete game.getBlockPtr();
		delete game.getNextPtr();
		game.nullifyPtr();
		game.nullifyNext();
	}
	if(!quitGame && soundOn){
        music=Mix_LoadMUS("GameOver.wav");
        Mix_PlayMusic(music,-1);
        SDL_Delay(3000);
	}
	Mix_FreeMusic(music);
	music=NULL;
	fileScorePlayerName();
	delete [] playerName;
}

void Tetris::resetGame(){
    score=0;
    if(soundOn){
        Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,1,2048);
        music=Mix_LoadMUS("Tetris.wav");
        Mix_PlayMusic(music,-1);
    }
    quitGame=false;
    for(int i=0;i<BOARD_HEIGHT;i++){
        for(int j=0;j<BOARD_WIDTH;j++){
            if(i==BOARD_HEIGHT-1 || j==0 || j==BOARD_WIDTH-1)
                game.getBoardPtr()[i][j]=3;
            else
                game.getBoardPtr()[i][j]=0;
        }
    }
    if(game.getBlockPtr()!=NULL){
        delete game.getBlockPtr();
        game.nullifyPtr();
    }
}

void Tetris::fileScorePlayerName(){
    fileOut << std::endl << "\t\t\t\t" << playerName << "\t\t\t\t\t\t" << score << std::endl;
}

void Tetris::readScorePlayerName(){
    fileIn.open("Player Data.txt");
    fileIn.close();
}

void Tetris::setPlayerName(std::string name){
    playerName=new char[name.length()+1];
    strcpy(playerName,name.c_str());
}

void Tetris::setSoundOn(bool on){
    soundOn=on;
}

bool Tetris::getSoundOn() const{
    return soundOn;
}

void Tetris::setLevel(bool level){
    levelEasy=level;
}

bool Tetris::getLevel() const{
    return levelEasy;
}
