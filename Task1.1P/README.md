Task 1.1P - Switching ON Lights

System Description
The system was intended to be used in a smart elderly care home situation. The porch light and hallway light will automatically turn on when Linda comes home and switches on the switch. The duration of the porch light and hallway is 30 and 60 seconds respectively. This enables one to have a better visibility and safety during night entry in the house.

Components Used
Arduino Nano 33 IoT
1 external LED
1 built-in LED on the Arduino
1 resistor
1 switch
Breadboard
Jumper wires

Explanation of the Code

Pin Definitions
The program starts with giving pins to the light outside the door, hallway and switch. The inbuilt LED on pin 13 is the porch light, the external LED on pin 12 is the hallway light and the switch is connected on pin 4.

Setup Function
The set up (function) establishes the pins of the porch light and the hallway light as an output since they operate LEDs. The switch pin has been set to INPUT and the pullup is set to INPUT which makes the switch readable without the addition of a pull up resistor in the circuit.

Loop Function
The loop () function constantly verifies that the switch is on. Once the switch is turned on, both of the lights get turned on simultaneously.

Light Timing
On activation, the porch light lasts 30 seconds and goes off. The corridor lighting is kept on an additional 30 seconds so that its active time is 60 seconds. This meets the requirement of the task.

Switch Handling
At the end it is put in a small while loop because the program will not permit a further activation until the switch is released. This will ensure that the system does not switch on and off repeatedly as long as the switch is on.
