//
// Created by Jackson Pinsonneault on 3/24/26.
//

#include "etc_controller.h"

// Assign appropriate GPIO objects depending on pin parameters
ETCController::ETCController(PinName APPS1_pin, PinName APPS2_pin)
    : apps1(APPS1_pin), apps2(APPS2_pin) {}

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
bool ETCController::in_range(float value, float low, float high) {}
    return value >= low && value <= high;
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

    float v1 = apps1.read() * 3.3f;
    float v2 = apps2.read() * 3.3f;

    apps1_pos = clamp((v1 - APPS1_MIN_VOLTAGE) / (APPS1_MAX_VOLTAGE - APPS1_MIN_VOLTAGE));
    apps2_pos = clamp((v2 - APPS2_MIN_VOLTAGE) / (APPS2_MAX_VOLTAGE - APPS2_MIN_VOLTAGE));

    float avg_pos = (apps1_pos + apps2_pos) / 2.0f;

    torque_demand = static_cast<int16_t>(avg_pos*MAX_TORQUE);

    /*
        Finish the step listed above.
    */

    // Here to simplify this function and readability.
    update_implausibilities();

    if(apps_implausibility || out_of_range_implausibility){
        torque_demand = 0;
    }
}

/*
    Timer based logic for the ETC to be rules compliant. MUST
    include rules T.4.2.4, T.4.2.9 (out of range).
*/
void ETCController::update_implausibilities() {

    float v1 = apps1.read() * 3.3f;
    float v2 = apps2.read() * 3.3f;

    bool mismatch = fabsf(apps1_pos - apps2_pos) > 0.10f;

    constexpr float MARGIN = 0.1f;
    bool out_of_range =
        !in_range(v1, APPS1_MIN_VOLTAGE - MARGIN, APPS1_MAX_VOLTAGE + MARGIN) ||
        !in_range(v2, APPS2_MIN_VOLTAGE - MARGIN, APPS2_MAX_VOLTAGE + MARGIN);

    if (mismatch) {
        if (!apps_mismatch_running) {
            apps_mismatch_timer.reset();
            apps_mismatch_timer.start();
            apps_mismatch_running = true;
        }
    } else {
        apps_mismatch_timer.stop();
        apps_mismatch_running = false;
        apps_implausibility = false;
    }
    if (apps_mismatch_running && apps_mismatch_timer.elapsed_time() > 100ms) {
        apps_implausibility = true;
    }

    if (out_of_range) {
        if (!apps_range_running) {
            apps_range_timer.reset();
            apps_range_timer.start();
            apps_range_running = true;
        }
    } else {
        apps_range_timer.stop();
        apps_range_running = false;
        out_of_range_implausibility = false;
    }
    if (apps_range_running && apps_range_timer.elapsed_time() > 100ms) {
        out_of_range_implausibility = true;
    }
}
