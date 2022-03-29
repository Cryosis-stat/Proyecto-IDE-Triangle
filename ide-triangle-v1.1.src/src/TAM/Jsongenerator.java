/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package TAM;

import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.FileWriter;
import java.io.PrintWriter;


/*
* Creates a file that contain
* TAM instructions in Json format
*/
public class Jsongenerator {
    
   static String objectName; 
   
   static int CT; 
      

 /**
  * Writes in the file the length 
  * following the json format.
  * @param n	the length to write.
  * @param pw	pointer to the file.
  */  
  private static void writeN(int n,PrintWriter pw){
    pw.println("    \"length\" : " + n + ",");
  } 

  
  
 /**
  * Writes in the file the operand 
  * following the json format.
  * @param d	the operand to write.
  * @param pw	pointer to the file.
  */  
  private static void writeD(int d,PrintWriter pw){
    pw.println("    \"operand\" : " + d );
  }  

  
 /**
  * Writes in the file the register
  * following the json format.
  * @param r	the register to write.
  * @param pw	pointer to the file.
  */
  private static void writeR(int r, PrintWriter pw){
  
    switch (r) {
      case Machine.CBr:
        pw.println("    \"register\" : \"CB\",");
        break;
      case Machine.CTr:
	pw.println("    \"register\" : \"CT\",");
	break;
      case Machine.PBr:
	pw.println("    \"register\" : \"PB\",");
	break;
      case Machine.PTr:
	pw.println("    \"register\" : \"PT\",");
	break;
      case Machine.SBr:
	pw.println("    \"register\" : \"SB\",");
	break;
      case Machine.STr:
	pw.println("    \"register\" : \"ST\",");
	break;
      case Machine.HBr:
	pw.println("    \"register\" : \"HB\",");
	break;
      case Machine.HTr:
	pw.println("    \"register\" : \"HT\",");
	break;
      case Machine.LBr:
	pw.println("    \"register\" : \"LB\",");
	break;
      case Machine.L1r:
	pw.println("    \"register\" : \"L1\",");
	break;
      case Machine.L2r:
	pw.println("    \"register\" : \"L2\",");
	break;
      case Machine.L3r:
	pw.println("    \"register\" : \"L3\",");
	break;
      case Machine.L4r:
	pw.println("    \"register\" : \"L4\",");
	break;
      case Machine.L5r:
	pw.println("    \"register\" : \"L5\",");
	break;
      case Machine.L6r:
	pw.println("    \"register\" : \"L6\",");
	break;
      case Machine.CPr:
	pw.println("    \"register\" : \"CP\",");
	break;
    }
  
  } 
  
  /**
   * Writes in the file operation of the given instruction in 
   * assembly-code format following the json format.
   * @param instr	the instruction to write.
   * @param pw	pointer to the file.
   */
  private static void writeInstruction(Instruction instr, PrintWriter pw){
     
    pw.println("  {");
    switch (instr.op) {
      case Machine.LOADop:
        pw.println("    \"operation\" : \"LOAD\",");
	break;

      case Machine.LOADAop:
        pw.println("    \"operation\" : \"LOADA\",");
        break;

      case Machine.LOADIop:
        pw.println("    \"operation\" : \"LOADI\",");
        break;

      case Machine.LOADLop:
        pw.println("    \"operation\" : \"LOADL\",");
        break;

      case Machine.STOREop:
        pw.println("    \"operation\" : \"STORE\",");
        break;

      case Machine.STOREIop:
        pw.println("    \"operation\" : \"STOREI\",");
        break;

      case Machine.CALLop:
        pw.println("    \"operation\" : \"CALL\",");
        break;

      case Machine.CALLIop:
        pw.println("    \"operation\" : \"CALLI\",");
	break;

      case Machine.RETURNop:
        pw.println("    \"operation\" : \"RETURN\",");
        break;

      case Machine.PUSHop:
        pw.println("    \"operation\" : \"PUSH\",");
        break;

      case Machine.POPop:
        pw.println("    \"operation\" : \"POP\",");
        break;

      case Machine.JUMPop:
        pw.println("    \"operation\" : \"JUMP\",");
        break;

      case Machine.JUMPIop:
        pw.println("    \"operation\" : \"JUMPI\",");
        break;

      case Machine.JUMPIFop:
        pw.println("    \"operation\" : \"JUMPIF\",");
        break;

      case Machine.HALTop:
        pw.println("    \"operation\" : \"HALT\",");
        break;
    }
    
    writeR(instr.r,pw);
    writeN(instr.n,pw);
    writeD(instr.d,pw);
    if (instr.op != Machine.HALTop)
        pw.println("  },");
    else 
        pw.println("  }");
  } 
 
   /**
   * Create de file and write the instructions .
   */
  private static void createJSON(String filename){
  
   FileWriter file = null;   
   PrintWriter pw = null;
   try
        {
            //Create file
            file = new FileWriter(filename.replace(".tam", ".json"));
            pw = new PrintWriter(file);
            
            //write in file
            pw.println("[");
            for (int addr = Machine.CB; addr < CT; addr++) {
                writeInstruction(Machine.code[addr],pw);
            }
            
            pw.println("]");
            
            file.close();
        }                                                                                                                                                                              
    catch (Exception e) {
            e.printStackTrace();
        }
 
  } 
  
   /**
   * Loads the TAM object program into code store from the named file.
   * @param objectName	the name of the file containing the program.
   */
  private static void loadObjectProgram (String objectName) {

    FileInputStream objectFile = null;
    DataInputStream objectStream = null;

    int addr;
    boolean finished = false;

    try {
      objectFile = new FileInputStream (objectName);
      objectStream = new DataInputStream (objectFile);

      addr = Machine.CB;
      while (!finished) {
        Machine.code[addr] = Instruction.read(objectStream);
        if (Machine.code[addr] == null)
          finished = true;
        else
          addr = addr + 1;
      }
      CT = addr;
      objectFile.close();
    } catch (FileNotFoundException s) {
      CT = Machine.CB;
      System.err.println ("Error opening object file: " + s);
    } catch (IOException s) {
      CT = Machine.CB;
      System.err.println ("Error reading object file: " + s);
    }
  }    
   
  
  /**
  * Main function,can receive the name of the
  * TAM objetc to be written in json
  */
  public static void main(String[] args) {
       
    if (args.length == 1){
      objectName = args[0];
      loadObjectProgram(objectName);
      createJSON(objectName);
      
    }
    else
      System.out.print("\nFile name not specified\n");
  }  
      
}
