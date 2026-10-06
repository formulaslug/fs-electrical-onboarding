# Terms
**Range** - the span between the lowest and highest values a sensor can measure

**Resolution** - The smallest change the sensor can register

**Accuracy** - How close the reading is to the true value, reported pressure to real pressure

**Precision** - How consistent repeated readings are when nothing changes, consistent readings in pressure

**Micro-Electro-Mechanical System (MEMS)** - Tiny mechanical parts built directly onto a chip. 
The sensors are very small and cheap, it has a microscopic membrane that will bend slightly as air pressure changes, and the chip converts that bend into an electrical reading.

**Microcontroller** - A tiny computer on a single chip that reads sensors, makes decisions, and sends data. 
On the car, microcontrollers collect sensor readings and send them to the telemetry system.

**Printed Circuit Board (PCB)** - The flat board, which is usually green, holds electronic parts and connects them with copper traces. 
Putting several sensors on the same PCB means mounting them on one board that's wired to one microcontroller

**Standard Temperature and Pressure (STP)** - An agreed-upon reference condition, 0° C and about 100,000 Pa 

# Common Sensor Output Interfaces
## Analog - has a smooth range from fully off to fully on, encompassing every level in between like a dimmer knob, versus an on and off switch. 

### How it sends data
The sensor puts out a voltage that rises and falls with pressure which travels down the wire to the microcontroller. The built-in ADC reads the voltage and turns it into a number which the microcontroller then converts into a pressure 

### Wires needed
Analog adds one signal wire that carries voltage, so on top of the wire that provides power to turn on the sensor and the wire for the ground, there are 3 total wires. 

### Multiple identical sensors
The power and ground wires can be shared among all the sensors, but each sensor still requires its own signal wire and ADC input pin on the microcontroller and each microcontroller only has a limited number of those pins. 

### Strengths
- Analog is simple, no protocol or code rules to set up, just read a voltage
- Identical sensors never conflict with each other because each has its own wire
- Easy to understand and test with basic tools

### Weaknesses 
- wires pick up stray electricity from motors and high-power cables which are in the racecar, the microcontroller can't tell them apart from a real reading
- Resolution is limited by the ADC
- Pin count, many sensors use up many pins

### Example



# Questions
