#ifndef TETRIS_H
#define TETRIS_H

#include <SDL_mixer.h>
#include <iostream>
#include <fstream>
#include "Board.h"
#include "Graphics.h"

class Tetris {
	private:
	    bool quitGame;                          // to detect if the user has quit the game
	    bool soundOn;                           // to determine if the state of the sound in the game
	    bool levelEasy;                         // to determine the level of the game
	    char* playerName;                       // holds the name of the player
	    std::ofstream fileOut;                  // to save the scores and player names in an external file
	    std::ifstream fileIn;                   // to read the scores and player names from the external file
	    Mix_Music *music;                       // to play the soundtrack
		Board game;						        // to control all the aspects of a single game session
		SDL_Window *window;                     // a pointer to the window for drawing
		SDL_Renderer *renderer;                 // a pointer to the renderer that draws
		int score;						        // to store the score of the player
	public:
		Tetris(SDL_Window*,SDL_Renderer*);      // called when "Tetris" class object is created. Sets the score to 0, quitGame to false and window and renderer pointers to the received ones
		void startGame();				        // gets the game running
		void resetGame();                       // resets the game
		void setSoundOn(bool);                  // to toggle the sound on and off
		bool getSoundOn() const;                // returns whether the sound is on or not
		void setLevel(bool);                    // sets the level to either easy or hard
		bool getLevel() const;                  // returns the level of the game
		void setPlayerName(std::string name);   // sets the username data member to the received one
		void fileScorePlayerName();             // exports the score and name of the current player to an external file
		void readScorePlayerName();             // reads and prints out the score and name of every player that has played the game so far
		~Tetris();						        // destroys the "Tetris" class object
};

#endif // TETRIS_H
