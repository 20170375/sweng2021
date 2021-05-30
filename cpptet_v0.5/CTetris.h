#pragma once
#include "Tetris.h"

class CTetris : public Tetris {
    public:
        Matrix *oCScreen;
    private:
        static Matrix **setOfCBlockObjects;
        Matrix *currCBlk;
        Matrix *iCScreen;

    public:
        CTetris(int dy, int dx);
        ~CTetris();
        static void init(int *setOfBlockArrays[], int nTypes, int nDegrees);
        TetrisState accept(char key);
    private:
        void deleteFullLines();
};
