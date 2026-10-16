# Pressure Sensor Onboarding Research - Suhas Meka

# Pros and Cons

In order to find a replacement for the BMP180 sensor we need to make sure that the new sensor has the exact same properties as the BMP180, but doesn't have cons that the BMP180 has. 

Pros:
- High Resolution and Accuracy
- Built-in Temperature Measurement & Calibration
- Ultra-Low Power Consumption
- Widespread Software

Cons:
- Fixed I2C Address
- Discontinued 
- Environment Sensitivity
- Slow sampling rates

# Recommended Communication Protocol: SPI
- Each SPI Sensor shares the same 3 wires (MOSI, MISO, SCK), but uses its own dedicated CS pin. 
- We can connect these CS wires to the microcontroller where the microcontroller can collect data from any sensor whenever it wants to. 
- Since we are physically connecting the CS wire to the Microcontroller there shouldn't be any problems with the microcontroller not being able to identify which is which sensor. 
- The SPI Sensor each share the 3 wires, we can add more SPI Sensors to the microcontroller, compared to the I2C Sensors. 
- More pressure sensors in one microcontroller allows us enabling faster data acquisition for battery cooling monitoring and aero simulation. 

# Key Parameters: 
1. Pressure Measurement Range: The Pressure range that the sensor can safely and accurately measure
      -Makes sure that the sensor won't saturate
2. Accuracy: how closely the reading matches the true atmospheric pressure.
       -Crucial to fully understand the pressure of the battery during different race conditions. 
3. Sampling Rate: How many measurements can the sensor output per second.
        -Higher sampling rates can help us understand the true pattern of the pressure/airflow of the battery. 

# Recommendation Replacement: 
-BMP280: Added SPI support, but contains the same features as the BMP180
-BMP390: SPI Sensor: higher accuracy and output speed. 

#Sensor Design Case
- We can make a sensor that follow the SPI sensor design, having 4 wires where 3 of them are shared, and the last unique wire is for the microcontroller to identify which sensor is which. With this we can connect multiple sensors to the motherboard. Hence increasing output. 



