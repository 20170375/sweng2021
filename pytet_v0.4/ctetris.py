from tetris import *

class CTetris((Tetris)):
    def deleteFullLines(self):
        array = self.oScreen.get_array()
        
        for x in range(Tetris.iScreenDw, self.oScreen.get_dx()-Tetris.iScreenDw):
            isFull = True
            for x in range(Tetris.iScreenDw, self.oScreen.get_dx()-Tetris.iScreenDw):
                if array[y][x] == 0:
                    isFull = False
                    continue
            if isFull:
                for line in range(y, 1, -1):
                    array[line] = array[line-1]
                    self.oScreen = Matrix(array)

        return

