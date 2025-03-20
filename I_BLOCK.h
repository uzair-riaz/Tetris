#ifndef I_BLOCK_H
#define I_BLOCK_H

#include "Block.h"

class I_BLOCK:public Block{
    public:
        I_BLOCK();
        void rotateRight();
        void rotateLeft();
        void rotateUp();
        void rotateDown();
        virtual ~I_BLOCK();
};

#endif // I_BLOCK_H
