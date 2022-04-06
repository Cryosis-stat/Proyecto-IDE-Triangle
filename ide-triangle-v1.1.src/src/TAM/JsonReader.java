/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package TAM;

import static TAM.Interpreter.CT;
import static TAM.Interpreter.interpretProgram;
import static TAM.Interpreter.showStatus;
import static TAM.Machine.CB;
import com.google.gson.Gson;

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
    
   private static int getOperationCode(String operation){
   
   int opCode = 0;
   
       switch (operation) {
           case "LOAD":
               opCode = Machine.LOADop;
               break;
           case "LOADA":
               opCode = Machine.LOADAop;
               break;
           case "LOADI":
               opCode = Machine.LOADIop;
               break;
           case "LOADL":
               opCode = Machine.LOADLop;
               break;
           case "STORE":
               opCode = Machine.STOREop;
               break;
           case "STOREI":
               opCode = Machine.STOREIop;
               break;
           case "CALL":
               opCode = Machine.CALLop;
               break;
           case "CALLI":
               opCode = Machine.CALLIop;
               break;
           case "RETURN":
               opCode = Machine.RETURNop;
               break;
           case "PUSH":
               opCode = Machine.PUSHop;
               break;
           case "POP":
               opCode = Machine.POPop;
               break;
           case "JUMP":
               opCode = Machine.JUMPop;
               break;
           case "JUMPI":
               opCode = Machine.JUMPIop;
               break;
           case "JUMPIF":
               opCode = Machine.JUMPIFop;
               break;
           case "HALT":
               opCode = Machine.HALTop;
               break;
           default:
               break;
       }
   
   return opCode;
   }
   
   
   private static int getRegisterCode(String register){
   
   int registerCode = 0;
   
       switch (register) {
           case "CB":
               registerCode = Machine.CBr;
               break;
           case "CT":
               registerCode = Machine.CTr;
               break;
           case "PB":
               registerCode = Machine.PBr;
               break;
           case "PT":
               registerCode = Machine.PTr;
               break;
           case "SB":
               registerCode = Machine.SBr;
               break;
           case "ST":
               registerCode = Machine.STr;
               break;
           case "HB":
               registerCode = Machine.HBr;
               break;
           case "HT":
               registerCode = Machine.HTr;
               break;
           case "LB":
               registerCode = Machine.LBr;
               break;
           case "L1":
               registerCode = Machine.L1r;
               break;
           case "L2":
               registerCode = Machine.L2r;
               break;
           case "L3":
               registerCode = Machine.L3r;
               break;
           case "L4":
               registerCode = Machine.L4r;
               break;
           case "L5":
               registerCode = Machine.L5r;
               break;
           case "L6":
               registerCode = Machine.L6r;
               break;
           case "CP":
               registerCode = Machine.CPr;
               break;
           default:
               break;
       }   
   
   
   return registerCode;
   }
   
   
   

    public static void readFileTAM(String info) {
        Gson gson = new Gson();
        String result = "********** TAM Disassembler (Sun Version 2.1) **********\n";
        int cont = 0;
        JsonReader[] tam = gson.fromJson(info, JsonReader[].class);
        
        for (JsonReader obj : tam) {
            result += cont + ":  " + obj.getOperation() + "  (" + obj.getLength() + ")  " + obj.getOperand() + " " + obj.getRegister() + "\n";
            loadInstruction(obj,cont);
            cont += 1;
        }
        System.out.print(result);
        
        if (cont != 0){
            TAM.Interpreter.CT = cont;
            //interpretProgram();
            //showStatus();
        }
        
    }
    
    public static void executeCode(){
    
        if (CT != CB){ 
            System.out.println("***************** Running from File *****************\n");
            interpretProgram();
            showStatus();
        }
        else{
        System.out.println("Could't execute code");
        }
    
    }
    
    private static void loadInstruction (JsonReader instruction, int pos){
    
        int operation = getOperationCode(instruction.getOperation());
        int register = getRegisterCode(instruction.getRegister());
        int length = instruction.getLength();
        int operand =instruction.getOperand();

        Machine.code[pos] = new Instruction();
        Machine.code[pos].op = operation;
        Machine.code[pos].r = register;
        Machine.code[pos].n = length; 
        Machine.code[pos].d = operand;
    } 
    
}
