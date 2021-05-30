#pragma once
#include "Matrix.h"

enum TetrisState { Running, NewBlock, Finished };

class Tetris {
    public:
        static int iScreenDw;
        Matrix *oScreen;
    protected:
        static int nBlockTypes;
        static int nBlockDegrees;
        static Matrix **setOfBlockObjects;
        bool justStarted;
        int idxBlockType;
        int idxBlockDegree;
        int arrayScreenDx;
        int arrayScreenDy;
        int top;
        int left;
        TetrisState state;
    private:
        int iScreenDy;
        int iScreenDx;
        int *arrayScreen;
        Matrix *currBlk;
        Matrix *tempBlk;
        Matrix *iScreen;

    public:
        Tetris(int dy, int dx);
        ~Tetris();
        static void init(int *setOfBlockArrays[], int nTypes, int nDegrees);
        TetrisState accept(char key);
    protected:
        int *createArrayScreen();
        void deleteFullLines();
};
