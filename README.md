# KeyboardTrackpointTouchPad

This is an Arduino sketch, designed for the <a href="https://store.arduino.cc/usa/arduino-due">Due</a>

It is connected to a Thinkpad T43 keyboard, TrackPoint and TouchPad.

The keyboard is a 10x17 matrix. Using the numerous digital interrupts of the Due, we attach ISR functions to the pins on the output of the matrix pins. Powering the input pins in sequence, we catch the interrupt and mark that key to be pressed.

TrackPoint uses +5v, GND, Data, Clock and Reset. It functions as a strange PS2 mouse. You skip the normal initialization steps, and simply pull the reset pin high, pause then pull it now.

Touchpad uses +5v, GND, Data and Clock. It functions as a standard PS2 mouse.
