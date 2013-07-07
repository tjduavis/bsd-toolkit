/*
 * IGeneration.java
 * Created on April 7, 2007
 * @author TJ, Vincent Lam, and Ryan Wang
 * Copyright 2007, All Rights Reserved
 */

package gameoflife;

/**
 * !Iterator
 * Participant: Iterator
 * Description: Serves to define the encapsulation of a Generation
 */
public interface IGeneration {
    public IGrid NextGeneration();
}
