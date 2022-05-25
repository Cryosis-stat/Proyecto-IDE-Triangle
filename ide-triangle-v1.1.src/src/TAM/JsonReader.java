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
   
   
  private static void writeR (char leftbracket, int r, char rightbracket) {

    System.out.print(leftbracket);
    switch (r) {
      case Machine.CBr:
        System.out.print ("CB");
        break;
      case Machine.CTr:
	System.out.print ("CT");
	break;
      case Machine.PBr:
	System.out.print ("PB");
	break;
      case Machine.PTr:
	System.out.print ("PT");
	break;
      case Machine.SBr:
	System.out.print ("SB");
	break;
      case Machine.STr:
	System.out.print ("ST");
	break;
      case Machine.HBr:
	System.out.print ("HB");
	break;
      case Machine.HTr:
	System.out.print ("HT");
	break;
      case Machine.LBr:
	System.out.print ("LB");
	break;
      case Machine.L1r:
	System.out.print ("L1");
	break;
      case Machine.L2r:
	System.out.print ("L2");
	break;
      case Machine.L3r:
	System.out.print ("L3");
	break;
      case Machine.L4r:
	System.out.print ("L4");
	break;
      case Machine.L5r:
	System.out.print ("L5");
	break;
      case Machine.L6r:
	System.out.print ("L6");
	break;
      case Machine.CPr:
	System.out.print ("CP");
	break;
    }
    System.out.print (rightbracket);
  }
   
    private static void blankN() {
    System.out.print ("      ");
  } 
   
   
  private static void writeN (int n) {
    System.out.print ("(" + n + ") ");
    if (n < 10)
      System.out.print ("  ");
    else if (n < 100)
      System.out.print (" ");
  }   
   
  private static void writeD (int d) {
    System.out.print (d);
  }  
   
     private static void writePrimitive (int d) {
    switch (d) {
      case Machine.idDisplacement:
        System.out.print ("id      ");
	break;
      case Machine.notDisplacement:
	System.out.print ("not     ");
	break;
      case Machine.andDisplacement:
	System.out.print ("and     ");
	break;
      case Machine.orDisplacement:
	System.out.print ("or      ");
	break;
      case Machine.succDisplacement:
	System.out.print ("succ    ");
	break;
      case Machine.predDisplacement:
	System.out.print ("pred    ");
	break;
      case Machine.negDisplacement:
	System.out.print ("neg     ");
	break;
      case Machine.addDisplacement:
	System.out.print ("add     ");
	break;
      case Machine.subDisplacement:
	System.out.print ("sub     ");
	break;
      case Machine.multDisplacement:
	System.out.print ("mult    ");
	break;
      case Machine.divDisplacement:
	System.out.print ("div     ");
	break;
      case Machine.modDisplacement:
	System.out.print ("mod     ");
	break;
      case Machine.ltDisplacement:
	System.out.print ("lt      ");
	break;
      case Machine.leDisplacement:
	System.out.print ("le      ");
	break;
      case Machine.geDisplacement:
	System.out.print ("ge      ");
	break;
      case Machine.gtDisplacement:
	System.out.print ("gt      ");
	break;
      case Machine.eqDisplacement:
	System.out.print ("eq      ");
	break;
      case Machine.neDisplacement:
	System.out.print ("ne      ");
	break;
      case Machine.eolDisplacement:
	System.out.print ("eol     ");
	break;
      case Machine.eofDisplacement:
	System.out.print ("eof     ");
	break;
      case Machine.getDisplacement:
	System.out.print ("get     ");
	break;
      case Machine.putDisplacement:
	System.out.print ("put     ");
	break;
      case Machine.geteolDisplacement:
	System.out.print ("geteol  ");
	break;
      case Machine.puteolDisplacement:
	System.out.print ("puteol  ");
	break;
      case Machine.getintDisplacement:
	System.out.print ("getint  ");
	break;
      case Machine.putintDisplacement:
	System.out.print ("putint  ");
	break;
      case Machine.newDisplacement:
	System.out.print ("new     ");
	break;
      case Machine.disposeDisplacement:
	System.out.print ("dispose ");
	break;
    }
  }
   
     private static void writeInstruction (Instruction instr) {

    switch (instr.op) {
      case Machine.LOADop:
	System.out.print ("LOAD  ");
	writeN(instr.n);
	writeD(instr.d);
	writeR('[', instr.r, ']');
	break;

      case Machine.LOADAop:
        System.out.print ("LOADA ");
        blankN();
        writeD(instr.d);
        writeR('[', instr.r, ']');
        break;

      case Machine.LOADIop:
        System.out.print ("LOADI ");
        writeN(instr.n);
        break;

      case Machine.LOADLop:
        System.out.print ("LOADL ");
        blankN();
        writeD(instr.d);
        break;

      case Machine.STOREop:
        System.out.print ("STORE ");
        writeN(instr.n);
        writeD(instr.d);
        writeR('[', instr.r, ']');
        break;

      case Machine.STOREIop:
        System.out.print ("STOREI");
        writeN(instr.n);
        break;

      case Machine.CALLop:
        System.out.print ("CALL  ");
        if (instr.r == Machine.PBr) {
          blankN();
          writePrimitive(instr.d);
        } else {
          writeR('(', instr.n, ')');
          System.out.print ("  ");
          writeD(instr.d);
          writeR('[', instr.r, ']');
        }
        break;

      case Machine.CALLIop:
        System.out.print ("CALLI ");
	break;

      case Machine.RETURNop:
        System.out.print ("RETURN");
        writeN(instr.n);
        writeD(instr.d);
        break;

      case Machine.PUSHop:
        System.out.print ("PUSH  ");
        blankN();
        writeD(instr.d);
        break;

      case Machine.POPop:
        System.out.print ("POP   ");
        writeN(instr.n);
        writeD(instr.d);
        break;

      case Machine.JUMPop:
        System.out.print ("JUMP  ");
        blankN();
        writeD(instr.d);
        writeR('[', instr.r, ']');
        break;

      case Machine.JUMPIop:
        System.out.print ("JUMPI ");
        break;

      case Machine.JUMPIFop:
        System.out.print ("JUMPIF");
        writeN(instr.n);
        writeD(instr.d);
        writeR('[', instr.r, ']');
        break;

      case Machine.HALTop:
        System.out.print ("HALT  ");
    }
  }
   

    public static void readFileTAM(String info) {
        Gson gson = new Gson();
        String result = "********** TAM JSON Reader ( Version 1) **********\n";
        System.out.print(result);
        int cont = 0;
        JsonReader[] tam = gson.fromJson(info, JsonReader[].class);
        
        for (JsonReader obj : tam) {
            loadInstruction(obj,cont);
            writeInstruction(Machine.code[cont]);
            System.out.println();
            cont += 1;
        }
        
        if (cont != 0){
            TAM.Interpreter.CT = cont;
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
