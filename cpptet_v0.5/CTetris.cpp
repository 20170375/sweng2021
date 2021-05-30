#include "CTetris.h"
#include <cmath>

Matrix **CTetris::setOfCBlockObjects;

void CTetris::init(int *setOfBlockArrays[], int nTypes, int nDegrees) {
    Tetris::init(setOfBlockArrays, nTypes, nDegrees);
    setOfCBlockObjects = new Matrix*[nBlockTypes];
    for(int y=0; y<nBlockTypes; y++)
        setOfCBlockObjects[y] = new Matrix[nBlockDegrees];
    
    int size[nBlockTypes];
    for(int i=0; i<nBlockTypes; i++)
        size[i] = 0;

    for(int i=0; i<nBlockTypes; i++) {
        for(int j=0; setOfBlockArrays[i * nBlockDegrees][j]!=-1; j++)
            size[i]++;
        size[i] = (int)sqrt(size[i]);
    }

    for(int i=0; i<nBlockTypes; i++){
        for(int j=0; j<nBlockDegrees; j++){
            Matrix obj = Matrix(setOfBlockArrays[i * nBlockDegrees + j], size[i], size[i]);
            obj.mulc(i+1);
            setOfCBlockObjects[i][j] = obj;
        }
    }
}

CTetris::CTetris(int dy, int dx) : Tetris(dy, dx){
    currCBlk = new Matrix();
    iCScreen = new Matrix(createArrayScreen(), arrayScreenDy, arrayScreenDx);
    oCScreen = new Matrix(iCScreen);
}

CTetris::~CTetris() {
    for(int i=0; i<nBlockTypes; i++)
        delete [] setOfCBlockObjects[i];
    delete [] setOfCBlockObjects;
    delete currCBlk;
    delete iCScreen;
    delete oCScreen;
}

TetrisState CTetris::accept(char key) {
    if(key>='0' && key<=('0' + nBlockTypes - 1)){
        if(justStarted == false)
            deleteFullLines();
        *iCScreen = Matrix(oCScreen);
    }

    state = Tetris::accept(key);

    *currCBlk = setOfCBlockObjects[idxBlockType][idxBlockDegree];
    Matrix* tempCBlk = iCScreen->clip(top, left, top+currCBlk->get_dy(), left+currCBlk->get_dx());
    tempCBlk = tempCBlk->add(currCBlk);

    *oCScreen = Matrix(iCScreen);
    oCScreen->paste(tempCBlk, top, left);
    return state;
}

void CTetris::deleteFullLines() {
    int **array = oScreen->get_array();
    int **cArray = oCScreen->get_array();
        
    for(int y=oScreen->get_dy()-iScreenDw-1; y>=0; y--) {
        bool isFull = true;

        for(int x=iScreenDw; x<oScreen->get_dx()-iScreenDw; x++) {
            if(array[y][x] == 0){
                isFull = false;
                break;
            }
        }
        if(isFull) {
            for(int line=y; line>0; line--) {
                for(int x=iScreenDw; x<oScreen->get_dx()-iScreenDw; x++) {
                    array[line][x] = array[line-1][x];
                    cArray[line][x] = cArray[line-1][x];
                }
            }
            for(int x=iScreenDw; x<oScreen->get_dx()-iScreenDw; x++) {
                array[0][x] = 0;
                cArray[0][x] = 0;
            }
            
            int *array2 = new int[oScreen->get_dy() * oScreen->get_dx() + 1];
            int *cArray2 = new int[oScreen->get_dy() * oScreen->get_dx() + 1];
            for(int i=0; i<oScreen->get_dy(); i++) {
                for(int j=0; j<oScreen->get_dx(); j++) {
                    array2[i * oScreen->get_dx() + j] = array[i][j];
                    cArray2[i * oScreen->get_dx() + j] = cArray[i][j];
                }
            }
            *oScreen = Matrix(array2, oScreen->get_dy(), oScreen->get_dx());
            *oCScreen = Matrix(cArray2, oScreen->get_dy(), oScreen->get_dx());
            return deleteFullLines();
        }
    }

    return;
}