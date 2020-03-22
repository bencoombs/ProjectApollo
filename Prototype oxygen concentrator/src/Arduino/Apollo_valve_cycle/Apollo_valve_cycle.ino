//
//    Valve cycling code for Project Apollo v1 prototype
//


// Connectivity:
// - Connect GND from Arduino to GND(-) on ULN2003 board 
// - Connect Vin from Arudino to 12V(+) on ULN2003 board and to (+) of 2-way valve motor and to (+) of 5-way valve motor
// - Connect PIN 2 pin from Arduino to IN PIN 1 on ULN2003 board
// - Connect PIN 3 pin from Arduino to IN PIN 2 on ULN2003 board
// - Connect OUT PIN 1 pin from ULN2003 board to (-) of 2-way valve
// - Connect OUT PIN 2 pin from ULN2003 board to (-) of 5-way valve
// - Program Arduino board
// - Verify that the LEDs blink in the right order
// - Connect 12V supply to Arduino (at least 1.5A current)
// - Verify that valves couple in the right order 


// PIN identifiers

// 
// PIN 2 on Arduino Uno
// - To be connnected to INPUT PIN 1 on ULN2003 board 
// - Which drives OUT PIN 1 on ULN2003 board 
// - Which drives (-) on 2-way valve
// 
int valve_2way = 2;

// 
// PIN 3 on Arduino Uno
// - To be connnected to INPUT PIN 2 on ULN2003 board 
// - Which drives OUT PIN 2 on ULN2003 board 
// - Which drives (-) on 5-way valve
// 
int valve_5way = 3;

// Scale in which timing values are expressed (as multiplies of the number below)
int timing_unit_scale_milliseconds = 1000;

// Time for opening the 2-way valve
// 1 time units 
int timing_valve_2way = 1; 

// Time for alternating the 5-way valve
// 8 time units 
int timing_valve_5way_alternating = 8; 

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(valve_2way, OUTPUT);
  pinMode(valve_5way, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void halfCycle(int state_5way)
{
  digitalWrite(LED_BUILTIN, state_5way);   // turn the built-in LED with the same value as 5-WAY state

  // Turn on 5-way
  digitalWrite(valve_5way, state_5way);    
  // Wait for 5-way to be opened for the given amount of time
  delay(timing_valve_5way_alternating * timing_unit_scale_milliseconds);

  // Turn on the 2-way briefly
  digitalWrite(valve_2way, HIGH);    
  delay(timing_valve_2way * timing_unit_scale_milliseconds);
  digitalWrite(valve_2way, LOW);    
}

void loop() {
  halfCycle(HIGH);
  halfCycle(LOW);  
}