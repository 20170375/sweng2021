from tetris import *

class CTetris((Tetris)):
    setOfCBlockObjects = 0
    
    @classmethod
    def init(cls, setOfBlockArrays):
        Tetris.init(setOfBlockArrays)
        CTetris.setOfCBlockObjects = [[0]* Tetris.nBlockDegrees for _ in range(Tetris.nBlockTypes)]

        for i in range(Tetris.nBlockTypes):
            for j in range(Tetris.nBlockDegrees):
                obj = Matrix(setOfBlockArrays[i][j])
                obj.mulc(i+1)
                CTetris.setOfCBlockObjects[i][j] = obj
        return

    def __init__(self, cy, cx):
        Tetris.__init__(self, cy, cx)
        arrayScreen = self.createArrayScreen()
        self.iCScreen = Matrix(arrayScreen)
        self.oCScreen = Matrix(self.iCScreen)
        return

    def accept(self, key):
        if key >= '0' and key <= '6':
            if self.justStarted == False:
                self.deleteFullLines()
            self.iCScreen = Matrix(self.oCScreen)

        state = Tetris.accept(self, key)

        currCBlk = CTetris.setOfCBlockObjects[self.idxBlockType][self.idxBlockDegree]
        tempBlk = self.iCScreen.clip(self.top, self.left,
                                            self.top + currCBlk.get_dy(),
                                            self.left + currCBlk.get_dx())
        tempBlk = tempBlk + currCBlk

        self.oCScreen = Matrix(self.iCScreen)
        self.oCScreen.paste(tempBlk, self.top, self.left)
        return state

    def deleteFullLines(self):
        array = self.oScreen.get_array()
        cArray = self.oCScreen.get_array()
        
        for y in range(self.oScreen.get_dy()-CTetris.iScreenDw-1, 0, -1):
            for x in range(CTetris.iScreenDw, self.oScreen.get_dx()-CTetris.iScreenDw):
                if array[y][x] == 0:
                    break
            else:
                for line in range(y, 0, -1):
                    array[line] = array[line-1][ : ]
                    cArray[line] = cArray[line-1][ : ]
                for x in range(CTetris.iScreenDw, self.oScreen.get_dx()-CTetris.iScreenDw):
                    array[0][x] = 0
                    cArray[0][x] = 0
                self.oScreen = Matrix(array)
                self.oCScreen = Matrix(cArray)
                return self.deleteFullLines()

        return


### end of class CTetris():
