//
// Created by Jackson Pinsonneault on 3/24/26.
//

#ifndef ETC_CONTROLLER_H
#define ETC_CONTROLLER_H

#include "mbed.h"

class ETCController {
public:

    /*
        Start of public variables
    */



    /*
        End of public variables
    */

    /*
        Public method definitions, don't edit
    */
    ETCController(PinName APPS1_pin, PinName APPS2_pin);

    void update_state();

private:
    /*
        Start of private variables
    */

    

    /*
        End of private variables
    */

    /*  
        !! IMPORTANT: ALL OF THE MIN/MAX VOLTAGES SHOULD BE !!
        !! RETUNED VIA SERIAL BEFORE TESTING ANYTHING       !!
    */

    static constexpr float APPS1_MIN_VOLTAGE = 0.396;
    static constexpr float APPS1_MAX_VOLTAGE = 1.086f;

    static constexpr float APPS2_MIN_VOLTAGE = 0.439f;
    static constexpr float APPS2_MAX_VOLTAGE = 1.133f;

    static constexpr float PEDAL_DEADZONE_PERCENTAGE = 0.05;

    static constexpr int16_t MAX_TORQUE = 32767 * 0.1; // Multiplied by 0.1 for controlled 
                                                       // motor torque during onboarding.

    float clamp(float value);

    bool in_range(float value, float low, float high);

    void update_implaus();
};

#endif
