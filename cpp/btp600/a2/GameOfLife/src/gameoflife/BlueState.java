/*
 * BlueState.java
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
public class BlueState implements BaseState {
    
    /** Creates a new instance of BlueState */
    public BlueState() {
        
    }
    public BaseState getNextState() {
        return new DeadState();
    }
    public Color stateColor() {
        return Color.BLUE;
    }
    public BaseState killThisCell() {
        return new DeadState();
    } 
}
