#ifndef T_BLOCK_H
#define T_BLOCK_H

#include "Block.h"

class T_BLOCK:public Block{
    public:
        T_BLOCK();
        void rotateRight();
        void rotateLeft();
        void rotateUp();
        void rotateDown();
        virtual ~T_BLOCK();
};

#endif // T_BLOCK_H
