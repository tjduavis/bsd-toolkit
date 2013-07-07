/*
 * RedState.java
 *
 * Created on 2007�� 4�� 7�� (��), ���� 6:41
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
