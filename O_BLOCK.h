#ifndef O_BLOCK_H
#define O_BLOCK_H

#include "Block.h"


class O_BLOCK:public Block{
    public:
        O_BLOCK();
        void constState();
        void rotateRight();
        void rotateLeft();
        void rotateUp();
        void rotateDown();
        virtual ~O_BLOCK();
};

#endif // O_BLOCK_H
