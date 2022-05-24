


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

        var print_data = "  " + i.toString() + ": " + file_content[i].operation + 
        " " + file_content[i].register + " " + 
        file_content[i].length + " " + 
        file_content[i].operand + "\n";

        displayContents(print_data);
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
