


var json_parsed = null;


function getOperationCode( operation ){
   
    var opCode;

    switch (operation){

        case 'LOAD':
            opCode = machine_operation.LOADop;
            break;
        case "LOADA" :
            opCode = machine_operation.LOADAop;
            break;
        case "LOADI":
            opCode = machine_operation.LOADIop;
            break;
        case "LOADL":
            opCode = machine_operation.LOADLop;
            break;
        case "STORE":
            opCode = machine_operation.STOREop;
            break;
        case "STOREI":
            opCode = machine_operation.STOREIop;
            break;
        case "CALL":
            opCode = machine_operation.CALLop;
            break;
        case "CALLI":
            opCode = machine_operation.CALLIop;
            break;
        case "RETURN":
            opCode = machine_operation.RETURNop;
            break;
        case "PUSH":
            opCode = machine_operation.PUSHop;
            break;
        case "POP":
            opCode = machine_operation.POPop;
            break;
        case "JUMP":
            opCode = machine_operation.JUMPop;
            break;
        case "JUMPI":
            opCode = machine_operation.JUMPIop;
            break;
        case"JUMPIF":
            opCode = machine_operation.JUMPIFop;
            break;
        case"HALT":
            opCode = machine_operation.HALTop;
            break;
        default:
            opCode = -1;
                   
    }

    return opCode;

}
 
 
 function getRegisterCode( register ){
    
 
    var registerCode;

    switch (register){
    
         case "CB":
            registerCode = registers.CBr;
            break;
         case "CT":
            registerCode = registers.CTr;
            break;
         case "PB":
            registerCode = registers.PBr;
            break;
         case "PT":
            registerCode = registers.PTr;
            break;
         case "SB":
            registerCode = registers.SBr;
            break;
         case "ST":
            registerCode = registers.STr;
            break;
         case "HB":
            registerCode = registers.HBr;
            break;
         case "HT":
            registerCode = registers.HTr;
            break;
         case "LB":
            registerCode = registers.LBr;
            break;
         case "L1":
            registerCode = registers.L1r;
            break;
         case "L2":
            registerCode = registers.L2r;
            break;
         case "L3":
            registerCode = registers.L3r;
            break;
         case "L4":
            registerCode = registers.L4r;
            break;
         case "L5":
            registerCode = registers.L5r;
            break;
         case "L6":
            registerCode = registers.L6r;
            break;
         case "CP":
            registerCode = registers.CPr; 
            break;
         default: 
            registerCode = -1;
    
    }

    return registerCode;

 }

 function getRegisterName( r, ){
  
    var registerName;

    switch (r) {
      case registers.CBr:
        registerName = "CB";
        break;
      case registers.CTr:
        registerName ="CT";
	break;
      case registers.PBr:
        registerName ="PB";
	break;
      case registers.PTr:
        registerName ="PT";
	break;
      case registers.SBr:
        registerName ="SB";
	break;
      case registers.STr:
        registerName ="ST";
	break;
      case registers.HBr:
        registerName ="HB";
	break;
      case registers.HTr:
        registerName ="HT";
	break;
      case registers.LBr:
        registerName ="LB";
	break;
      case registers.L1r:
        registerName ="L1";
	break;
      case registers.L2r:
        registerName ="L2";
	break;
      case registers.L3r:
        registerName ="L3";
	break;
      case registers.L4r:
        registerName ="L4";
	break;
      case registers.L5r:
        registerName ="L5";
	break;
      case registers.L6r:
        registerName ="L6";
	break;
      case registers.CPr:
        registerName ="CP";
	break;
    }

    return registerName;
  
  } 




 function writeR ( leftbracket,  r,  rightbracket, data_string) {

    data_string += leftbracket;
    switch (r) {
      case "CB":
        data_string += "CB";
        break;
        case "CT":
        data_string += "CT";
	break;
      case "PB":
        data_string += "PB";
	break;
      case "PT":
        data_string += "PT";
	break;
      case "SB":
        data_string += "SB";
	break;
      case "ST":
        data_string += "ST";
	break;
      case "HB":
        data_string += "HB";
	break;
      case "HT":
        data_string += "HT";
	break;
      case "LB":
        data_string += "LB";
	break;
      case "L1":
        data_string += "L1";
	break;
      case "L2":
        data_string += "L2";
	break;
      case "L3":
        data_string += "L3";
	break;
      case "L4":
        data_string += "L4";
	break;
      case "L5":
        data_string += "L5";
	break;
      case "L6":
        data_string +="L6";
	break;
      case "CP":
        data_string +="CP";
	break;
    }

    data_string += rightbracket;
    return data_string;

  }



 function blankN(data_string) {
    data_string += "      ";
    return data_string;

}

function writeN (n,data_string) {
    data_string += "(" + n + ") ";
    if (n < 10)
        data_string +="  ";
    else if (n < 100)
        data_string += " ";

    return data_string;

  }

function writeD ( d,data_string) {
    data_string += d;
    return data_string;

  }

function writePrimitive (d,data_string) {
    switch (d) {
      case primitive_routines_address.idDisplacement:
        data_string +="id      ";
	break;
      case primitive_routines_address.notDisplacement:
        data_string +="not     ";
	break;
      case primitive_routines_address.andDisplacement:
        data_string +="and     ";
	break;
      case primitive_routines_address.orDisplacement:
        data_string +="or      ";
	break;
      case primitive_routines_address.succDisplacement:
        data_string +="succ    ";
	break;
      case primitive_routines_address.predDisplacement:
        data_string +="pred    ";
	break;
      case primitive_routines_address.negDisplacement:
        data_string +="neg     ";
	break;
      case primitive_routines_address.addDisplacement:
        data_string +="add     ";
	break;
      case primitive_routines_address.subDisplacement:
        data_string +="sub     ";
	break;
      case primitive_routines_address.multDisplacement:
        data_string +="mult    ";
	break;
      case primitive_routines_address.divDisplacement:
        data_string +="div     ";
	break;
      case primitive_routines_address.modDisplacement:
        data_string +="mod     ";
	break;
      case primitive_routines_address.ltDisplacement:
        data_string +="lt      ";
	break;
      case primitive_routines_address.leDisplacement:
        data_string +="le      ";
	break;
      case primitive_routines_address.geDisplacement:
        data_string +="ge      ";
	break;
      case primitive_routines_address.gtDisplacement:
        data_string +="gt      ";
	break;
      case primitive_routines_address.eqDisplacement:
        data_string += "eq      ";
	break;
      case primitive_routines_address.neDisplacement:
        data_string += "ne      ";
	break;
      case primitive_routines_address.eolDisplacement:
        data_string += "eol     ";
	break;
      case primitive_routines_address.eofDisplacement:
        data_string += "eof     ";
	break;
      case primitive_routines_address.getDisplacement:
        data_string += "get     ";
	break;
      case primitive_routines_address.putDisplacement:
        data_string += "put     ";
	break;
      case primitive_routines_address.geteolDisplacement:
        data_string += "geteol  ";
	break;
      case primitive_routines_address.puteolDisplacement:
        data_string += "puteol  ";
	break;
      case primitive_routines_address.getintDisplacement:
        data_string += "getint  ";
	break;
      case primitive_routines_address.putintDisplacement:
        data_string += "putint  ";
	break;
      case primitive_routines_address.newDisplacement:
        data_string += "new     ";
	break;
      case primitive_routines_address.disposeDisplacement:
        data_string += "dispose ";
	break;
    }

    return data_string;
  }




 function writeInstruction (instr) {

    var data_string = "";

    switch (instr.operation) {
      case "LOAD":
	data_string += "LOAD  ";
	data_string = writeN(instr.length,data_string);
	data_string =writeD(instr.operand,data_string);
	data_string =writeR('[', instr.register, ']',data_string);
	break;

      case "LOADA":
        data_string +="LOADA ";
        data_string = blankN(data_string);
        data_string = writeD(instr.operand,data_string);
        data_string = writeR('[', instr.register, ']',data_string);
        break;

      case "LOADI":
        data_string += "LOADI ";
        data_string = writeN(instr.length,data_string);
        break;

      case "LOADL":
        data_string += "LOADL ";
        data_string = blankN(data_string);
        data_string = writeD(instr.operand,data_string);
        break;

      case "STORE":
        data_string += "STORE ";
        data_string = writeN(instr.length,data_string);
        data_string = writeD(instr.operand,data_string);
        data_string = writeR('[', instr.register, ']',data_string);
        break;

      case "STOREI":
        data_string += "STOREI";
        data_string = writeN(instr.length,data_string);
        break;

      case "CALL":
        data_string += "CALL  ";
        if (getRegisterCode(instr.register) == registers.PBr) {
            data_string =  blankN(data_string);
            data_string = writePrimitive(instr.operand,data_string);
        } else {
            data_string = writeR('(', getRegisterName(instr.length), ')',data_string);
            data_string += "  ";
            data_string = writeD(instr.operand,data_string);
            data_string = writeR('[', instr.register, ']',data_string);
        }
        break;

      case "CALLI":
        data_string += "CALLI ";
	break;

      case "RETURN":
        data_string += "RETURN";
        data_string = writeN(instr.length,data_string);
        data_string = writeD(instr.operand,data_string);
        break;

      case "PUSH":
        data_string += "PUSH  ";
        data_string = blankN(data_string);
        data_string = writeD(instr.operand,data_string);
        break;

      case "POP":
        data_string += "POP   ";
        data_string = writeN(instr.length,data_string);
        data_string =  writeD(instr.operand,data_string);
        break;

      case "JUMP":
        data_string += "JUMP  ";
        data_string = blankN(data_string);
        data_string = writeD(instr.operand,data_string);
        data_string = writeR('[', instr.register, ']',data_string);
        break;

      case "JUMPI":
        data_string += "JUMPI ";
        break;

      case "JUMPIF":
        data_string += "JUMPIF";
        data_string = writeN(instr.length,data_string);
        data_string = writeD(instr.operand,data_string);
        data_string = writeR('[', instr.register, ']',data_string);
        break;

      case "HALT":
        data_string += "HALT  ";
    }

    displayContents(data_string);
  }



 function displayContents(contents) {
    var element = document.getElementById('file-content');
    element.textContent += contents;
  }
  
 function print_file(file_content){


    var size = file_content.length;

    element = document.getElementById('file_header');
    element.style.display = "inline-block"; 

    var element = document.getElementById('file-content');
    element.textContent = "";
    
    for ( var i = 0; i < size; i++) {

        var print_data = "  " + i.toString() + ": " 
        displayContents(print_data);
        writeInstruction(file_content[i]);
        displayContents("\n");

    }

}

document.getElementById('file-input').addEventListener('change', readFile, false)

 function readFile(e) {
    var file = e.target.files[0];
    if (!file) {
      return;
    }
    var reader = new FileReader();
    reader.onload = function(e) {
      var contents = e.target.result;
    json_parsed = JSON.parse(contents);
      print_file(json_parsed);
      
    };
    reader.readAsText(file);
  }


function load_Code(){

    var size = json_parsed.length;

    for (pos = 0; pos < size; pos++) {

        code[pos] = new Instruction(0,0,0,0);
        code[pos].op = getOperationCode(json_parsed[pos].operation);
        code[pos].r = getRegisterCode(json_parsed[pos].register);
        code[pos].n = parseInt(json_parsed[pos].length);
        code[pos].d = parseInt(json_parsed[pos].operand);

    }

    return pos;

}
