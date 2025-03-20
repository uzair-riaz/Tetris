#ifndef J_BLOCK_H
#define J_BLOCK_H

#include "Block.h"

class J_BLOCK:public Block{
    public:
        J_BLOCK();
        void rotateRight();
        void rotateLeft();
        void rotateUp();
        void rotateDown();
        virtual ~J_BLOCK();
};

#endif // J_BLOCK_H
