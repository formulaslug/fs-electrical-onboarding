//
// Created by Jackson Pinsonneault on 3/24/26.
//

#ifndef ETC_CONTROLLER_H
#define ETC_CONTROLLER_H

#include "mbed.h"

Timer implaus1_timer;
Timer implaus2_timer;
Timer implaus3_timer;
Timer implaus4_timer;

class ETCController {
public:

    /*
        Start of public variables
    */
   // list all variables used in etc_controller.cpp
   // make everything private and use getters and setters to be safe
    /*
        End of public variables
    */

    /*
        Public method definitions, don't edit
    */
    ETCController(PinName APPS1_pin, PinName APPS2_pin) {}; //constructor

    void update_state();

private:
    /*
        Start of private variables
    */
   //input variables
    float apps1_voltage;
    float apps2_voltage;

    //implaus variables
        //fault types
    bool apps1_out_of_range;
    bool apps2_out_of_range;
    bool pre_offset_apps_is_matching;
    bool post_offset_apps_is_matching;
    bool implaus_1;
    bool implaus_2;
    bool implaus_3;
    bool implaus_4;
    

    bool gen_faulting;
    bool gen_implaus;
    int implaus_timer_count;

    //pedal position variables
    float apps_1_volt_increment = 0.0069;
    int apps_1_pedal_position;
    float apps_2_volt_increment = 0.00694;
    int apps_2_pedal_position;

    //torque variables
    int16_t torque_apps_1 = 0;
    int16_t torque_apps_2 = 0;
    int calculated_torque = 0;


    void calculate_torque(int apps_1_pedal_position, int apps_2_pedal_position);

    void apps_1_pedal_position_calc(int apps1_voltage , int apps_1_volt_increment);

    void apps_2_pedal_position_calc(int apps2_voltage , int apps_2_volt_increment);
    
    /*
        End of private variables
    */

    /*  
        !! IMPORTANT: All global voltages are based off     !!
        !! an older testing time. Still, voltages           !!
        !! should always be checked and updated if wrong.   !!
    */

    static constexpr float APPS1_MIN_VOLTAGE = 0.396; //constexpr makes evaluate at compile time not run time      
    static constexpr float APPS1_MAX_VOLTAGE = 1.086f;

    static constexpr float APPS2_MIN_VOLTAGE = 0.439f;
    static constexpr float APPS2_MAX_VOLTAGE = 1.133f;

    static constexpr float PEDAL_DEADZONE_PERCENTAGE = 0.03;

    static constexpr int16_t MAX_TORQUE = 32767 * 0.1; // Multiplied by 0.1 for controlled 
                                                       // motor torque during onboarding.

    float clamp(float value);
//im confused on clamp and in_range. if the value is outside the range, should we clamp it?
    bool in_range(float value, float low, float high);

    void update_implausibilities();
};

#endif
