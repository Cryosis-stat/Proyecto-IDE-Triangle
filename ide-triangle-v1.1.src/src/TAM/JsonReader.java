/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package TAM;

/**
 *
 * @author sofia
 */
public class JsonReader {
    private String operation;
    private String register;
    private int operand;
    private int length;

    public JsonReader() {
    }

    public JsonReader(String operation, String register,int operand, int length) {
        this.operation = operation;
        this.register = register;
        this.operand = operand;
        this.length = length;
    }

    public String getOperation() {
        return operation;
    }

    public String getRegister() {
        return register;
    }

    public int getLength() {
        return length;
    }

    public int getOperand() {
        return operand;
    }
}
