#include "I_BLOCK.h"

I_BLOCK::I_BLOCK(){
    rotateUp();
}

I_BLOCK::~I_BLOCK(){
    //dtor
}

void I_BLOCK::rotateRight(){
    initBlock();
    _block[2][1]=1;
    _block[2][2]=2;
    _block[2][3]=1;
    _block[2][4]=1;
}

void I_BLOCK::rotateLeft(){
    initBlock();
    _block[2][0]=1;
    _block[2][1]=1;
    _block[2][2]=2;
    _block[2][3]=1;
}

void I_BLOCK::rotateDown(){
    initBlock();
    _block[1][2]=1;
    _block[2][2]=2;
    _block[3][2]=1;
    _block[4][2]=1;
}

void I_BLOCK::rotateUp(){
    initBlock();
    _block[0][2]=1;
    _block[1][2]=1;
    _block[2][2]=2;
    _block[3][2]=1;

}
