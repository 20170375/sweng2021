#pragma once
#include "Matrix.h"

enum TetrisState { Running, NewBlock, Finished };

class Tetris {
    public:
        static int nBlockTypes;
        static int nBlockDegrees;
        static int iScreenDw;
        static Matrix **setOfBlockObjects;
        bool justStarted;
        int iScreenDy;
        int iScreenDx;
        int idxBlockType;
        int idxBlockDegree;
        int arrayScreenDx;
        int arrayScreenDy;
        int top;
        int left;
        int state;
        int *arrayScreen;
        Matrix *currBlk;
        Matrix *tempBlk;
        Matrix *iScreen;
        Matrix *oScreen;

        Tetris(int dy, int dx);
        ~Tetris();
        static void init(int *setOfBlockArrays[], int nTypes, int nDegrees);
        int *createArrayScreen();
        int accept(char key);
        void deleteFullLines();
};
