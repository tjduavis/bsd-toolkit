/*
 * GameBoard.java
 * Created on April 7, 2007
 * @author TJ, Vincent Lam, and Ryan Wang
 * Copyright 2007, All Rights Reserved
 */
package gameoflife;

import java.awt.event.ItemEvent;
import javax.swing.*;
import java.awt.*;
import java.lang.Object.*;
import java.awt.event.*;
import java.io.*;

/**
 * Client
 * Description: Serves to encapsulate the entire game application.
 */
public class GameBoard extends javax.swing.JFrame {
    IGeneration generator;
    int gameBoardSize = 0;
    // mapSize 0: small game board
    // mapSize 1: medium game board
    // mapSize 2: large game board
    int gameSpeed = 0;
    // speed 0: very slow
    // speed 1: slow
    // speed 2: moderate
    // speed 3: fast
    // speed 4: very fast
    int offScreenCells = 100;
    int defaultCellSize = 20;
    int defaultGameSpeed = 1000;
    String fileOpenErrorMessage = "Invalid filename. Try again.";
    boolean keepGenerating = false;
    /**
     * Creates new form GameBoard
     */
    public GameBoard() {
        initComponents();
        initGameBoard();
        tfFileName.setText("sample.txt");
    }
    public void initGameBoard() {
        cGameBoard = new java.awt.Canvas();
        cGameBoard.setSize(offScreenCells * defaultCellSize, offScreenCells * defaultCellSize);
        myScrollPane.add(cGameBoard);
        cGameBoard.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                int cellSize = defaultCellSize;
                for (int i = 0; i < gameBoardSize; i++) {cellSize /= 2;}
                cellClicked(evt.getY()/cellSize, evt.getX()/cellSize);
            }
        });
        myTimer = new Timer(defaultGameSpeed, new ActionListener() {
           public void actionPerformed (ActionEvent evt) {
               if (keepGenerating) myGameBoard.setGrid((Grid)generator.NextGeneration());
               refreshGameBoard();
           } 
        });
        myTimer.start();
        
        myGameBoard = new Grid(offScreenCells, offScreenCells);
        generator = myGameBoard.createGenerator();
        drawGrids();
        refreshGameBoard();
        // listener is added. draw grids. 
    }

    public void cellClicked(int rowNum, int colNum) {
        // trigger the color change 
        // get the resultant color and draw it
        myGameBoard.cellClicked(rowNum, colNum);
        refreshGameBoard();
    }
    

    // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
    private void initComponents() {
        jSeparator1 = new javax.swing.JSeparator();
        btnStart = new javax.swing.JButton();
        btnNext = new javax.swing.JButton();
        cbMapSize = new javax.swing.JComboBox();
        cbGameSpeed = new javax.swing.JComboBox();
        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        tfFileName = new javax.swing.JTextField();
        btnLoad = new javax.swing.JButton();
        jSeparator2 = new javax.swing.JSeparator();
        myScrollPane = new java.awt.ScrollPane();
        btnClear = new javax.swing.JButton();
        jLabel4 = new javax.swing.JLabel();
        lblCounter = new javax.swing.JLabel();
        jSeparator3 = new javax.swing.JSeparator();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setResizable(false);

        btnStart.setFont(new java.awt.Font("Tahoma", 0, 12));
        btnStart.setText("Start");
        btnStart.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseReleased(java.awt.event.MouseEvent evt) {
                btnStartMouseReleased(evt);
            }
        });

        btnNext.setFont(new java.awt.Font("Tahoma", 0, 12));
        btnNext.setText("Next");
        btnNext.setActionCommand("btnClear");
        btnNext.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                btnNextMouseClicked(evt);
            }
        });

        cbMapSize.setFont(new java.awt.Font("Tahoma", 0, 12));
        cbMapSize.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Small", "Midium", "Large" }));
        cbMapSize.addItemListener(new java.awt.event.ItemListener() {
            public void itemStateChanged(java.awt.event.ItemEvent evt) {
                cbMapSizeSelectedItemChanged(evt);
            }
        });

        cbGameSpeed.setFont(new java.awt.Font("Tahoma", 0, 12));
        cbGameSpeed.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Very Slow", "Slow", "Moderate", "Fast", "Very Fast" }));
        cbGameSpeed.addItemListener(new java.awt.event.ItemListener() {
            public void itemStateChanged(java.awt.event.ItemEvent evt) {
                cbGameSpeedSelectedItemChanged(evt);
            }
        });

        jLabel1.setFont(new java.awt.Font("Tahoma", 0, 12));
        jLabel1.setText("Speed:");

        jLabel2.setFont(new java.awt.Font("Tahoma", 0, 12));
        jLabel2.setText("Map Size:");

        jLabel3.setFont(new java.awt.Font("Tahoma", 0, 12));
        jLabel3.setText("Map File Name");

        tfFileName.setFont(new java.awt.Font("Tahoma", 0, 12));
        tfFileName.addFocusListener(new java.awt.event.FocusAdapter() {
            public void focusGained(java.awt.event.FocusEvent evt) {
                tfFileNameFocusGained(evt);
            }
        });

        btnLoad.setFont(new java.awt.Font("Tahoma", 0, 12));
        btnLoad.setText("Load");
        btnLoad.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                btnLoadMouseClicked(evt);
            }
        });

        myScrollPane.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseReleased(java.awt.event.MouseEvent evt) {
                myScrollPaneMouseReleased(evt);
            }
        });
        myScrollPane.addMouseMotionListener(new java.awt.event.MouseMotionAdapter() {
            public void mouseDragged(java.awt.event.MouseEvent evt) {
                myScrollPaneMouseDragged(evt);
            }
        });

        btnClear.setFont(new java.awt.Font("Tahoma", 0, 12));
        btnClear.setText("Clear Game Board");
        btnClear.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                btnClearMouseClicked(evt);
            }
        });

        jLabel4.setText("Generation Counter: ");

        lblCounter.setFont(new java.awt.Font("Tahoma", 0, 12));
        lblCounter.setText("0");

        org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .addContainerGap()
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(layout.createSequentialGroup()
                        .add(jLabel3)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(tfFileName, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 174, Short.MAX_VALUE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(btnLoad)
                        .add(189, 189, 189))
                    .add(org.jdesktop.layout.GroupLayout.TRAILING, layout.createSequentialGroup()
                        .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                            .add(org.jdesktop.layout.GroupLayout.LEADING, jSeparator3, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 500, Short.MAX_VALUE)
                            .add(org.jdesktop.layout.GroupLayout.LEADING, layout.createSequentialGroup()
                                .add(btnStart)
                                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                                .add(btnNext)
                                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                                .add(btnClear)
                                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                                .add(jLabel4)
                                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                                .add(lblCounter))
                            .add(org.jdesktop.layout.GroupLayout.LEADING, layout.createSequentialGroup()
                                .add(jLabel1)
                                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                                .add(cbGameSpeed, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 88, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                                .add(jLabel2)
                                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                                .add(cbMapSize, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 88, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                            .add(org.jdesktop.layout.GroupLayout.LEADING, jSeparator2, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 500, Short.MAX_VALUE)
                            .add(org.jdesktop.layout.GroupLayout.LEADING, jSeparator1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 500, Short.MAX_VALUE)
                            .add(org.jdesktop.layout.GroupLayout.LEADING, myScrollPane, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 500, Short.MAX_VALUE))
                        .addContainerGap())))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .addContainerGap()
                .add(myScrollPane, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 300, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jSeparator1, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 10, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(btnStart)
                    .add(btnNext)
                    .add(btnClear)
                    .add(jLabel4)
                    .add(lblCounter))
                .add(14, 14, 14)
                .add(jSeparator2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 10, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(cbMapSize, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                        .add(jLabel1)
                        .add(cbGameSpeed, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .add(jLabel2)))
                .add(15, 15, 15)
                .add(jSeparator3, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 10, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(tfFileName, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(btnLoad)
                    .add(jLabel3))
                .addContainerGap())
        );
        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void tfFileNameFocusGained(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_tfFileNameFocusGained
        if (tfFileName.getText().equalsIgnoreCase(fileOpenErrorMessage)) {tfFileName.setText("");}
        
    }//GEN-LAST:event_tfFileNameFocusGained

    private void btnLoadMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_btnLoadMouseClicked
        String fileName = tfFileName.getText();
        DataInputStream dis = null; 
        String record = null; 
        int recCount = 0; 
        stopRunning();
        try { 
           File f = new File(fileName); 
           FileInputStream fis = new FileInputStream(f); 
           BufferedInputStream bis = new BufferedInputStream(fis); 
           dis = new DataInputStream(bis);  
           
           while ((record=dis.readLine()) != null) { 
              recCount++; 
              int col = Integer.parseInt(record.split(",")[0]);
              int row = Integer.parseInt(record.split(",")[1]);
              String color = record.split(",")[2];
              cellClicked(row, col);
              if (color.equalsIgnoreCase("Blue") == true) {cellClicked(row, col);}
           } 
        } catch (IOException e) {
           //System.out.println(e.getMessage());
           tfFileName.setText(fileOpenErrorMessage);
           
          
        } finally {  
           if (dis != null) { 
	      try {
                 dis.close(); 
	      } catch (IOException ioe) {
                  
	      }
           } 
        } 
    }//GEN-LAST:event_btnLoadMouseClicked

    private void btnClearMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_btnClearMouseClicked
        stopRunning();
        refreshGameBoard();
    }//GEN-LAST:event_btnClearMouseClicked
    private void stopRunning() {
        myGameBoard.clearGameBoard();
        //myTimer.stop();
        keepGenerating = false;
        if (btnStart.getText() == "Stop") {btnStart.setText("Start");}   
    }
    
    private void btnNextMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_btnNextMouseClicked
        myGameBoard.setGrid((Grid)generator.NextGeneration());
        refreshGameBoard();
    }//GEN-LAST:event_btnNextMouseClicked

    private void myScrollPaneMouseReleased(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_myScrollPaneMouseReleased
        refreshGameBoard();
    }//GEN-LAST:event_myScrollPaneMouseReleased

    private void myScrollPaneMouseDragged(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_myScrollPaneMouseDragged
        refreshGameBoard();
    }//GEN-LAST:event_myScrollPaneMouseDragged

    private void cbGameSpeedSelectedItemChanged(java.awt.event.ItemEvent evt) {//GEN-FIRST:event_cbGameSpeedSelectedItemChanged
        gameSpeed = cbGameSpeed.getSelectedIndex();
        if (gameSpeed == 0) {
            myTimer.setDelay(1000);
        } else if (gameSpeed == 1) {
            myTimer.setDelay(500);
        } else if (gameSpeed == 2) {
            myTimer.setDelay(300);
        } else if (gameSpeed == 3) {
            myTimer.setDelay(100);
        } else if (gameSpeed == 4) {
            myTimer.setDelay(50);
        }
        
        
    }//GEN-LAST:event_cbGameSpeedSelectedItemChanged

    private void cbMapSizeSelectedItemChanged(java.awt.event.ItemEvent evt) {//GEN-FIRST:event_cbMapSizeSelectedItemChanged
        gameBoardSize = cbMapSize.getSelectedIndex();
        drawGrids();
        refreshGameBoard();
    }//GEN-LAST:event_cbMapSizeSelectedItemChanged
    private void refreshGameBoard() {
        //drawGrids();
        lblCounter.setText(Integer.toString(myGameBoard.getAge()));
        int cellsRow = myGameBoard.getRow();
        int cellsCol = myGameBoard.getCol();
        for (int row = 0; row < cellsRow; row++) {
            for (int col = 0; col < cellsCol; col++) {
                drawRects(row, col, myGameBoard.getColor(row, col));
            }
        }
    }
    private void btnStartMouseReleased(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_btnStartMouseReleased
        if (btnStart.getText() == "Stop") {
            //myTimer.stop();
            keepGenerating = false;
            btnStart.setText("Start");
        } else {
            //myTimer.start();
            keepGenerating = true;
            btnStart.setText("Stop");            
        }
    }//GEN-LAST:event_btnStartMouseReleased
    
    private void drawGrids() {
        int cellSize = defaultCellSize;
        int numberOfLoops = offScreenCells;
        for (int i = 0; i < gameBoardSize; i++) {cellSize /= 2; numberOfLoops *= 2;}
        
        Graphics myGraphics = cGameBoard.getGraphics();
        myGraphics.setColor(Color.decode("#FFFFFF"));
        myGraphics.fillRect(0, 0, defaultCellSize * offScreenCells, defaultCellSize * offScreenCells);
        myGraphics.setColor(Color.decode("#CCCCCC"));
        for (int i = 0; i < numberOfLoops; i++) {myGraphics.drawLine(i * cellSize, 0, i * cellSize, defaultCellSize * offScreenCells);}
        for (int i = 0; i < numberOfLoops; i++) {myGraphics.drawLine(0, i * cellSize, defaultCellSize * offScreenCells, i * cellSize);}
        myGraphics.drawLine(defaultCellSize * offScreenCells,0,defaultCellSize * offScreenCells,defaultCellSize * offScreenCells);
        myGraphics.drawLine(0,defaultCellSize * offScreenCells,defaultCellSize * offScreenCells,defaultCellSize * offScreenCells);
    }
    private void drawRects(int coorRow, int coorCol, Color recColor) {
        int cellSize = defaultCellSize;
        for (int i = 0; i < gameBoardSize; i++) {cellSize /= 2;}
        Graphics myGraphics = cGameBoard.getGraphics();
        myGraphics.setColor(recColor);
        myGraphics.fillRect(coorCol * cellSize + 1, coorRow * cellSize + 1, cellSize - 1, cellSize - 1);
    }
    
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                GameBoard myGameBoard = new GameBoard();
                myGameBoard.setVisible(true);
                myGameBoard.setTitle("Game Of Life V1 by Timothy, Vincent and Ryan");
            }
        });
    }
    private java.awt.Canvas cGameBoard;
    private Graphics offScreen;
    private Grid myGameBoard;
    private Timer myTimer;
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btnClear;
    private javax.swing.JButton btnLoad;
    private javax.swing.JButton btnNext;
    private javax.swing.JButton btnStart;
    private javax.swing.JComboBox cbGameSpeed;
    private javax.swing.JComboBox cbMapSize;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JSeparator jSeparator1;
    private javax.swing.JSeparator jSeparator2;
    private javax.swing.JSeparator jSeparator3;
    private javax.swing.JLabel lblCounter;
    private java.awt.ScrollPane myScrollPane;
    private javax.swing.JTextField tfFileName;
    // End of variables declaration//GEN-END:variables
    
}
