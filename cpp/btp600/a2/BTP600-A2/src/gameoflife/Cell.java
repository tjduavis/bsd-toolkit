/*
 * Cell.java
 * Created on April 7, 2007
 * @author TJ, Vincent Lam, and Ryan Wang
 * Copyright 2007, All Rights Reserved
 */

package gameoflife;

/**
 * !State
 * Participant: Context
 * Description: Serves to contain a set of behavours.
 */
public class Cell {
    BaseState currentState;
    BaseState nextState;
    public Cell() {setState(new DeadState());}
    public void setNextState(BaseState recState) {nextState = recState;}
    public void setState(BaseState recState) {currentState = recState;}
    public BaseState getState() {return currentState;}
    public void killThisCell() {setState(new DeadState());}
    public void applyNewState() {if (nextState != null) {currentState = nextState; nextState = null;}}
    // Grid class triggers this function.
    
    public void giveLife(String recColor) {
        if (recColor == "Red") {setState(new RedState());}
        else if (recColor == "Blue") {setState(new BlueState());}
        else {setState(new DeadState());}
    }
    public void thisCellClicked() {setState(currentState.getNextState());}
}
