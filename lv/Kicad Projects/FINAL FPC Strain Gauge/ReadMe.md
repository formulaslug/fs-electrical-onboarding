Overview:
This project is a temperature-compensated strain gauge using copper traces patterned directly onto a flexible PCB (FPC) to measure mechanical strain and vibrations.

The system converts strain-induced resistance changes into 24-bit digital measurements transmitted over SPI at a target of 1000 samples per second.

The project consists of two main components which can be found in the folder this markdown file is located:

1. FPC Strain Gauge

This is the main resistance sensor laid out on an JLCPCB-spec Flexible PCB. It has two pads that can be converted to connectors to be connected to the circuit PCB.

2. FPC Strain Gauge Circuit

This is where all the signals and logic are handles. The main FPC Gauge connects to this board with amplifies and samples the analog data to convert it to an digital output using an ADC.

How It Works:

1. Copper Trace Strain Gauges

Two perpendicular sepentine copper traces act as resistive strain guages. Mechanical deformation changes their resistances and this is what we measure in terms of raw data.

2. Wheatstone Half-Bridge

The gauges and two resistors and two 350 ohm resistros form a Wheatstone brdige. Opposing resistance changes produce a differential voltage proportional to strain, while similar temperature effects largely cancel.

3. INA333 Amplifier

The INA333 amplifies the small differential voltage. A buffered 1.65 V reference offset is used here.

4. Analog Filtering

An RC low-pass filter is used to reduce high-frequency interference before digitization.

5. ADS1220IRVAR ADC

The Texas Instruments ADS1220IRVAR is a 24-bit delta-sigma ADC in a 3.5 × 3.5 mm VQFN-16 package.
 
    a. Measures LOAD_SIGNAL relative to VREF_1V65
    b. Uses a 2.048 V internal reference
    c. Provides internal digital filtering
    d. Configured for 1 kS/s continuous conversion
    e. Operates from the board's 3.3 V supply
