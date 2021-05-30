#pragma once
#include "Tetris.h"

class CTetris : public Tetris {
    public:
        static Matrix **setOfCBlockObjects;
        Matrix *currCBlk;
        Matrix *iCScreen;
        Matrix *oCScreen;

        CTetris(int dy, int dx);
        ~CTetris();
        static void init(int *setOfBlockArrays[], int nTypes, int nDegrees);
        TetrisState accept(char key);
        void deleteFullLines();
};
