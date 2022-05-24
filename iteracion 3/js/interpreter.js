

var console_output = document.getElementById("console_data");  //console output to write
var buttom_pressed = false
var input_data; // place to save data from the input text form in the console


//event tha occur when the enter buttom in the console is pressed
function setPressed(){
  buttom_pressed = true;

  input_data = document.getElementById("inputData").value;
  document.getElementById("inputData").value = "";

  document.getElementById("inputData").disabled = true;
  document.getElementById("enter_input").disabled = true;
  
}


var data = new Array(1024);
//Data stores registers

//final
var CB = 0;
var SB = 0;
var HB = 1024;  //uper bound of data array

var CT;
var CP;
var ST;
var HT;
var LB;
var program_status;

var isNumber = true;


//Status values

//final
const status_values = {
running :0,
halted :1,
failedDataStoreFull : 2,
failedInvalidCodeAddress : 3,
failedInvalidInstruction : 4,
failedOverflow : 5,
failedZeroDivide : 6,
failedIOError : 7

};


//static
var accumulator;

function content( r ){ //Returns ...
    switch(r){
      case registers.CBr:
        return CB;
      case registers.CTr:
        return CT;
      case registers.PBr:
        return PB;
      case registers.PTr:
        return PT;
      case registers.SBr:
        return SB;
      case registers.STr:
        return ST;
      case registers.HBr:
        return HB;
      case registers.HTr:
        return HT;
      case registers.LBr:
        return LB;
      case registers.L1r:
        return data[LB];
      case registers.L2r:
        return data[data[LB]];
      case registers.L3r:
        return data[data[data[LB]]];
      case registers.L4r:
        return data[data[data[data[LB]]]];
      case registers.L5r:
        return data[data[data[data[data[LB]]]]];
      case registers.L6r:
        return data[data[data[data[data[data[LB]]]]]];
      case registers.CPr:
        return CP;
      default:
        return 0;
    }
}

//Program status
function dump(){ //Writes the state of the program if a error occur
    var addr;
    var staticLink;
    var dynamicLink;
    var localRegNum;

    console_output.textContent += "\nState of data store and registers\n\n";

    if(HT == HB){
      console_output.textContent += "            |--------|          (heap is empty)\n";
    }
    else{
      console_output.textContent +=("       HB-->\n");
      console_output.textContent +=("            |--------|\n");

        for(addr = HB - 1; addr >= HT; addr--){
          console_output.textContent +=(addr + ":\n");
            if (addr == HT)
            console_output.textContent +=(" HT-->");
            else
            console_output.textContent +=("      ");

            console_output.textContent +=("|"+data[addr]+"|\n");
        }
        console_output.textContent +=("            |--------|\n");
    }
    console_output.textContent +=("            |////////|\n");
    console_output.textContent +=("            |////////|\n");
    if (ST == SB){
      console_output.textContent +=("            |--------|          (stack is empty)\n");
    } 
    else{
        dynamicLink = LB;
        staticLink = LB;
        localRegNum = registers.LBr;
        console_output.textContent +=("      ST--> |////////|\n");
        console_output.textContent +=("            |--------|\n");

        for(addr = ST - 1; addr >= SB; addr--){
          console_output.textContent +=(addr + ":");
            if (addr == SB)
            console_output.textContent +=(" SB-->");
            else if (addr == staticLink){
                    switch (localRegNum) {
                        case registers.LBr:
                          console_output.textContent +=(" LB-->");
                        break;
                        case registers.L1r:
                          console_output.textContent +=(" L1-->");
                        break;
                        case registers.L2r:
                          console_output.textContent +=(" L2-->");
                        break;
                        case registers.L3r:
                          console_output.textContent +=(" L3-->");
                        break;
                        case registers.L4r:
                          console_output.textContent +=(" L4-->");
                        break;
                        case registers.L5r:
                          console_output.textContent +=(" L5-->");
                        break;
                        case registers.L6r:
                          console_output.textContent +=(" L6-->");
                        break;
                    }
                    staticLink = data[addr];
                    localRegNum++;
            } else{
              console_output.textContent +=("      ");
            }
            if ((addr == dynamicLink) && (dynamicLink != SB))
            console_output.textContent +=("|SL= "+ data[addr] +"|");
            else if ((addr == dynamicLink + 1) && (dynamicLink != SB))
            console_output.textContent +=("|DL="+data[addr] + "|");
            else if ((addr == dynamicLink+2)&&(dynamicLink != SB))
            console_output.textContent +=("|RA="+ data[addr] +"|");
            else
            console_output.textContent +=("|"+ data[addr] +"|");
            console_output.textContent +=("\n");
            if (addr == dynamicLink){
              console_output.textContent +=("            |--------|\n");
                dynamicLink = data[addr + 1];
            }
        }
    }
    console_output.textContent +=("\n");
}

function showStatus(){ // Writes an indication of whether and why the program has terminated.

  console_output.textContent +=("\n");
    switch (program_status) {
      case status_values.running:
        console_output.textContent +=("Program is running.\n");
        break;
      case status_values.halted:
        console_output.textContent +=("Program has halted normally.\n");
        break;
      case status_values.failedDataStoreFull:
        console_output.textContent +=("Program has failed due to exhaustion of Data Store.\n");
        break;
      case status_values.failedInvalidCodeAddress:
        console_output.textContent +=("Program has failed due to an invalid code address.\n");
        break;
      case status_values.failedInvalidInstruction:
        console_output.textContent +=("Program has failed due to an invalid instruction.\n");
        break;
      case status_values.failedOverflow:
        console_output.textContent +=("Program has failed due to overflow.\n");
        break;
      case status_values.failedZeroDivide:
        console_output.textContent +=("Program has failed due to division by zero.\n");
        break;
      case status_values.failedIOError:
        console_output.textContent +=("Program has failed due to an IO error.\n");
        break;
    }
    if (program_status != status_values.halted)
      dump();

}


//Interpretation

// Signals failure if there is not enough space to expand the stack or
// heap by spaceNeeded.
function checkSpace( spaceNeeded){ 

    if (HT - ST < spaceNeeded){
      program_status = status_values.failedDataStoreFull;
    }
}


// Tests whether the given datum represents true.
function isTrue( datum){ 
    if(datum == trueRep){
        return true;
    } else{
        return false;
    }
}

// Tests whether two multi-word objects are equal, given their common
// size and their base addresses.
function equal( size,  addr1,  addr2){ 

     eq = true;
     index = 0;

    while ((eq == 1) && (index < size)){
        if (data[addr1 + index] == data[addr2 + index])
            index = index + 1;
        else
            eq = false;
    }
    return eq;
}


// Signals failure if the datum is too large to fit into a single word,
// otherwise returns the datum as a single word.
function overflowChecked(datum){

    if ((-maxintRep <= datum) && (datum <= maxintRep))
      return  datum;
    else {
      program_status = status_values.failedOverflow;
      return 0;
    }
}

function toInt( b){
    
    if (b)
        return trueRep;
    else
        return falseRep;
}


var currentChar;

function verify_Number(value) {
  return !isNaN(value)
}


//function to process integers from the console input
async function readInt(){

  isNumber = true;

  document.getElementById("inputData").disabled = false;
  document.getElementById("enter_input").disabled = false;  


  await waitingButtomPressed()

  if (verify_Number(input_data)){
    return parseInt(input_data);
  }
  else{
    isNumber = false;
    return 0;
  }

}

//function to process chars from the console input
async function getChar(){

  document.getElementById("inputData").disabled = false;
  document.getElementById("enter_input").disabled = false;  

  await waitingButtomPressed()

  return input_data.charAt(0);

}


//function to wait for the input from the user
function waitingButtomPressed() {
  return new Promise((resolve) => {
    document.getElementById('enter_input').addEventListener('click', setPressed)
    function setPressed() {
      if (buttom_pressed) {
        document.getElementById('enter_input').removeEventListener('click', setPressed)
        resolve();
      }
    }
  });
}


// Invokes the given primitive routine.

async function callPrimitive ( primitiveDisplacement) {

    var addr;
    var size;
    var ch;

    switch (primitiveDisplacement) {
      case primitive_routines_address.idDisplacement:
        break; // nothing to be done
      case primitive_routines_address.notDisplacement:
        data[ST - 1] = toInt(!isTrue(data[ST - 1]));
        break;
      case primitive_routines_address.andDisplacement:
        ST = ST - 1;
        data[ST - 1] = toInt(isTrue(data[ST - 1]) & isTrue(data[ST]));
        break;
      case primitive_routines_address.orDisplacement:
        ST = ST - 1;
        data[ST - 1] = toInt(isTrue(data[ST - 1]) | isTrue(data[ST]));
        break;
      case primitive_routines_address.succDisplacement:
        data[ST - 1] = overflowChecked(data[ST - 1] + 1);
        break;
      case primitive_routines_address.predDisplacement:
        data[ST - 1] = overflowChecked(data[ST - 1] - 1);
        break;
      case primitive_routines_address.negDisplacement:
        data[ST - 1] = -data[ST - 1];
        break;
      case primitive_routines_address.addDisplacement:
        ST = ST - 1;
        accumulator = data[ST - 1];
        data[ST - 1] = overflowChecked(accumulator + data[ST]);
        break;
      case primitive_routines_address.subDisplacement:
        ST = ST - 1;
        accumulator = data[ST - 1];
        data[ST - 1] = overflowChecked(accumulator - data[ST]);
        break;
      case primitive_routines_address.multDisplacement:
        ST = ST - 1;
        accumulator = data[ST - 1];
        data[ST - 1] = overflowChecked(accumulator * data[ST]);
        break;
      case primitive_routines_address.divDisplacement:
        ST = ST - 1;
        accumulator = data[ST - 1];
        if (data[ST] != 0)
          data[ST - 1] =  (accumulator / data[ST]);
        else
        program_status = status_values.failedZeroDivide;
        break;
      case primitive_routines_address.modDisplacement:
        ST = ST - 1;
        accumulator = data[ST - 1];
        if (data[ST] != 0)
          data[ST - 1] = (int) (accumulator % data[ST]);
        else
        program_status = status_values.failedZeroDivide;
        break;
      case primitive_routines_address.ltDisplacement:
        ST = ST - 1;
        data[ST - 1] = toInt(data[ST - 1] < data[ST]);
        break;
      case primitive_routines_address.leDisplacement:
        ST = ST - 1;
        data[ST - 1] = toInt(data[ST - 1] <= data[ST]);
        break;
      case primitive_routines_address.geDisplacement:
        ST = ST - 1;
        data[ST - 1] = toInt(data[ST - 1] >= data[ST]);
        break;
      case primitive_routines_address.gtDisplacement:
        ST = ST - 1;
        data[ST - 1] = toInt(data[ST - 1] > data[ST]);
        break;
      case primitive_routines_address.eqDisplacement:
        size = data[ST - 1]; // size of each comparand
        ST = ST - 2 * size;
        data[ST - 1] = toInt(equal(size, ST - 1, ST - 1 + size));
        break;
      case primitive_routines_address.neDisplacement:
        size = data[ST - 1]; // size of each comparand
        ST = ST - 2 * size;
        data[ST - 1] = toInt(! equal(size, ST - 1, ST - 1 + size));
        break;
      case primitive_routines_address.eolDisplacement:
        data[ST] = toInt(currentChar == '\n');
        ST = ST + 1;
        break;
      case primitive_routines_address.eofDisplacement:
        data[ST] = toInt(currentChar == -1);
        ST = ST + 1;
        break;
      case primitive_routines_address.getDisplacement:
        ST = ST - 1;
        addr = data[ST];
        //try {
          currentChar = await getChar();
        //} catch (java.io.IOException s) {
        //  program_status = status_values.failedIOError;
        //}
        data[addr] = currentChar.charCodeAt(0);
        break;
      case primitive_routines_address.putDisplacement:
        ST = ST - 1;
        ch =   String.fromCharCode(data[ST]);
        console_output.textContent += ch ;
        break;
      case primitive_routines_address.geteolDisplacement:
        //try {
          while ((currentChar = getchar( )) != '\n');
        //printf("got in geteolDisplacement\n");       /////Falta implementarse
        //} catch (java.io.IOException s) {
        //  program_status = status_values.failedIOError;
        //}
        break;
      case primitive_routines_address.puteolDisplacement:
        console_output.textContent +=("\n");
        break;
      case primitive_routines_address.getintDisplacement:
        ST = ST - 1;
        addr = data[ST];

        //cambio a la funcion de Java y C, esta usa await / async para esperar
        accumulator = await readInt();           

        if (isNumber == false)
        program_status = status_values.failedIOError;

        data[addr] = parseInt(accumulator);
        break;
      case primitive_routines_address.putintDisplacement:
        ST = ST - 1;
        accumulator = data[ST];
        console_output.textContent +=(accumulator);
        break;
      case primitive_routines_address.newDisplacement:
        size = data[ST - 1];
        checkSpace(size);
        HT = HT - size;
        data[ST - 1] = HT;
        break;
      case primitive_routines_address.disposeDisplacement:
        ST = ST - 1; // no action taken at present
        break;
    }

}

    // Runs the program in code store.

async function interpretProgram() {

    var currentInstr = new Instruction(0,0,0,0);
    var op, r, n, d, addr, index;

    // Initialize registers ...
    ST = SB;
    HT = HB;
    LB = SB;
    CP = CB;

    program_status = status_values.running;

    do {
      // Fetch instruction ...
      currentInstr = code[CP];
      // Decode instruction ...
      op = currentInstr.op;
      r = currentInstr.r;
      n = currentInstr.n;
      d = currentInstr.d;

      //printf("\n opcode: %d, registercode: %d , length: %d, value: %d\n",op,r,n,d);

      // Execute instruction ...
      switch (op) {
        case machine_operation.LOADop:
          addr = d + content(r);
          checkSpace(n);
          for (index = 0; index < n; index++)
            data[ST + index] = data[addr + index];
          ST = ST + n;
          CP = CP + 1;
          break;
        case machine_operation.LOADAop:
          addr = d + content(r);
          checkSpace(1);
          data[ST] = addr;
          ST = ST + 1;
          CP = CP + 1;
          break;
        case machine_operation.LOADIop:
          ST = ST - 1;
          addr = data[ST];
          checkSpace(n);
          for (index = 0; index < n; index++)
            data[ST + index] = data[addr + index];
          ST = ST + n;
          CP = CP + 1;
          break;
        case machine_operation.LOADLop:
          checkSpace(1);
          data[ST] = d;
          ST = ST + 1;
          CP = CP + 1;
          break;
        case machine_operation.STOREop:
          addr = d + content(r);
          ST = ST - n;
          for (index = 0; index < n; index++)
            data[addr + index] = data[ST + index];
          CP = CP + 1;
          break;
        case machine_operation.STOREIop:
          ST = ST - 1;
          addr = data[ST];
          ST = ST - n;
          for (index = 0; index < n; index++)
            data[addr + index] = data[ST + index];
          CP = CP + 1;
          break;
        case machine_operation.CALLop:
          addr = d + content(r);
          if (addr >= PB) {
            await callPrimitive(addr - PB);
            CP = CP + 1;
          } else {
            checkSpace(3);
            if ((0 <= n) && (n <= 15))
              data[ST] = content(n); // static link
            else
            program_status = status_values.failedInvalidInstruction;
            data[ST + 1] = LB; // dynamic link
            data[ST + 2] = CP + 1; // return address
            LB = ST;
            ST = ST + 3;
            CP = addr;
          }
          break;
        case machine_operation.CALLIop:
          ST = ST - 2;
          addr = data[ST + 1];
          if (addr >= PB) {
            await callPrimitive(addr - PB);
            CP = CP + 1;
          } else {
            // data[ST] = static link already
            data[ST + 1] = LB; // dynamic link
            data[ST + 2] = CP + 1; // return address
            LB = ST;
            ST = ST + 3;
            CP = addr;
          }
          break;
        case machine_operation.RETURNop:
          addr = LB - d;
          CP = data[LB + 2];
          LB = data[LB + 1];
          ST = ST - n;
          for (index = 0; index < n; index++)
            data[addr + index] = data[ST + index];
          ST = addr + n;
          break;
        case machine_operation.PUSHop:
          checkSpace(d);
          ST = ST + d;
          CP = CP + 1;
          break;
        case machine_operation.POPop:
          addr = ST - n - d;
          ST = ST - n;
          for (index = 0; index < n; index++)
            data[addr + index] = data[ST + index];
          ST = addr + n;
          CP = CP + 1;
          break;
        case machine_operation.JUMPop:
          CP = d + content(r);
          break;
        case machine_operation.JUMPIop:
          ST = ST - 1;
          CP = data[ST];
          break;
        case machine_operation.JUMPIFop:
          ST = ST - 1;
          if (data[ST] == n)
            CP = d + content(r);
          else
            CP = CP + 1;
          break;
        case machine_operation.HALTop:
          program_status = status_values.halted;
          break;
      }
      if ((CP < CB) || (CP >= CT))
      program_status = status_values.failedInvalidCodeAddress;
    } while (program_status == status_values.running);

}

async function interprete( instructions_amount){

  console_output.textContent = "";

  element = document.getElementById('container');
  element.style.display = "none";    
  element = document.getElementById('container2');
  element.style.display = "inline-block";

  console_output.textContent += "********** TAM Interpreter (JavaScript Version 1) **********\n\n" ;

    CT = instructions_amount;
    await interpretProgram();
    showStatus();

    
}
