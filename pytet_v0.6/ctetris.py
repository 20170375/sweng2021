from tetris import *

class CTetris(Tetris):
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

    def anyConflictWhileUpdate(self):
        doesConflict = Tetris.anyConflictWhileUpdate(self)

        currCBlk = CTetris.setOfCBlockObjects[self.idxBlockType][self.idxBlockDegree]
        tempBlk = self.iCScreen.clip(self.top, self.left, self.top+currCBlk.get_dy(), self.left+currCBlk.get_dx())
        tempBlk = tempBlk + currCBlk

        self.oCScreen = Matrix(self.iCScreen)
        self.oCScreen.paste(tempBlk, self.top, self.left)
        return doesConflict

### end of class CTetris():
