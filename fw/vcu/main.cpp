#include "etc_controller.h"
#include "mbed.h"
#include <cstdio>

EventQueue etc_queue;
Thread etc_thread;

AnalogIn steering_position{PC_5};
DigitalIn bspd_fault{PA_2};
DigitalIn bspd_shutdown_out{PA_3};

CAN canP{PB_8, PB_9, 500000};
CAN canD{PB_5, PB_6, 1000000};
ETCController etc{PC_1, PC_2, PC_3, PA_1, PA_0, PC_13, PC_0, PA_7, PB_1, PC_4}; // add imu at end
ETCState& etc_state = etc.state;

void send_etc_CAN_messages();
void send_sme_CAN_messages_powertrain();
void send_sme_CAN_messages_data();

namespace {
constexpr float RAD_TO_DEG = 57.2957795f;
}

int main() {
    printf("Hello World!!\n");

    etc_queue.call_every(50ms, &send_etc_CAN_messages);
    etc_queue.call_every(40ms, &send_sme_CAN_messages_powertrain);
    etc_queue.call_every(80ms, &send_sme_CAN_messages_data);
    etc_thread.start(callback(&etc_queue, &EventQueue::dispatch_forever));

    CANMessage rx;
    while (true) {
        if (canP.read(rx)) {
            switch (rx.id) {
            case 0x391: {
            }
            }
        }

        etc.update_state();
    }

    return 0;
}

void send_etc_CAN_messages() {
    uint8_t tpdo_pedal_travel[8] = {0};
    uint16_t APPS1_scaled_voltage = static_cast<uint16_t>(etc_state.APPS1_voltage * 1000);
    uint16_t APPS2_scaled_voltage = static_cast<uint16_t>(etc_state.APPS2_voltage * 1000);
    uint16_t BPPS_scaled_voltage = static_cast<uint16_t>(etc_state.BPPS_voltage * 1000);
    tpdo_pedal_travel[0] = APPS1_scaled_voltage & 0xFF;
    tpdo_pedal_travel[1] = APPS1_scaled_voltage >> 8;
    tpdo_pedal_travel[2] = APPS2_scaled_voltage & 0xFF;
    tpdo_pedal_travel[3] = APPS2_scaled_voltage >> 8;
    tpdo_pedal_travel[4] = BPPS_scaled_voltage & 0xFF;
    tpdo_pedal_travel[5] = BPPS_scaled_voltage >> 8;
    tpdo_pedal_travel[6] = static_cast<uint8_t>(etc_state.APPS_position_avg * 100);
    tpdo_pedal_travel[7] = static_cast<uint8_t>(etc_state.BPPS_position * 100);

    uint8_t tpdo_status[8] = {0};
    uint16_t front_BSE_pressure = static_cast<uint16_t>(etc_state.front_BSE_pressure);
    uint16_t read_BSE_pressure = static_cast<uint16_t>(etc_state.read_BSE_pressure);
    uint16_t steering_position_mv = steering_position.read_voltage() * 1000;
    tpdo_status[0] = etc_state.ready_to_drive
                     | (etc_state.motor_enabled << 1)
                     | (etc_state.rtd_button_pressed << 2)
                     | (etc.battery_precharged << 3)
                     | (etc_state.implaus_APPS_range << 4)
                     | (etc_state.implaus_BPPS_range << 5)
                     | (etc_state.implaus_APPS_deviation << 6)
                     | (etc_state.implaus_BSE_range << 7);
    tpdo_status[1] = etc_state.implaus_brake_and_accel
                     | (etc_state.reversing << 1)
                     | (etc_state.brakelight_enabled << 2)
                     | (etc_state.regen_allowed << 3)
                     | (etc_state.solenoid_open << 4)
                     | (bspd_fault.read() << 6)
                     | (bspd_shutdown_out.read() << 7);
    tpdo_status[2] = front_BSE_pressure & 0xFF;
    tpdo_status[3] = front_BSE_pressure >> 8;
    tpdo_status[4] = read_BSE_pressure & 0xFF;
    tpdo_status[5] = read_BSE_pressure >> 8;
    tpdo_status[6] = steering_position_mv & 0xFF;
    tpdo_status[7] = steering_position_mv >> 8;

    CANMessage msg1{402, tpdo_pedal_travel, 8};
    CANMessage msg2{403, tpdo_status, 8};
    canD.write(msg1);
    canD.write(msg2);
}

void send_sme_CAN_messages_powertrain() {
    etc.update_mbb_alive();

    uint8_t tpdo_throttle_demand[8];
    tpdo_throttle_demand[0] = etc_state.unfiltered_motor_torque & 0xFF;
    tpdo_throttle_demand[1] = etc_state.unfiltered_motor_torque >> 8;
    tpdo_throttle_demand[2] = etc_state.MAX_SPEED & 0xFF;
    tpdo_throttle_demand[3] = etc_state.MAX_SPEED >> 8;
    tpdo_throttle_demand[4] = (!etc_state.reversing)
                              | (etc_state.reversing << 1) 
                              | (etc_state.motor_enabled << 3);
    tpdo_throttle_demand[5] = etc_state.mbb_alive;

    uint8_t tpdo_max_currents[8];
    tpdo_max_currents[0] = etc_state.CHARGE_CURRENT_LIMIT & 0xFF;
    tpdo_max_currents[1] = etc_state.CHARGE_CURRENT_LIMIT >> 8;
    tpdo_max_currents[2] = etc_state.DISCHARGE_CURRENT_LIMIT & 0xFF;
    tpdo_max_currents[3] = etc_state.DISCHARGE_CURRENT_LIMIT >> 8;

    CANMessage throttle_msg{390, tpdo_throttle_demand, 8};
    CANMessage currents_msg{646, tpdo_max_currents, 8};

    canP.write(throttle_msg);
    canP.write(currents_msg);
    ThisThread::sleep_for(5ms);
    canD.write(throttle_msg);
    canD.write(currents_msg);
}

void send_sme_CAN_messages_data() {
    // Update traction control reduction factor synchronized with torque commands

    uint8_t tpdo_throttle_demand[8];
    tpdo_throttle_demand[0] = etc_state.unfiltered_motor_torque & 0xFF;
    tpdo_throttle_demand[1] = etc_state.unfiltered_motor_torque >> 8;
    tpdo_throttle_demand[2] = etc_state.MAX_SPEED & 0xFF;
    tpdo_throttle_demand[3] = etc_state.MAX_SPEED >> 8;
    tpdo_throttle_demand[4] = (!etc_state.reversing)
                              | (etc_state.reversing << 1) 
                              | (etc_state.motor_enabled << 3);
    tpdo_throttle_demand[5] = etc_state.mbb_alive;

    uint8_t tpdo_max_currents[8];
    tpdo_max_currents[0] = etc_state.CHARGE_CURRENT_LIMIT & 0xFF;
    tpdo_max_currents[1] = etc_state.CHARGE_CURRENT_LIMIT >> 8;
    tpdo_max_currents[2] = etc_state.DISCHARGE_CURRENT_LIMIT & 0xFF;
    tpdo_max_currents[3] = etc_state.DISCHARGE_CURRENT_LIMIT >> 8;

    CANMessage throttle_msg{390, tpdo_throttle_demand, 8};
    CANMessage currents_msg{646, tpdo_max_currents, 8};

    canD.write(throttle_msg);
    canD.write(currents_msg);
}

void send_sync() { canP.write(CANMessage{0x80, (uint8_t*)nullptr, 0}); }
