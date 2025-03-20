#include "Board.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

Board::Board():_board(NULL),firstCall(false),ptr(NULL),random(0){
    brush=new Graphics;
    _board=new int*[BOARD_HEIGHT];
    for(int i=0;i<BOARD_HEIGHT;i++){
        _board[i]=new int[BOARD_WIDTH];
    }
    for(int i=0;i<BOARD_HEIGHT;i++){
        for(int j=0;j<BOARD_WIDTH;j++){
        	if(i==BOARD_HEIGHT-1 || j==0 || j==BOARD_WIDTH-1)
        		_board[i][j]=FIXED;
        	else
        		_board[i][j]=FREE;
        }
    }
}

Board::~Board(){
    for(int i=0;i<BOARD_HEIGHT;i++){
        delete [] _board[i];
    }
    delete [] _board;
    delete brush;
}

void Board::updateBoard(){
	for(int i=0;i<BOARD_HEIGHT-1;i++){
		for(int j=1;j<BOARD_WIDTH-1;j++){
			if(_board[i][j]!=FIXED)
				_board[i][j]=FREE;
		}
	}
}

void Board::draw(SDL_Window* win,SDL_Renderer* ren,int score) const{
	brush->draw(win,ren,_board,next->getBlock(),BOARD_HEIGHT,BOARD_WIDTH,BLOCK_HEIGHT,BLOCK_WIDTH,score);
}

int Board::genRandom(){
	time_t seconds;
	time(&seconds);
	srand((unsigned int) seconds);
	return (rand()%7+1);
}

void Board::randomBlock(){
    if(!firstCall){
        firstCall=true;
        prevRand=genRandom();
    }
    else{
        prevRand=random;
    }
    switch(prevRand){
        case 1:
            ptr=new L_BLOCK;
            break;
        case 2:
            ptr=new J_BLOCK;
            break;
        case 3:
            ptr=new S_BLOCK;
            break;
        case 4:
            ptr=new Z_BLOCK;
            break;
        case 5:
            ptr=new T_BLOCK;
            break;
        case 6:
            ptr=new I_BLOCK;
            break;
        case 7:
            ptr=new O_BLOCK;
            break;
    }
    ptr->set_xPos(BOARD_WIDTH/2);
    ptr->set_yPos(0);
}

void Board::nextBlock(){
    random=genRandom();
	switch(random){
		case 1:
			next=new L_BLOCK;
			break;
		case 2:
			next=new J_BLOCK;
			break;
		case 3:
			next=new S_BLOCK;
			break;
		case 4:
			next=new Z_BLOCK;
			break;
		case 5:
			next=new T_BLOCK;
			break;
		case 6:
			next=new I_BLOCK;
			break;
		case 7:
			next=new O_BLOCK;
			break;
	}
}

Block* Board::getBlockPtr() const{
	return ptr;
}

Block* Board::getNextPtr() const{
    return next;
}

int Board::getRandom(){
	return random;
}

void Board::putBlock(){
	for(int i=ptr->upCheck();i<=ptr->downCheck();i++){
		for(int j=ptr->leftCheck();j<=ptr->rightCheck();j++){
			if(ptr->getBlock()[i][j]!=0){
				_board[ptr->get_yPos()+i-ptr->upCheck()][ptr->get_xPos()+j-ptr->leftCheck()]=ptr->getBlock()[i][j];
			}
		}
	}
}

void Board::fixBlock(){
	for(int i=0;i<BOARD_HEIGHT-1;i++){
		for(int j=1;j<BOARD_WIDTH-1;j++){
			if(_board[i][j]!=FREE)
				_board[i][j]=FIXED;
		}
	}
}

void Board::gravityFall(){
	for(int i=BOARD_HEIGHT-2;i>=0;i--){
		for(int j=1;j<BOARD_WIDTH-1;j++){
			if(_board[i][j]!=FREE){
				for(int k=i;_board[k+1][j]!=FIXED;k++){
					_board[k+1][j]=_board[k][j];
					_board[k][j]=FREE;
				}
			}
		}
	}
}

int Board::clearLine(){
	int count,score=0;
	for(int i=BOARD_HEIGHT-2;i>=0;i--){
		count=0;
		for(int j=1;j<BOARD_WIDTH-1;j++){
			if(_board[i][j]==FREE){
				count++;
				j=BOARD_WIDTH;
			}
		}
		if(count==0){
			for(int j=1;j<BOARD_WIDTH-1;j++){
				_board[i][j]=FREE;
			}
		fillLine(i);
		score++;
		i++;
		}
	}
	return score;
}

void Board::fillLine(int lineNo){
	for(int i=lineNo;i>0;i--){
		for(int j=1;j<BOARD_WIDTH-1;j++){
			_board[i][j]=_board[i-1][j];
		}
	}
}

void Board::nullifyPtr(){
	ptr=NULL;
}

void Board::nullifyNext(){
    next=NULL;
}

bool Board::isMovePossible() const{
	for(int i=ptr->downCheck();i>=ptr->upCheck();i--){
		for(int j=ptr->leftCheck();j<=ptr->rightCheck()+1;j++){
			if(ptr->getBlock()[i][j]!=0){
				if(_board[ptr->get_yPos()+(i-ptr->upCheck())+1][ptr->get_xPos()+(j-ptr->leftCheck())]==FIXED){
					return false;
				}
			}
		}
	}
	return true;
}

bool Board::isRotationPossible(int** block,int xPos,int yPos,int rotateCount){
    Block *temp;
    switch(prevRand){
        case 1:
            temp=new L_BLOCK;
            break;
        case 2:
            temp=new J_BLOCK;
            break;
        case 3:
            temp=new S_BLOCK;
            break;
        case 4:
            temp=new Z_BLOCK;
            break;
        case 5:
            temp=new T_BLOCK;
            break;
        case 6:
            temp=new I_BLOCK;
            break;
        case 7:
            temp=new O_BLOCK;
            break;
    }
    for(int i=0;i<BLOCK_HEIGHT;i++){
        for(int j=0;j<BLOCK_WIDTH;j++){
            temp->getBlock()[i][j]=ptr->getBlock()[i][j];
        }
    }
    temp->set_xPos(ptr->get_xPos());
    temp->set_yPos(ptr->get_yPos());
    if(rotateCount==0){
        temp->rotateRight();
    }
    else if(rotateCount==1){
        temp->rotateDown();
    }
    else if(rotateCount==2){
        temp->rotateLeft();
    }
    else if(rotateCount==3){
        temp->rotateUp();
    }
    for(int i=temp->downCheck();i>=temp->upCheck();i--){
		for(int j=temp->leftCheck();j<=temp->rightCheck()+1;j++){
			if(temp->getBlock()[i][j]!=0){
				if(_board[temp->get_yPos()+(i-temp->upCheck())][temp->get_xPos()+(j-temp->leftCheck())]==FIXED){
					return false;
				}
			}
		}
	}
	return true;
}

bool Board::isTopFilled() const{
	for(int i=1;i<BOARD_WIDTH-1;i++){
		if(_board[0][i]==FIXED)
			return true;
	}
	return false;
}

int** Board::getBoardPtr() const{
	return _board;
}

bool Board::leftObstacleCheck() const{
	for(int i=ptr->upCheck();i<=ptr->downCheck();i++){
		if(_board[ptr->get_yPos()+(i-ptr->upCheck())][ptr->get_xPos()-1]==FIXED)
			return true;
	}
	return false;
}

bool Board::rightObstacleCheck() const{
	for(int i=ptr->upCheck();i<=ptr->downCheck();i++){
		if(_board[ptr->get_yPos()+(i-ptr->upCheck())][ptr->get_xPos()+(ptr->rightCheck()-ptr->leftCheck())+1]==FIXED)
			return true;
	}
	return false;
}
