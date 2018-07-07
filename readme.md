Overview:
  <ul>
  <li>This project will allow you to set a breakpoint in your sketch and step through it</li>
  <li>Proper wiring to each device is supported and expected in some cases</li>
  <li>Actual Arduino libraries such as Keypad.cpp are used wherever possible.</li>
  </ul>
  
Supported Projects/Components<br>
<TABLE>
<tr><th>Project Files</th><th>Components</th><th>Description</th></tr>
<tr><td>LEDSwitch.txt</td><td>LED, Momentary Depress Switch</td><td>LED goes on when switch is pressed</td></tr>
<tr><td>Resistor5VSwitch.txt</td><td>LED, Resistor, Momentary Depress Switch</td><td>LED goes on when switch is pressed</td></tr>
<tr><td>Blinky.txt</td><td>LED</td><td>LED goes on/off automatically</td></tr>
<tr><td>Digit3.txt</td><td>3 Digit 7 segment display, Momentary Depress Switch</td><td>7 segment display updates when momentary depress switch presed</td></tr>
<tr><td>Keypad.txt</td><td>4x4 matrix keypad</td><td>Serial output updates upon key press</td></tr>
<tr><td>KeypadDisplay.txt</td><td>4x4 matrix keypad, LCD Display</td><td>LCD display updates upon key press</td></tr>
<tr><td>LCDDisplay.txt</td><td>LCDDisplay, Momentary Depress Switch</td><td>LCD display updates when switch is pressed</td></tr>
<tr><td>SevenSeg.txt</td><td>7 segment display of single digit</td><td>7 segment digit increments upon switch press</td></tr>
<tr><td>RotaryDip.txt</td><td>Rotary Dip switch</td><td>Serial output updates when one of 3 rotary dip switches are changed</td></tr>
<tr><td>ShiftRegister.txt</td><td>74HC595 Shift Register, LED, Momentary Depress Switch</td><td>LEDs connected to shift register update when switch is pressed</td></tr>
<tr><td>Multiplexer.txt</td><td>4051 Multiplexer</td><td>When switch is depressed multiplexer chooses other input</td></tr>
</TABLE>

Free CPP Compiler:  
  The free cpp compiler that was used to build this project can be downloaded from
  http://sourceforge.net/projects/orwelldevcpp/ 

Build/Run instructions:
  <ul>
  <li>Download and install above cpp dev compiler</li>
  <li>Download ArduinoDebugger.zip from this github repository</li>
  <li>Unzip the contents of ArduinoDebugger-master.zip/ArduinoDebugger-master to C:\ArduinoDebugger</li>
  <li>Open C:\ArduinoDebugger\prjArduinoSimulator.dev in cpp dev</li>
  <li>Execute, Rebuild All from cpp compiler (F12)</li>
  <li>Execute, Compile and Run from cpp compiler (F11)</li>
  <li>Ignore Serial Monitor, and select Project, Open Project</li>
  <li>Select an existing project (like SevenSeg.txt)</li>
  <li>This will change a source file called: sketch.ino, so you must close the program and rebuild all (F12) and Run(F11) again</li>
  <li>Again select the same existing poject (like SevenSeg.txt) this time the sketh.ino will not change</li>
  <li>The graphical interface should now behave like expected, and breakpoints can be set in the cpp dev environment to step through the arduino code </li>
  </ul> 
  
Online videos that demonstrate usage:
<ul>
  <li>[video1](http://www.youtube.com/watch?v=AdZ5GbDC1h0&feature=youtu.be)</li>
  <li>[video2](http://www.youtube.com/watch?v=laa9VnRzuT0&feature=youtu.be)</li>
  <li>[video3](http://www.youtube.com/watch?v=AdZ5GbDC1h0&feature=youtu.be)</li>  
  <li>[3 Digit 7 segment display](http://youtu.be/_W_GPd936jg)</li>
  <li>[Rotary Dip](http://www.youtube.com/watch?v=vOSc0lCG9bM&feature=youtu.be)</li>
</ul>  
  
Last Tested 7/6/2018 on Windows OS:
  Windows 10
  
Last Tested with Arduino libraries from version
  1.0.2   
  
Questions/Comments
  paulware@hotmail.com
  
I have recently discovered <a href="http://en.wikipedia.org/wiki/Test-driven_development">TDD</a> which dictates that<br>
all code changes be preceded by a test case enhancement.  While I don't have that many test-cases, I do have a suite of <br>
projects which are loaded and tested before every release.

Design Notes
<ul>
<li>SimUtilities Class<br>
     Contains utilities to list all connections and set a value on the connection
</li>
<li>Pull-up Resistor
<ul>
  <li>pinMode (pinNumber,INPUT);<li>
  <li>digitalWrite (pinNumber,1); // Set pull-up resistor</li>
  <li>Will have constValue.value = 1, and constValue.resistance = 20000</li>
</ul>
</li>
</ul>
  
