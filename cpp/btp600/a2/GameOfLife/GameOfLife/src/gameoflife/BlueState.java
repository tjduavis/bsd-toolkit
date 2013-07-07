/*
 * BlueState.java
 *
 * Created on 2007년 4월 7일 (토), 오후 6:44
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
