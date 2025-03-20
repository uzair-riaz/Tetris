#include "Z_BLOCK.h"

Z_BLOCK::Z_BLOCK(){
   rotateUp();
}

Z_BLOCK::~Z_BLOCK()
{
    //dtor
}

void Z_BLOCK::rotateRight(){
    initBlock();
    _block[2][2]=2;
    _block[1][3]=1;
    _block[3][2]=1;
    _block[2][3]=1;
}

void Z_BLOCK::rotateLeft(){
    initBlock();
    _block[2][2]=2;
    _block[1][2]=1;
    _block[2][1]=1;
    _block[3][1]=1;
}

void Z_BLOCK::rotateUp(){
    initBlock();
    _block[2][2]=2;
    _block[1][1]=1;
    _block[1][2]=1;
    _block[2][3]=1;
}

void Z_BLOCK::rotateDown(){
    initBlock();
    _block[2][2]=2;
    _block[2][1]=1;
    _block[3][2]=1;
    _block[3][3]=1;
}
