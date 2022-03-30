/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Core.IDE;

import java.awt.event.ActionListener;

/**
 *
 * @author OtonielBN
 */
public class IDEJSONexecuter {
    // <editor-fold defaultstate="collapsed" desc=" Methods ">    
    
    /**
     * Creates a new instance of IDEInterpreter.
     * @param _delegate Event to be fired when the thread stops running.
     */
    public IDEJSONexecuter(ActionListener _delegate) {
        delegate = _delegate;
    }
    
    /**
     * Runs the Interpreter static main method as a separate thread.
     * @param fileName Path to the TAM Object File.
     */       
    public synchronized void Run() {
        new Thread(new Runnable() {
            public void run() {
                TAM.JsonReader.executeCode();
                delegate.actionPerformed(null);
            }
        }).start();
    } 

    // <editor-fold defaultstate="collapsed" desc=" Attributes ">
    private ActionListener delegate;    // Gets triggered when the Interpreter stops.
    // </editor-fold>

    
}
