#ifndef Z_BLOCK_H
#define Z_BLOCK_H

#include "Block.h"


class Z_BLOCK:public Block{
    public:
        Z_BLOCK();
        void rotateRight();
        void rotateLeft();
        void rotateUp();
        void rotateDown();
        virtual ~Z_BLOCK();
};

#endif // Z_BLOCK_H
