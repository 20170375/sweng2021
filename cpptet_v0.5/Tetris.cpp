#include "Tetris.h"

Tetris::Tetris() {
    
}

Tetris::Tetris(int dy, int dx) {
    iScreenDy = dy;
    iScreenDx = dx;
    arrayScreen = createArrayScreen();
    iScreen = Matrix(arrayScreen);
    oScreen = Matrix(iScreen);
    justStarted = true;
}

Tetris::~Tetris() {
    for(int y=0; y<nBlockTypes; y++)
        delete setOfBlockObjects[y];
    delete setOfBlockObjects;

    for(int y=0; y<arrayScreenDy; y++)
        delete arrayScreen[y];
    delete arrayScreen;
}

void Tetris::init(int **setOfBlockArrays, int blockTypes, int blockDegrees) {
    nBlockTypes = blockTypes;
    nBlockDegrees = blockDegrees;

    setOfBlockObjects = new int*[nBlockTypes];
    for(int y=0; y<nBlockTypes; y++)
        setOfBlockObjects[y] = new int[nBlockDegrees];
    
    for(int y=0; y<nBlockTypes; y++) {
        for(int x=0; x<nBlockDegrees; x++)
            setOfBlockObjects[y][x] = 0;
    }

    int arrayBlk_maxSize = 0;
    for(int i=0; i<nBlockTypes; i++) {
        if(arrayBlk_maxSize <= len(setOfBlockArrays[i][0]))
            arrayBlk_maxSize = len(setOfBlockArrays[i][0];
    }
    iScreenDw = arrayBlk_maxSize;     // larget enough to cover the largest block

    for(int i=0; i<nBlockTypes; i++) {
        for(int j=0; j<nBlockDegrees; j++)
            setOfBlockObjects[i][j] = Matrix(setOfBlockArrays[i][j]);
    }
}

int ** Tetris::createArrayScreen() {
    arrayScreenDx = iScreenDw * 2 + iScreenDx;
    arrayScreenDy = iScreenDy + iScreenDw;

    arrayScreen = new int*[arrayScreenDy];
    for(int y=0; y<arrayScreenDy; y++)
        arrayScreen[y] = new int[arrayScreenDx];
    for(int y=0; y<arrayScreenDy; y++) {
        for(int x=0; x<arrayScreenDx; x++)
            arrayScreen[y][x] = 0;
    }

    for(int y=0; y<iScreenDy; y++) {
        for(int x=0; x<iScreenDw; x++)
            arrayScreen[y][x] = 1;
        for(int x=0; x<iScreenDx; x++)
            arrayScreen[y][iScreenDw + x] = 0;
        for(int x=0; x<iScreenDw; x++)
            arrayScreen[y][iScreenDw + iScreenDx + x] = 1;
    }

    for(int y=0; y<iScreenDw; y++) {
        for(int x=0; x<arrayScreenDx; x++)
            arrayScreen[iScreenDy + y][x] = 1;
    }

    return arrayScreen;
}

int Tetris::accept(char key) {
    state = Running;

    if(key>='0' && key<='6') {
        if(justStarted == false)
            deleteFullLines();
        iScreen = Matrix(oScreen);
        idxBlockType = int(key) - '0';
        idxBlockDegree = 0;
        currBlk = setOfBlockObjects[idxBlockType][idxBlockDegree];
        top = 0;
        left = iScreenDw + iScreenDx/2 - currBlk.get_dx()/2;
        tempBlk = iScreen.clip(top, left, top+currBlk.get_dy(), left+currBlk.get_dx());
        tempBlk = tempBlk + currBlk;
        justStarted = false;
        // std::cout << std::endl; // 한줄 공백출력

        if(tempBlk.anyGreaterThan(1))
            state = Finished;
        oScreen = Matrix(iScreen);
        oScreen.paste(tempBlk, top, left);
        return state;
    }
    else if(key == 'q') {
        
    }
    else if(key == 'a') { // move left
        left -= 1;
    }
    else if(key == 'd') { // move right
        left += 1;
    }
    else if(key == 's') { // move down
        top += 1;
    }
    else if(key == 'w') { // rotate the block clockwise
        idxBlockDegree = (idxBlockDegree + 1) % nBlockDegrees;
        currBlk = setOfBlockObjects[idxBlockType][idxBlockDegree];
    }
    else if(key == ' ') { // drop the block
        while(!tempBlk.anyGreaterThan(1)) {
            top += 1;
            tempBlk = iScreen.clip(top, left, top+currBlk.get_dy(), left+currBlk.get_dx());
            tempBlk = tempBlk + currBlk;
        }
    }
    else{
        // cout << "Wrong key!!!";
    }

    tempBlk = iScreen.clip(top, left, top+currBlk.get_dy(), left+currBlk.get_dx());
    tempBlk = tempBlk + currBlk;

    if(tempBlk.anyGreaterThan(1)){   // 벽 충돌시 undo 수행
        if(key == 'a'){ // undo: move right
            left += 1;
        }
        else if(key == 'd'){ // undo: move left
            left -= 1;
        }
        else if(key == 's'){ // undo: move up
            top -= 1;
            state = NewBlock;
        }
        else if(key == 'w'){ // undo: rotate the block counter-clockwise
            idxBlockDegree = (idxBlockDegree - 1) % nBlockDegrees;
            currBlk = setOfBlockObjects[idxBlockType][idxBlockDegree];
        }
        else if(key == ' '){ // undo: move up
            top -= 1;
            state = NewBlock;
        }
        
        tempBlk = iScreen.clip(top, left, top+currBlk.get_dy(), left+self.currBlk.get_dx());
        tempBlk = tempBlk + currBlk;
    }

    oScreen = Matrix(iScreen);
    oScreen.paste(tempBlk, top, left);

    return state;
}

void Tetris::deleteFullLines() {

}