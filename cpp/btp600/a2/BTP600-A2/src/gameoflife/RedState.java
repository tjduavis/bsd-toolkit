/*
 * Grid.java
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
public class RedState implements BaseState{
    
    /** Creates a new instance of RedState */
    public RedState() {
        
    }
    public BaseState getNextState() {
        return new BlueState();
    }
    public Color stateColor() {
        return Color.RED;
    }
    public BaseState killThisCell() {
        return new DeadState();
    } 
}
