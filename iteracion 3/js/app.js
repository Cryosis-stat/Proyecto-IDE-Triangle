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
  
