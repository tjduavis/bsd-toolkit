/*
 * Generation.java
 * Created on April 7, 2007
 * @author TJ, Vincent Lam, and Ryan Wang
 * Copyright 2007, All Rights Reserved
 */

package gameoflife;
import java.awt.Color;

/**
 * !Iterator
 * Participant: Concrete Iterator
 * Description: Serves to manage the generation process of the cells contained in the Grid  
 */
public class Generation implements IGeneration {
    Grid _grid;
    
    /** Creates a new instance of Generation */
    public Generation(Grid grid) {
        _grid = grid;
    }
    public IGrid NextGeneration() { 
        _grid.addAge();
        for (int row = 0; row < _grid.getRow(); row++) {
            for (int col = 0; col < _grid.getCol(); col++) {
                process(row, col);
            }
        }
        for (int row = 0; row < _grid.getRow(); row++) {
            for (int col = 0; col < _grid.getCol(); col++) {
                _grid.getCell(row,col).applyNewState();
            }
        }   
        return _grid;
    }
    private void process(int row, int col) {
        int numberOfRedCells = 0;
        int numberOfBlueCells = 0;
        for (int r = row - 1; r <= row + 1; r++) {
            for (int c = col - 1; c <= col + 1; c++) {
                if (!(row == r && col == c)) {
                    if (r >= 0 && c >= 0 && r <= _grid.getRow() && c <= _grid.getCol()) {
                        if (_grid.getCell(r,c).getState().stateColor() == Color.RED) numberOfRedCells++;
                        if (_grid.getCell(r,c).getState().stateColor() == Color.BLUE) numberOfBlueCells++;                        
                    } 
                }
            }
        }
        
        if (_grid.getColor(row, col) == Color.BLACK && numberOfRedCells == 3) {
            _grid.getCell(row, col).setNextState(new RedState());
        } else if (_grid.getColor(row, col) == Color.BLACK && numberOfBlueCells == 3) {
            _grid.getCell(row, col).setNextState(new BlueState());
        } else if (_grid.getColor(row, col) == Color.RED && (numberOfRedCells < 2 || numberOfRedCells > 3)) {
            _grid.getCell(row, col).setNextState(new DeadState());
        } else if (_grid.getColor(row, col) == Color.BLUE && (numberOfBlueCells < 2 || numberOfBlueCells > 3)) {
            _grid.getCell(row, col).setNextState(new DeadState());
        }
    }
}
