/*
 * IGrid.java
 * Created on April 7, 2007
 * @author TJ, Vincent Lam, and Ryan Wang
 * Copyright 2007, All Rights Reserved
 */

package gameoflife;

/**
 * !Iterator
 * Participant: Abstract Aggregation
 * Description: Serves to define the encapsulation of the aggregation of Cells
 */
public interface IGrid {
    public IGeneration createGenerator();
}
