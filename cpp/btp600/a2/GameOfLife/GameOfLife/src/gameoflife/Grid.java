/*
 * Grid.java
 *
 * Created on 2007년 4월 7일 (토), 오후 7:01
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package gameoflife;
import java.awt.Color;
/**
 *
 * @author Administrator
 */
public class Grid {
    Cell[][] myCells;
    int rowSize;
    int colSize;
    int counter;
    /** Creates a new instance of Grid */
    public Grid(int recRowSize, int recColSize) {
        counter = 0;
        rowSize = recRowSize;
        colSize = recColSize;
        myCells = new Cell[recRowSize + 2][recColSize + 2];
        for (int row = 0; row < myCells.length; row++) {
            for (int col = 0; col < myCells[row].length; col++) {
                myCells[row][col] = new Cell();
            }
        }
    }
    public void clearGameBoard() {
        counter = 0;
        for (int r = 0; r < rowSize; r++) {
            for (int c = 0; c < colSize; c++) {
                getCell(r, c).killThisCell();
            }
        }
    
    }
    public Cell[][] getCells() {return myCells;}
    public int gameBoardRow() {return rowSize;}
    public int gameBoardCol() {return colSize;}
    public Color getColor(int recRow, int recCol) {
        Color returnValue = null;
        if (recRow >= 0 && recRow <= rowSize && recCol >= 0 && recCol <= colSize) { 
            
            returnValue = myCells[recRow][recCol].getState().stateColor();
        }
        return returnValue;
    }
    public Cell getCell(int recRow, int recCol) {return myCells[recRow][recCol];}
    public void cellClicked(int recRow, int recCol) {myCells[recRow][recCol].thisCellClicked();}
    public void nextGeneration() {
        counter++;
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                assessCell(row, col);
            }
        }
        for (int r = 0; r < rowSize; r++) {
            for (int c = 0; c < colSize; c++) {
                getCell(r,c).applyNewState();
            }
        }        
    }
    public void assessCell(int row, int col) {
        int numberOfRedCells = 0;
        int numberOfBlueCells = 0;
        for (int r = row - 1; r <= row + 1; r++) {
            for (int c = col - 1; c <= col + 1; c++) {
                if (!(row == r && col == c)) {
                    if (r >= 0 && c >= 0 && r <= rowSize && c <= colSize) {
                        //if (getColor(r, c) == Color.RED) {numberOfRedCells++;}
                        //if (getColor(r, c) == Color.BLUE) {numberOfBlueCells++;}
                        //if (myCells[r][c].getState().stateColor() == Color.RED) numberOfRedCells++;
                        if (myCells[r][c].getState().stateColor() == Color.RED) numberOfRedCells++;
                        if (myCells[r][c].getState().stateColor() == Color.BLUE) numberOfBlueCells++;
                        
                    } 
                }
            }
        }
        
        if (getColor(row, col) == Color.BLACK && numberOfRedCells == 3) {
       //if (getColor(row, col) == null && numberOfRedCells == 3) {
        //getCell(row, col).giveLife("Red");
            getCell(row, col).setNextState(new RedState());
        } else if (getColor(row, col) == Color.BLACK && numberOfBlueCells == 3) {
        //} else if (getColor(row, col) == null && numberOfBlueCells == 3) {
            //getCell(row, col).giveLife("Blue");
            getCell(row, col).setNextState(new BlueState());
        } else if (numberOfRedCells+numberOfBlueCells < 2 || numberOfRedCells+numberOfBlueCells > 3) {
            //getCell(row, col).killThisCell();
            getCell(row, col).setNextState(new DeadState());
        }

         
        
    }
    public int getCount() {return counter;}
}
