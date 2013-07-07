/*
 * BaseState.java
 * Created on April 7, 2007
 * @author TJ, Vincent Lam, and Ryan Wang
 * Copyright 2007, All Rights Reserved
 */

package gameoflife;
import java.awt.Color;

/**
 * !State
 * Participant: State
 * Description: Serves as an encapsulation of a the context Cell
 */
public interface BaseState {
    	public BaseState getNextState();
	public Color stateColor();
	public BaseState killThisCell();
}
