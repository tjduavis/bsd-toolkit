/*
 * DeadState.java
 * Created on April 7, 2007
 * @author TJ, Vincent Lam, and Ryan Wang
 * Copyright 2007, All Rights Reserved
 */

package gameoflife;
import java.awt.Color;

/**
 * !State
 * Participant: Concrete State
 * Description: Serves to represents a concrete behaviour state of a Cell.
 */
public class DeadState implements BaseState{
    
    /** Creates a new instance of DeadState */
    public DeadState() {
    }
    public BaseState getNextState() {
        return new RedState();
    }
    public Color stateColor() {
        return Color.BLACK;
        //return null;
    }
    public BaseState killThisCell() {
        return new DeadState();
    } 
}
