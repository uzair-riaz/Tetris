#ifndef S_BLOCK_H
#define S_BLOCK_H

#include "Block.h"


class S_BLOCK:public Block{
    public:
        S_BLOCK();
        void rotateRight();
        void rotateLeft();
        void rotateUp();
        void rotateDown();
        virtual ~S_BLOCK();
};

#endif // S_BLOCK_H
