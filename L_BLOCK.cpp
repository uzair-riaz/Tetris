#include "L_BLOCK.h"

L_BLOCK::L_BLOCK(){
    rotateRight();
}

L_BLOCK::~L_BLOCK(){
    //dtor
}

void L_BLOCK::rotateRight(){
    initBlock();
    _block[1][2]=1;
    _block[2][2]=2;
    _block[3][2]=1;
    _block[3][3]=1;
}

void L_BLOCK::rotateLeft(){
    initBlock();
    _block[1][1]=1;
    _block[1][2]=1;
    _block[2][2]=2;
    _block[3][2]=1;
}

void L_BLOCK::rotateUp(){
    initBlock();
    _block[2][1]=1;
    _block[2][2]=2;
    _block[2][3]=1;
    _block[1][3]=1;
}

void L_BLOCK::rotateDown(){
    initBlock();
    _block[2][1]=1;
    _block[2][2]=2;
    _block[2][3]=1;
    _block[3][1]=1;
}
