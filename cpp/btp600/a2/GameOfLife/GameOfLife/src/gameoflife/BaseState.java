/*
 * BaseState.java
 *
 * Created on 2007�� 4�� 7�� (��), ���� 6:39
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
public interface BaseState {
    	public BaseState getNextState();
	public Color stateColor();
	public BaseState killThisCell();
}
