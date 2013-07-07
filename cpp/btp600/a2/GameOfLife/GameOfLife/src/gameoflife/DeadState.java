/*
 * DeadState.java
 *
 * Created on 2007년 4월 7일 (토), 오후 6:48
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
