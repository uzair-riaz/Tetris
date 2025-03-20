#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <windows.h>
#include "Graphics.h"

#define BLOCK_HEIGHT 5							        // number of rows of the block array
#define BLOCK_WIDTH 5							        // number of columns of the block array

class Block{
    protected:
        int** _block;							        // to store the structure of a block
        int _xPos,_yPos;						        // to store the current indices of a block on board
    public:
        Block();								        // called at the time of object creation. Sets _block pointer to NULL, _xPos and _yPos to 0
        virtual void rotateRight()=0;			        // pure virtual function overridden in corresponding blocks. rotates the block on the right
		virtual void rotateLeft()=0;			        // pure virtual function overridden in corresponding blocks. rotates the block on the left
		virtual void rotateUp()=0;				        // pure virtual function overridden in corresponding blocks. rotates the block up
        virtual void rotateDown()=0;			        // pure virtual function overridden in corresponding blocks. rotates the block down
        void initBlock();						        // sets all the cells of block shape to 0
		void moveRight();						        // increments _xPos to move the block right on the board
		void moveLeft();						        // decrements _xPos to move the block left on the board
		void moveDown();						        // increments _yPos to constantly move the block down on the board
		int leftCheck() const;					        // returns the column number for the first non-zero value encountered from left in the _block array
		int rightCheck() const;					        // returns the column number for the first non-zero value encountered from right in the _block array
		int upCheck() const;					        // returns the row number for the first non-zero value encountered from up in the _block array
		int downCheck() const;					        // returns the row number for the first non-zero value encountered from down in the _block array
        int** getBlock() const;					        // returns the _block double pointer
        int get_xPos() const;					        // returns the _xPos value
        int get_yPos() const;					        // returns the _yPos value
        void set_xPos(int);						        // sets the _xPos equal to the received parameter
        void set_yPos(int);						        // sets the _yPos equal to the received parameter
        virtual ~Block();						        // destroys the object and/or pointer along with explicitly deleting _block double pointer
};

#endif
