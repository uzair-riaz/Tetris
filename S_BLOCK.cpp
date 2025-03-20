#include "S_BLOCK.h"

S_BLOCK::S_BLOCK(){
    rotateUp();
}

S_BLOCK::~S_BLOCK(){
    //dtor
}

void S_BLOCK::rotateRight(){
    initBlock();
    _block[1][2]=1;
    _block[2][2]=2;
    _block[2][3]=1;
    _block[3][3]=1;
}

void S_BLOCK::rotateLeft(){
    initBlock();
    _block[1][1]=1;
    _block[2][2]=2;
    _block[2][1]=1;
    _block[3][2]=1;
}

void S_BLOCK::rotateUp(){
    initBlock();
    _block[2][2]=2;
    _block[3][2]=1;
    _block[3][1]=1;
    _block[2][3]=1;
}

void S_BLOCK::rotateDown(){
    initBlock();
    _block[3][2]=2;
    _block[2][2]=1;
    _block[3][1]=1;
    _block[2][3]=1;
}
