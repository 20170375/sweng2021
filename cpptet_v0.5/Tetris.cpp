#include "Tetris.h"
#include <cmath>

int Tetris::nBlockTypes;
int Tetris::nBlockDegrees;
int Tetris::iScreenDw;
Matrix **Tetris::setOfBlockObjects;

Tetris::Tetris(int dy, int dx) {
    iScreenDy = dy;
    iScreenDx = dx;
    currBlk = new Matrix();
    tempBlk = new Matrix();
    iScreen = new Matrix(createArrayScreen(), arrayScreenDy, arrayScreenDx);
    oScreen = new Matrix(iScreen);
    justStarted = true;
}

Tetris::~Tetris() {
    for(int i=0; i<nBlockTypes; i++)
        delete [] setOfBlockObjects[i];
    delete [] setOfBlockObjects;
    delete [] arrayScreen;
    delete currBlk;
    delete tempBlk;
    delete iScreen;
    delete oScreen;
}

void Tetris::init(int *setOfBlockArrays[], int nTypes, int nDegrees) {
    nBlockTypes = nTypes;
    nBlockDegrees = nDegrees;
    setOfBlockObjects = new Matrix*[nBlockTypes];
    for(int y=0; y<nBlockTypes; y++)
        setOfBlockObjects[y] = new Matrix[nBlockDegrees];

    int maxSize = 0;
    int size[nBlockTypes];
    for(int i=0; i<nBlockTypes; i++)
        size[i] = 0;

    for(int i=0; i<nBlockTypes; i++) {
        for(int j=0; setOfBlockArrays[i * nBlockDegrees][j]!=-1; j++)
            size[i]++;
        size[i] = (int)sqrt(size[i]);
        if(maxSize <= size[i])
            maxSize = size[i];
    }

    for(int i=0; i<nBlockTypes; i++) {
        for(int j=0; j<nBlockDegrees; j++)
            setOfBlockObjects[i][j] = Matrix(setOfBlockArrays[i * nBlockDegrees + j], size[i], size[i]);
    }
    iScreenDw = maxSize;     // large enough to cover the largest block
}

int *Tetris::createArrayScreen() {
    arrayScreenDy = iScreenDy + iScreenDw;
    arrayScreenDx = iScreenDx + iScreenDw * 2;

    arrayScreen = new int[arrayScreenDy * arrayScreenDx];
    for(int y=0; y<iScreenDy; y++) {
        for(int x=0; x<iScreenDw; x++)
            arrayScreen[y * arrayScreenDx + x] = 1;
        for(int x=0; x<iScreenDx; x++)
            arrayScreen[y * arrayScreenDx + iScreenDw + x] = 0;
        for(int x=0; x<iScreenDw; x++)
            arrayScreen[y * arrayScreenDx + iScreenDw + iScreenDx + x] = 1;
    }

    for(int y=0; y<iScreenDw; y++)
        for(int x=0; x<arrayScreenDx; x++)
            arrayScreen[(iScreenDy + y) * arrayScreenDx + x] = 1;

    return arrayScreen;
}

TetrisState Tetris::accept(char key) {
    state = Running;

    if(key>='0' && key<=('0' + nBlockTypes - 1)) {
        if(justStarted == false)
            deleteFullLines();
        *iScreen = Matrix(oScreen);
        idxBlockType = int(key) - '0';
        idxBlockDegree = 0;
        *currBlk = setOfBlockObjects[idxBlockType][idxBlockDegree];
        top = 0;
        left = iScreenDw + iScreenDx/2 - currBlk->get_dx()/2;
        tempBlk = iScreen->clip(top, left, top+currBlk->get_dy(), left+currBlk->get_dx());
        tempBlk = tempBlk->add(currBlk);
        justStarted = false;
        // std::cout << std::endl; // 한줄 공백출력

        if(tempBlk->anyGreaterThan(1))
            state = Finished;
        *oScreen = Matrix(iScreen);
        oScreen->paste(tempBlk, top, left);
        return state;
    }
    else if(key == 'q') { }
    else if(key == 'a') { left -= 1; }
    else if(key == 'd') { left += 1; }
    else if(key == 's') { top += 1; }
    else if(key == 'w') { // rotate the block clockwise
        idxBlockDegree = (idxBlockDegree + 1) % nBlockDegrees;
        *currBlk = setOfBlockObjects[idxBlockType][idxBlockDegree];
    }
    else if(key == ' ') { // drop the block
        while(!tempBlk->anyGreaterThan(1)) {
            top += 1;
            tempBlk = iScreen->clip(top, left, top+currBlk->get_dy(), left+currBlk->get_dx());
            tempBlk = tempBlk->add(currBlk);
        }
    }
    else{ cout << "Wrong key!!!" << endl; }

    tempBlk = iScreen->clip(top, left, top+currBlk->get_dy(), left+currBlk->get_dx());
    tempBlk = tempBlk->add(currBlk);

    if(tempBlk->anyGreaterThan(1)) {   // 벽 충돌시 undo 수행
        if(key == 'a') { left += 1; } // undo: move right
        else if(key == 'd') { left -= 1; } // undo: move left
        else if(key == 's') { // undo: move up
            top -= 1;
            state = NewBlock;
        }
        else if(key == 'w') { // undo: rotate the block counter-clockwise
            if(idxBlockDegree > 1)
                idxBlockDegree = (idxBlockDegree - 1) % nBlockDegrees;
            else
                idxBlockDegree = (idxBlockDegree + nBlockDegrees - 1) % nBlockDegrees;
            *currBlk = setOfBlockObjects[idxBlockType][idxBlockDegree];
        }
        else if(key == ' ') { // undo: move up
            top -= 1;
            state = NewBlock;
        }
        
        tempBlk = iScreen->clip(top, left, top+currBlk->get_dy(), left+currBlk->get_dx());
        tempBlk = tempBlk->add(currBlk);
    }

    *oScreen = Matrix(iScreen);
    oScreen->paste(tempBlk, top, left);

    return state;
}

void Tetris::deleteFullLines() {

}