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
   
   int code = 0;
   
       switch (operation) {
           case "LOAD":
               code = Machine.LOADop;
               break;
           case "LOADA":
               code = Machine.LOADAop;
               break;
           case "LOADI":
               code = Machine.LOADIop;
               break;
           case "LOADL":
               code = Machine.LOADLop;
               break;
           case "STORE":
               code = Machine.STOREop;
               break;
           case "STOREI":
               code = Machine.STOREIop;
               break;
           case "CALL":
               code = Machine.CALLop;
               break;
           case "CALLI":
               code = Machine.CALLIop;
               break;
           case "RETURN":
               code = Machine.RETURNop;
               break;
           case "PUSH":
               code = Machine.PUSHop;
               break;
           case "POP":
               code = Machine.POPop;
               break;
           case "JUMP":
               code = Machine.JUMPop;
               break;
           case "JUMPI":
               code = Machine.JUMPIop;
               break;
           case "JUMPIF":
               code = Machine.JUMPIFop;
               break;
           case "HALT":
               code = Machine.HALTop;
               break;
           default:
               break;
       }
   
   return code;
   }
   
   
   private static int getRegisterCode(String register){
   
   int code = 0;
   
       switch (register) {
           case "CB":
               code = Machine.CBr;
               break;
           case "CT":
               code = Machine.CTr;
               break;
           case "PB":
               code = Machine.PBr;
               break;
           case "PT":
               code = Machine.PTr;
               break;
           case "SB":
               code = Machine.SBr;
               break;
           case "ST":
               code = Machine.STr;
               break;
           case "HB":
               code = Machine.HBr;
               break;
           case "HT":
               code = Machine.HTr;
               break;
           case "LB":
               code = Machine.LBr;
               break;
           case "L1":
               code = Machine.L1r;
               break;
           case "L2":
               code = Machine.L2r;
               break;
           case "L3":
               code = Machine.L3r;
               break;
           case "L4":
               code = Machine.L4r;
               break;
           case "L5":
               code = Machine.L5r;
               break;
           case "L6":
               code = Machine.L6r;
               break;
           case "CP":
               code = Machine.CPr;
               break;
           default:
               break;
       }   
   
   
   return code;
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
            System.out.println("\n***************** Running from File *****************");
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
