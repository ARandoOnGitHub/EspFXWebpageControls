#include <Arduino.h>
//#include <pgmspace.h>
//// Coppy and paste HTML code here

///*

//stores raw literal
const char PAGE_MAIN[] PROGMEM = R"=====(
<!DOCTYPE html>
<!-- put into data folder when using SPIFFS -->
<html>
     <head>
        <link rel="stylesheet" href="styles.css">
        <title> 
            ESP32 Webpage Testing
        </title>
     </head>
     <body>
        <hl> 
            cskfbfhb
        </hl>
 <title>Guitar FX Control</title>
</head>
<body>
  <h1>Guitar FX Control</h1>
  <h2> Controls</h2>
  <h2>FX Selector</h2>
  <select id="selector" >
  <!-- onchange="updateSelector()"> -->
  </select>
  <p>You selected: <span id="selectedValue"></span></p> <!-- sainity check for selected value -->
  <h3>Internal or External FX</h3>
  <!-- <button type = "button" onclick ="change()" value = External>sefdbg </button>  -->
  <input
   onclick="change()" type="button" value="External" id="myButton1">
  </input>
<br>

<h3>Control 1</h3>
  <input type="range" min="0" max="100" value="50" class="slider" id="ctr1">
  Value: <span id='value1'></span> </span>%<br>

<h3>Control 2</h3>
  <input type="range" min="0" max="100" value="50" class="slider" id="ctr2">
  Value: <span id='value2'></span> </span>%<br>

  <h3>Control 3</h3>
    <input type="range" min="0" max="100" value="50" class="slider" id="ctr3">
    Value: <span id='value3'></span> </span>%<br>
<script>
//might put this in a seperate file later
var Socket;
function init() {
  Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
  Socket.onmessage = function(event){
    processCommand(event);
  };
}
// selector change/toggle code
let currentState = 'original';
function change() {
  var selector = document.getElementById("selector");
  var originalOptions = [
    { text: 'E1', value: 'E1' },
    { text: 'E2', value: 'E2' },
    { text: 'E3', value: 'E3' },
    { text: 'E4', value: 'E4' },
    { text: 'E5', value: 'E5' },
    { text: 'E6', value: 'E6' },
    { text: 'E7', value: 'E7' },
    { text: 'E8', value: 'E8' },
  ];
  var newOptions = [
    { text: 'P1', value: 'P1' },
    { text: 'P2', value: 'P2' },
    { text: 'P3', value: 'P3' },
    { text: 'P4', value: 'P4' },
    { text: 'P5', value: 'P5' },
    { text: 'P6', value: 'P6' },
    { text: 'P7', value: 'P7' },
    { text: 'P8', value: 'P8' },
  ];

  if (currentState === 'original') {
    currentState = 'new';
    updateOptions(selector, newOptions);
  } else {
    currentState = 'original';
    updateOptions(selector, originalOptions);
  }

  
    var elem = document.getElementById("myButton1");
    if (elem.value=="Internal") elem.value = "External";
    else elem.value = "Internal";}
function updateOptions(selector, options) {
  while (selector.options.length > 0) {
    selector.remove(0);
  }
  options.forEach((option) => {
    const newOption = document.createElement('option');
    newOption.text = option.text;
    newOption.value = option.value;
    selector.add(newOption);
  });
}
// get selected value from selector, the commented out stuff is same but longer
//const dropdown = document.getElementById('selector');
//const selectedValueDisplay = document.getElementById('selectedValue');
document.getElementById('selector').addEventListener('change', selection)// {
//document.getElementById('selectedValue').textContent = this.value;
   // });

function selection(){// shows the selected value
  document.getElementById('selectedValue').textContent = this.value;
  var selected = this.value
  console.log(selected);
//add esp32 logic

var msg = {

  type: 'Selected',
  value: selected

};

Socket.send(JSON.stringify(msg));
}

  // Get references to the slider elements and their corresponding span elements
  var slider1 = document.getElementById('ctr1');
  var slider2 = document.getElementById('ctr2');
  var slider3 = document.getElementById('ctr3');
  var valueSpan1 = document.getElementById('value1');
  var valueSpan2 = document.getElementById('value2');
  var valueSpan3 = document.getElementById('value3');

  // Event listeners for slider changes
  slider1.addEventListener('input', function() {
    valueSpan1.textContent = this.value; // Update the span value
   // console.log("Slider 1 Value:", this.value); // Log the value to the console
   var slider1val = this.value
    console.log("Slider 1 Value:", slider1val);

    //insert esp32 code here
  
    var msg = {
      type: 'slider1',
      value: slider1val

      };
      
      Socket.send(JSON.stringify(msg));
    
  });

  slider2.addEventListener('input', function() {
    valueSpan2.textContent = this.value  ;
    //console.log("Slider 2 Value:", this.value);

    var slider2val = this.value
    console.log("Slider 2 Value:", slider2val);

    //insert esp32 code here

    var msg = {
      type: 'slider2',
      value: slider2val

      };
      
      Socket.send(JSON.stringify(msg));
  });
  slider3.addEventListener('input', function() {
    valueSpan3.textContent = this.value;
    var slider3val = this.value
    console.log("Slider 3 Value:", slider3val);
    //console.log("Slider 3 Value:", this.value);
    
    //insert esp32 code here
    var msg = {
      type: 'slider3',
      value: slider3val

      };
      Socket.send(JSON.stringify(msg));
  });
function processCommand(event){
  var obj = JSON.parse(event.data);
  var type = obj.type
  if (type.localeCompare("slider1val") == 0 ) {
    var slider1val = parseInt(obj.value);
    console.log(slider1val);
    slider1.value = slider1val;
    output.innerHTML = slider1val;
}
window.onload = function(event){
  init();
}
}   
 </script>
</html>
)=====";

//*/
