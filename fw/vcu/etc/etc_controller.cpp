//
// Created by Jackson Pinsonneault on 3/24/26.
//

#include "etc_controller.h"

// Assign appropriate GPIO objects depending on pin parameters
ETCController::ETCController(PinName APPS1_pin, PinName APPS2_pin) {
    AnalogIn APPS1_percent(APPS1_pin);
    AnalogIn APPS2_percent(APPS2_pin);
}

/* 
    Nice function to write which returns a wrapped version of the
    value given between 0 and 1 (-0.1 => 0, 10 => 1, 0.3 => 0.3).
*/
float ETCController::clamp(float value) {
    if (value < 0) {
        return 0;
    } else if (value > 1) {
        return 1;
    } else {
        return value;
    }
}

/*
    Simple function to write which returns a bool of true or false
    depending on whether low <= value <= high is true.
*/
bool ETCController::in_range(float value, float low, float high) {
    return (value >= low && value <= high);
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

    APPS1_pos = (APPS1_percent * 3.3 - APPS1_MIN_VOLTAGE) / (APPS1_MAX_VOLTAGE - APPS1_MIN_VOLTAGE);
    APPS2_pos = (APPS2_percent * 3.3 - APPS2_MIN_VOLTAGE) / (APPS2_MAX_VOLTAGE - APPS2_MIN_VOLTAGE);

    effective_pos = (APPS1_pos + APPS2_pos) / 2;

    if (effective_pos < PEDAL_DEADZONE_PERCENTAGE) {
        effective_pos = 0;
    }

    motor_torque_demand = effective_pos * MAX_TORQUE;

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

    implaus_out_of_range = !(in_range(APPS1_percent * 3.3, APPS1_MIN_VOLTAGE, APPS1_MAX_VOLTAGE) && 
                             in_range(APPS2_percent * 3.3, APPS2_MIN_VOLTAGE, APPS2_MAX_VOLTAGE));

    if (APPS1_pos > 0.1 or APPS2_pos > 0.1){
        if (std::abs(APPS1_pos - APPS2_pos) < 0.1) {
            implaus_deviation = false;
        } else {
            implaus_deviation = true;
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
    int64_t duration_ms implaus_duration = implaus_timer.elapsed_time().count() / 1000;
    if (implaus_deviation | implaus_out_of_range) {
        if (!implaus_timer.running()) {
            implaus_timer.start();
        }

        if (duration_ms > 100) {
            motor_torque_demand = 0;
        }
    } else {
        implaus_timer.stop();
        implaus_timer.reset();
    }
}
