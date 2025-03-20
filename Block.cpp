#include "Block.h"

Block::Block():_xPos(0),_yPos(0){
	_block=new int*[BLOCK_HEIGHT];
	for(int i=0;i<BLOCK_HEIGHT;i++){
		_block[i]=new int[BLOCK_WIDTH];
	}
}

Block::~Block(){
	for(int i=0;i<BLOCK_HEIGHT;i++){
		delete [] _block[i];
	}
	delete [] _block;
}

int** Block::getBlock() const{
	return _block;
}

int Block::get_xPos() const{
	return _xPos;
}

int Block::get_yPos() const{
	return _yPos;
}

void Block::set_xPos(int x){
	_xPos=x;
}

void Block::set_yPos(int y){
	_yPos=y;
}

void Block::initBlock(){
    for(int i=0;i<BLOCK_HEIGHT;i++){
        for(int j=0;j<BLOCK_WIDTH;j++){
            _block[i][j]=0;
        }
    }
}

int Block::leftCheck() const{
	for(int j=0;j<BLOCK_WIDTH;j++){
		for(int i=0;i<BLOCK_HEIGHT;i++){
			if(_block[i][j]!=0)
				return j;
		}
	}
}

int Block::rightCheck() const{
	for(int j=BLOCK_WIDTH-1;j>=0;j--){
		for(int i=0;i<BLOCK_HEIGHT;i++){
			if(_block[i][j]!=0)
				return j;
		}
	}
}

int Block::upCheck() const{
	for(int i=0;i<BLOCK_HEIGHT;i++){
		for(int j=0;j<BLOCK_WIDTH;j++){
			if(_block[i][j]!=0)
				return i;
		}
	}
}

int Block::downCheck() const{
	for(int i=BLOCK_HEIGHT-1;i>=0;i--){
		for(int j=0;j<BLOCK_WIDTH;j++){
			if(_block[i][j]!=0)
				return i;
		}
	}
}

void Block::moveDown(){
	_yPos++;
}

void Block::moveLeft(){
	_xPos--;
}

void Block::moveRight(){
	_xPos++;
}
