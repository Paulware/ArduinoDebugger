Overview:
  <ul>
  <li>This project will allow you to set a breakpoint in your sketch and step through it</li>
  <li>Proper wiring to each device is supported and expected in some cases</li>
  <li>Actual Arduino libraries such as Keypad.cpp are used wherever possible.</li>
  </ul>
  
Supported Projects/Components
  <ul>
  <li>LEDSwitch.txt - LED goes on when switch is pressed</li>
  <li>Resistor5VSwitch.txt - LED goes on when switch is pressed</li>
  <li>Blinky.txt - LED goes on/off automatically</li> 
  <li>Digit3.txt - 3 Digit, 7 segment display interactive with momentary depress button</li>
  <li>Keypad.txt - 4x4 matrix keypad</li>
  <li>KeypadDisplay.txt - 4x4 matrix keypad and LCD Display</li>
  <li>LCDDisplay.txt - 4x16 character LCD Display </li>
  <li>SevenSeg.txt - Simple 1 digit seven segment display</li>
  </ul>

Free CPP Compiler:  
  The free cpp compiler that was used to build this project can be downloaded from
  http://sourceforge.net/projects/orwelldevcpp/ 

Build/Run instructions:
  <ul>
  <li>Download and install above cpp dev compiler</li>
  <li>Download ArduinoDebugger.zip from this github repository</li>
  <li>Unzip ArduinoDebugger.zip to C:\ArduinoDebugger</li>
  <li>Open C:\ArduinoDebugger\prjArduinoSimulator.dev in cpp dev</li>
  <li>Compile and Run, Open a project</li>
  <li>Rebuild All if the sketch.ino changes</li>
  <li>Set breakpoints, Debug</li>
  </ul> 
  
Online videos that demonstrate usage:
  [video1](http://www.youtube.com/watch?v=AdZ5GbDC1h0&feature=youtu.be)  
  [video2](http://www.youtube.com/watch?v=laa9VnRzuT0&feature=youtu.be)  
  [video3](http://www.youtube.com/watch?v=AdZ5GbDC1h0&feature=youtu.be)  
  [video4](http://youtu.be/_W_GPd936jg)
  
Last Tested 5/5/2013 on Windows OS:
  Windows 8
  
Last Tested with Arduino libraries from version
  1.0.2   
  
Questions/Comments
  paulware@hotmail.com
  
Help with projects
  [I can help with projects](http://fiverr.com/paulware/help-with-your-arduino-project)

<a href="https://tindie.com/shops/Paulware/?ref=offsite_badges&utm_source=sellers_Paulware&utm_medium=badges&utm_campaign=badge_large"><img src="https://s3.amazonaws.com/tindie-static/badges/tindie-large.png" alt="I sell on Tindie"></a>

I have recently discovered <a href="http://en.wikipedia.org/wiki/Test-driven_development">TDD</a> which dictates that<br>
all code changes be preceded by a test case enhancement.  While I don't have that many test-cases, I do have a suite of <br>
projects which are loaded and tested before every release.

Design Notes
<ul>
<li>Pull-up Resistor
<ul>
  <li>pinMode (pinNumber,INPUT);<li>
  <li>digitalWrite (pinNumber,1); // Set pull-up resistor</li>
  <li>Will have constValue.value = 1, and constValue.resistance = 20000</li>
</ul>
</li>
</ul>
  