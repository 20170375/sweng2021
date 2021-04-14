#include "CTetris.h"

void CTetris::init(int **setOfBlockArrays, int blockTypes, int blockDegrees) {
    Tetris::init(setOfBlockArrays, blockTypes, blockDegrees);
    setOfCBlockObjects = new int*[nBlockTypes];
    for(int y=0; y<nBlockTypes; y++)
        setOfCBlockObjects[y] = new int[nBlockDegrees];
    
    for(int i=0; i<nBlockTypes; i++){
        for(int j=0; j<nBlockDegrees; j++){
            Matrix obj = Matrix(setOfBlockArrays[i][j]);
            obj.mulc(i+1);
            setOfCBlockObjects[i][j] = obj;
        }
    }
}

CTetris::CTetris(int dy, int dx) {
    Tetris::Tetris(dy, dx);
    arrayScreen = createArrayScreen();
    iCscreen = Matrix(arrayScreen);
    oCscreen = Matrix(iCscreen);
}

int CTetris::accept(char key) {
    if(key>='0' && key<='6'){
        if(justStarted == false)
            deleteFullLines();
        iCscreen = Matrix(oCscreen);
    }

    state = Tetris::accept(key);

    currCBlk = setOfCBlockObjects[idxBlockType][idxBlockDegree];
    tempBlk = iCscreen.clip(top, left, top+currCBlk.get_dy(), left+currCBlk.get_dx());
    tempBlk = tempBlk + currCBlk;

    oCscreen = Matrix(iCscreen);
    oCscreen.paste(tempBlk, top, left);
}

void CTetris::deleteFullLines() {
    int **array = oScreen.get_array();
        
    for(int y=oScreen.get_dy()-iScreenDw-1; y>=0; y--) {
        bool isFull = true;

        for(int x=iScreenDw; x<oScreen.get_dx()-iScreenDw; x++) {
            if(array[y][x] == 0){
                isFull = false;
                break;
            }
        }
        if(isFull) {
            for(int line=y; line>0; line--) {
                for(int x=iScreenDw; x<oScreen.get_dx()-iScreenDw; x++)
                    array[line][x] = array[line-1][x];
            }
            for(int x=iScreenDw; x<oScreen.get_dx()-iScreenDw; x++)
                array[0][x] = 0;
            oScreen = Matrix(array);
            oCscreen = Matrix(oScreen);
            return deleteFullLines();
        }
    }

    return;
}