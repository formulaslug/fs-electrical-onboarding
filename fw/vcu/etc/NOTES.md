**NOTES**
(so that I have a place within VSCode to write things down as I work)
(because what is going on)

    - alright... wrote clamp() and in_range() okay
    - now trying to figure out how to write the constructor for ETC_Controller class
        - want to understand the class and the use of the object made from that class so i can write informedly (assuming that's a word)
    - i already found the PIN names from the kicad schematic
        - APPS_1 -- ADC1_IN11
        - APPS_2 -- ADC1_IN12
    - APPS = "Accelerator Pedal Position Sensor"
    - Glossary says APPS *RETURNS* a voltage... inferring that it's how we receive info on how far the accelerator pedal's been pressed
        - Have to convert this to . . . what?
        - "writing basic firmware using MBed to write a primitive ETC with appropriate pins from the fs-4 VCU schematic"