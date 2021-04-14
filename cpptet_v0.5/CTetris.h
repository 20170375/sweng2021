#pragma once
#include "Tetris.h"

class CTetris : public Tetris {
    private:
        static Matrix **setOfCBlockObjects;
        Matrix currCBlk;
        Matrix iCscreen;
        Matrix oCscreen;
    public:
        CTetris(int dy, int dx);
        ~CTetris();
        void CTetris::init(int **setOfBlockArrays, int blockTypes, int blockDegrees);
        int CTetris::accept(char key);
        void CTetris::deleteFullLines();
};
