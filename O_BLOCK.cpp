#include "O_BLOCK.h"

O_BLOCK::O_BLOCK(){
    constState();
}

O_BLOCK::~O_BLOCK(){
    //dtor
}

void O_BLOCK::constState(){
    initBlock();
    _block[2][2]=2;
    _block[2][3]=1;
    _block[3][2]=1;
    _block[3][3]=1;
}

void O_BLOCK::rotateRight(){
    constState();
}

void O_BLOCK::rotateLeft(){
    constState();
}

void O_BLOCK::rotateUp(){
    constState();
}

void O_BLOCK::rotateDown(){
    constState();
}
