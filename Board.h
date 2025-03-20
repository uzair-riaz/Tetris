#ifndef BOARD_H
#define BOARD_H

#include "Block.h"
#include "Graphics.h"
#include "J_BLOCK.h"
#include "L_BLOCK.h"
#include "S_BLOCK.h"
#include "Z_BLOCK.h"
#include "I_BLOCK.h"
#include "O_BLOCK.h"
#include "T_BLOCK.h"

#define BOARD_HEIGHT 30							// height of the board
#define BOARD_WIDTH 15							// block of the board

class Board{
    private:
        int** _board;			                            // to hold the structure of the board
        bool firstCall;                                     // to determine whether first block is generated
		Block *ptr;								            // to control a single block on board
		Block *next;                                        // to hold the next block
		Graphics* brush;                                    // "Graphics" class pointer used for drawing
		int random;								            // to generate a random number used for generation of a random block
		int prevRand;                                       // to hold the value of previously generated random number
        enum {FREE,FIXED=3};					            // FREE determines if a certain cell on board is free and FIXED determines if its fixed
    public:
        Board();                                            // called at the time of object creation. Sets the _board pointer to NULL and constructs "brush" with received parameters
		void randomBlock();						            // generates a random block
		void nextBlock();						            // displays the next block to be generated
		void putBlock();						            // fills the corresponding cells of board array according to the block shape
		void fixBlock();						            // fixes the block after any further move is impossible
		void gravityFall();						            // simulates gravity. Any block cell hovering will automatically fall down to the lowest FIXED cell
		void draw(SDL_Window*,SDL_Renderer*,int) const;     // draws the board array,block array and the score by passing window and renderer to brush pointer
		void updateBoard();						            // called after any further move is impossible by setting the block cells to FIXED
		int clearLine();						            // called after fixing the block to check if the latest block caused the line to fill. If it did, the line cells are FREE-d and line number is sent to "freeLine"
		void fillLine(int);						            // called inside clearLine. Accepts a line number and moves all the lines down from that point upwards
		bool isMovePossible() const;			            // checks if any further move is possible for a block. Returns false if it is not
		bool isRotationPossible(int**,int,int,int);         // checks if rotation is possible every time rotate button is pressed. Returns false if it is not
		bool isTopFilled() const;				            // checks if the top row is filled. Returns true even if a single cell is filled
		bool leftObstacleCheck() const;			            // returns true if there is a FIXED cell on the left of the block
		bool rightObstacleCheck() const;		            // returns true if there is a FIXED cell on the right of the block
		int genRandom();						            // returns a randomly generated number
		int** getBoardPtr() const;				            // returns the _board int double pointer
		Block* getBlockPtr() const;				            // returns the ptr Block pointer
		Block* getNextPtr() const;                          // returns the next Block pointer
		int getRandom();						            // returns the "random" data member
		void nullifyPtr();						            // sets the pointer to NULL
		void nullifyNext();                                 // sets the next pointer to NULL
        virtual ~Board();						            // called when "Board" object is out of scope. Destroys the object and/or pointer along with explicitly deleting _board double pointer
};

#endif // BOARD_H
