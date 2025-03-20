#include "T_BLOCK.h"

T_BLOCK::T_BLOCK(){
    rotateRight();
}

T_BLOCK::~T_BLOCK(){
    //dtor
}

void T_BLOCK::rotateRight(){
    initBlock();
    _block[1][2]=1;
    _block[2][2]=2;
    _block[2][3]=1;
    _block[3][2]=1;
}

void T_BLOCK::rotateLeft(){
    initBlock();
    _block[1][2]=1;
    _block[2][2]=2;
    _block[2][1]=1;
    _block[3][2]=1;
}

void T_BLOCK::rotateUp(){
    initBlock();
    _block[2][1]=1;
    _block[2][2]=2;
    _block[2][3]=1;
    _block[1][2]=1;
}

void T_BLOCK::rotateDown(){
    initBlock();
    _block[2][1]=1;
    _block[2][2]=2;
    _block[2][3]=1;
    _block[3][2]=1;
}
