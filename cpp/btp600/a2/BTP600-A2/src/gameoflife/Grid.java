/*
 * Grid.java
 * Created on April 7, 2007
 * @author TJ, Vincent Lam, and Ryan Wang
 * Copyright 2007, All Rights Reserved
 */

package gameoflife;
import java.awt.Color;

/**
 * !Iterator
 * Participant: Concrete Aggregation
 * Description: Serves to manage the cells both living and dead in the Game of Life game board
 */
public class Grid implements IGrid {
    private Cell[][] _cell;
    private int _row;
    private int _col;
    private int _age;
    /** Creates a new instance of Grid */
    public Grid(int rowSize, int colSize) {
        _age = 0;
        _row = rowSize;
        _col = colSize;
        _cell = new Cell[rowSize + 2][colSize + 2];
        for (int row = 0; row < _cell.length; row++) {
            for (int col = 0; col < _cell[row].length; col++) {
                _cell[row][col] = new Cell();
            }
        }
    }
    public int getRow() {
        return _row;
    }
    public int getCol() {
        return _col;
    }
    public Color getColor(int row, int col) {
        Color returnValue = null;
        if (row >= 0 && row <= _row && col >= 0 && col <= _col) {
            
            returnValue = _cell[row][col].getState().stateColor();
        }
        return returnValue;
    }
    public Cell getCell(int row, int col) {return _cell[row][col];}
    public Cell[][] getCells() {return _cell;}
    public int getAge() {return _age;}
    public void addAge() { _age++; }
    public void clearGameBoard() {
        _age = 0;
        for (int r = 0; r < _row; r++) {
            for (int c = 0; c < _col; c++) {
                getCell(r, c).killThisCell();
            }
        }
        
    }
    public void setGrid(Grid grid) {
        this._cell = grid.getCells();
    }
    public void cellClicked(int recRow, int recCol) {_cell[recRow][recCol].thisCellClicked();}
    public IGeneration createGenerator() {
        return new Generation(this);
    }
}
