//
// Created by Jackson Pinsonneault on 3/24/26.
//

#include "etc_controller.h"

// Assign appropriate GPIO objects depending on pin parameters
ETCController::ETCController(
    PinName APPS1_pin,
    PinName APPS2_pin
) {}

// Nice function to write which returns a wrapped version of the
// value given between 0 and 1 (-0.1 => 0, 10 => 1, 0.3 => 0.3)
float ETCController::clamp(float value) {}

// Simple function to write which returns a bool of true or false
// depending on whether low <= value <= high is true
bool ETCController::in_range(float value, float low, float high) {}

void ETCController::update_state() {
    state.APPS1_voltage = APPS1_input.read_voltage();
    state.APPS2_voltage = APPS2_input.read_voltage();
    state.BPPS_voltage = BPPS_input.read_voltage();
    state.front_BSE_voltage = front_BSE_input.read_voltage();
    state.rear_BSE_voltage = rear_BSE_input.read_voltage();

    state.front_BSE_pressure = ((state.front_BSE_voltage * 1000.0f - 330.0f) / (3300.0f - 660.0f)) * 2000.0f;
    state.read_BSE_pressure = ((state.rear_BSE_voltage * 1000.0f - 330.0f) / (3300.0f - 660.0f)) * 2000.0f;

    state.APPS1_position = (clamp(
        (state.APPS1_voltage - APPS1_MIN_VOLTAGE) / (APPS1_MAX_VOLTAGE - APPS1_MIN_VOLTAGE)
    ) - PEDAL_DEADZONE_PERCENTAGE) / (1 - 2*PEDAL_DEADZONE_PERCENTAGE);
    state.APPS2_position = (clamp(
        (state.APPS2_voltage - APPS2_MIN_VOLTAGE) / (APPS2_MAX_VOLTAGE - APPS2_MIN_VOLTAGE)
    ) - PEDAL_DEADZONE_PERCENTAGE) / (1 - 2*PEDAL_DEADZONE_PERCENTAGE);
    state.BPPS_position =
        clamp((state.BPPS_voltage - BPPS_MIN_VOLTAGE) / (BPPS_MAX_VOLTAGE - BPPS_MIN_VOLTAGE));
    state.APPS_position_avg = (state.APPS1_position + state.APPS2_position) / 2.0f;

    update_implaus();

    state.APPS_position_avg = accelerator_mapping(state.APPS_position_avg);

    // const float APPS_position_within_deadzone = (state.APPS_position_avg - PEDAL_DEADZONE_PERCENTAGE / (1 - 2*PEDAL_DEADZONE_PERCENTAGE));
    // const float BPPS_position_within_deadzone = (state.BPPS_position - PEDAL_DEADZONE_PERCENTAGE / (1 - 2*PEDAL_DEADZONE_PERCENTAGE));
    if (!REGEN_FORCE_DISABLE && state.regen_mode != 0) {
        state.unfiltered_motor_torque = static_cast<int16_t>(state.APPS_position_avg * MAX_TORQUE) - static_cast<int16_t>(state.BPPS_position * MAX_REGEN_TORQUE);
    } else {
        state.unfiltered_motor_torque = static_cast<int16_t>(state.APPS_position_avg * MAX_TORQUE);
    }

    // if (!TRACTION_CONTROL_FORCE_DISABLE && state.traction_mode != 0 && state.motor_torque.read() > 0) {
    //   // state.unfiltered_motor_torque = static_cast<int16_t>(state.motor_torque.read() * state.tc_torque_reduction_factor);
    // }

    // state.motor_torque.sample(state.unfiltered_motor_torque); // smooth out motor torque

    state.brakelight_enabled = (state.front_BSE_pressure > 30);
    brakelight.write(state.brakelight_enabled);

    state.solenoid_open = SOLENOID_FORCE_OPEN ? true : state.regen_allowed;
    solenoid.write(!state.solenoid_open);

    state.rtd_button_pressed = rtd_button.read();
}

void ETCController::update_implaus() {
    bool implaus_APPS_deviation =
        std::abs(state.APPS1_position - state.APPS2_position) > MAX_APPS_POSITION_DEVIATION;
    bool implaus_APPS_range =
        !in_range(state.APPS1_voltage, APPS1_MIN_VOLTAGE, APPS1_MAX_VOLTAGE)
        || !in_range(state.APPS2_voltage, APPS2_MIN_VOLTAGE, APPS2_MAX_VOLTAGE);
    bool implaus_BPPS_range = !in_range(state.BPPS_voltage, BPPS_MIN_VOLTAGE, BPPS_MAX_VOLTAGE);
    bool implaus_BSE_range =
        !in_range(state.front_BSE_voltage, FRONT_BSE_MIN_VOLTAGE, FRONT_BSE_MAX_VOLTAGE)
        || !in_range(state.rear_BSE_voltage, REAR_BSE_MIN_VOLTAGE, REAR_BSE_MAX_VOLTAGE);
    // APPS / Brake Pedal Plausibility Check:
    // "With accelerator > 25%, press brake pedal. Axle MUST stop"
    // Note: brake pedal range is up for interpretation
    bool implaus_brake_and_accel = (state.front_BSE_pressure > 30) && state.APPS_position_avg > 0.25f;

    update_implaus_timer(
        implaus_APPS_deviation_timer,
        implaus_APPS_deviation_timer_running,
        implaus_APPS_deviation,
        state.implaus_APPS_deviation
    );
    update_implaus_timer(
        implaus_APPS_range_timer,
        implaus_APPS_range_timer_running,
        implaus_APPS_range,
        state.implaus_APPS_range
    );
    update_implaus_timer(
        implaus_BPPS_range_timer,
        implaus_BPPS_range_timer_running,
        implaus_BPPS_range,
        state.implaus_BPPS_range
    );
    update_implaus_timer(
        implaus_BSE_range_timer,
        implaus_BSE_range_timer_running,
        implaus_BSE_range,
        state.implaus_BSE_range
    );

    // "axle may turn again once < 5% pedal position."
    if (state.implaus_brake_and_accel && state.APPS_position_avg < 0.05f) {
        state.implaus_brake_and_accel = false;
    }
    if (implaus_brake_and_accel) {
        state.implaus_brake_and_accel = true;
    }

    if (state.implaus_APPS_deviation
        || state.implaus_APPS_range
        || state.implaus_BPPS_range
        || state.implaus_brake_and_accel
        || state.implaus_BSE_range
        || !state.ready_to_drive)
    {
        state.motor_enabled = false;
    } else {
        state.motor_enabled = true;
    }
}
