#ifndef L_BLOCK_H
#define L_BLOCK_H

#include "Block.h"

class L_BLOCK:public Block{
    public:
        L_BLOCK();
        void rotateRight();
        void rotateLeft();
        void rotateUp();
        void rotateDown();
        virtual ~L_BLOCK();
};

#endif // L_BLOCK_H
