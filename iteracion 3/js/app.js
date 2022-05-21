function changeWindow(ventana){
  
    var element;
  
    if (ventana == 1){
  
      element = document.getElementById('container2');
      element.style.display = "none";    
      element = document.getElementById('container');
      element.style.display = "inline-block"; 
    }
  
    else if (ventana == 2){
      element = document.getElementById('container');
      element.style.display = "none";    
      element = document.getElementById('container2');
      element.style.display = "inline-block"; 
    }
    else
      return;
  }
  
  function read_input(){
  
  var data = document.getElementById("inputData").value;
  element = document.getElementById("result");
  element.textContent = data;
  //element.textContent = element.textContent + data;
  
  }
  
  
  
  function readSingleFile(e) {
    var file = e.target.files[0];
    if (!file) {
      return;
    }
    var reader = new FileReader();
    reader.onload = function(e) {
      var contents = e.target.result;
      displayContents(contents);
      var parseado = JSON.parse(contents);
      console.log(parseado);
    };
    reader.readAsText(file);
  }
  
  function displayContents(contents) {
    var element = document.getElementById('file-content');
    element.textContent = contents;
  }
  
  document.getElementById('file-input')
    .addEventListener('change', readSingleFile, false);