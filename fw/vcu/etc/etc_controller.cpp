//
// Created by Jackson Pinsonneault on 3/24/26.
//

#include "etc_controller.h"


// Assign appropriate GPIO objects depending on pin parameters
ETCController::ETCController(PinName APPS1_pin, PinName APPS2_pin) :
APPS1_in(APPS1_pin), APPS2_in(APPS2_pin) {
}

/* 
    Nice function to write which returns a wrapped version of the
    value given between 0 and 1 (-0.1 => 0, 10 => 1, 0.3 => 0.3).
*/
float ETCController::clamp(float value) {
    if (value < 0.0f) return 0.0f;
    if (value > 1.0f) return 1.0f;
    return value;
}

/*
    Simple function to write which returns a bool of true or false
    depending on whether low <= value <= high is true.
*/
bool ETCController::in_range(float value, float low, float high) {
    return value >= low && value <= high;
}

/*
    Complicated method with the goal of refreshing voltages,
    pedal positions, implausibilities, and motor torque demand.
*/
void ETCController::update_state() {
    /*
        Retrieve both APPS sensor voltages, determine pedal
        positions from globally set variables in header file, 
        then calculate a motor torque demand based off the 
        average if the two positions. 

        If you want an extra challenge, include the pedal
        deadzone percentage when determining pedal positions. 
        If you want to get really difficult, maybe even 
        include your own pedal mapping to make it non linear!
    */

    //  Uses curve of -(1/(1-h)^2)(x-1)^2+1 to both curve and provide a deadzone to the variable
    const float read = (APPS1_in.read() + APPS2_in.read())/2.0f-1;
    const float curved = clamp(-(1.0f/((1.0f-PEDAL_DEADZONE_PERCENTAGE)*(1.0f-PEDAL_DEADZONE_PERCENTAGE)))
        *(read*read)+1.0f);

    const float torque = curved*MAX_TORQUE;

    // Sets the static TARGET_TORQUE that will be used in the CAN bus
    TARGET_TORQUE = torque;

    /*
        Finish the step listed above.
    */

    // Here to simplify this function and readability.
    update_implausibilities();
}

/*
    Timer based logic for the ETC to be rules compliant. MUST
    include rules T.4.2.4, T.4.2.9 (out of range).
*/
void ETCController::update_implausibilities() {
    /*
        Start of implaus logic checking.
    */
    Timer timer;

    //APPS1 and APPS2 readings deviate by >10% (for >100ms) (T.4.2.4)
    timer.start();
    while (APPS1_in.read() < 0.9f*APPS2_in.read() || APPS2_in.read() < 0.9f*APPS1_in.read()) {
        if (timer.elapsed_time().count() >= 100000) {
            printf("APPS1 and APPS2 readings deviate by >10%% (for >100ms) (T.4.2.4)");
            //Write an error to the CAN?
            T_4_2_4_ERROR = true;
        }
    }

    //I don't see a T.4.2.9, so I'm assuming you meant T.4.2.10
    //APPS1 or APPS2 reading is outside of expected voltage range (for >100ms) (T.4.2.10)
    timer.reset();
    while (!in_range(APPS1_in.read_voltage(), APPS1_MIN_VOLTAGE, APPS1_MAX_VOLTAGE) ||
        !in_range(APPS2_in.read_voltage(), APPS2_MIN_VOLTAGE, APPS2_MAX_VOLTAGE)) {
        if (timer.elapsed_time().count() >= 100000) {
            printf("APPS1 or APPS2 reading is outside of expected voltage range (for >100ms) (T.4.2.10)");
            //Somehow write an error to the CAN?
            T_4_2_10_ERROR = true;
        }
    }




    /*
        End of implaus logic checking.
    */

    /*
        Check how long each implaus has been active for and
        update the actual implaus result if it's been active 
        for too long.
    */

    
}
