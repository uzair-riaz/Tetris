#include "J_BLOCK.h"

J_BLOCK::J_BLOCK(){
   rotateLeft();
}

J_BLOCK::~J_BLOCK(){
    //dtor
}

void J_BLOCK::rotateLeft(){
    initBlock();
    _block[1][2]=1;
    _block[2][2]=2;
    _block[3][2]=1;
    _block[3][1]=1;
}

void J_BLOCK::rotateRight(){
    initBlock();
    _block[1][3]=1;
    _block[1][2]=1;
    _block[2][2]=2;
    _block[3][2]=1;
}

void J_BLOCK::rotateUp(){
    initBlock();
    _block[2][1]=1;
    _block[2][2]=2;
    _block[2][3]=1;
    _block[1][1]=1;
}

void J_BLOCK::rotateDown(){
    initBlock();
    _block[2][1]=1;
    _block[2][2]=2;
    _block[2][3]=1;
    _block[3][3]=1;
}
