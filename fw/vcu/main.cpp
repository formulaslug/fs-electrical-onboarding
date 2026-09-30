#include "etc_controller.h"
#include "mbed.h"
#include <cstdio>

// APPS_1, APPS_2 from the fs-4 VCU schematic
ETCController etc{PC_1, PC_2};

CAN can{PB_8, PB_9, 500000};

constexpr unsigned int SME_RPDO_THROTTLE_DEMAND_ID = 390; // 0x186
constexpr unsigned int VCU_TPDO_STATUS_ID = 403;          // 0x193
constexpr int16_t SME_MAX_SPEED_RPM = 7500;

constexpr auto CAN_SEND_PERIOD = 50ms;     // 20 Hz
constexpr auto DEBUG_PRINT_PERIOD = 500ms; // 2 Hz

// Not a Ticker: CAN::write() can't run in an ISR
EventQueue can_queue;
Thread can_thread{osPriorityAboveNormal};

// Predefined for use in main()
void send_CAN_messages();
void send_etc_CAN_messages();
void send_sme_CAN_messages();
void print_debug();

int main() {
    printf("Hello World!!\n");

    /*
        Make send_CAN messages loop consistently
        at 20hz (20 messages / second)
    */

    can_queue.call_every(CAN_SEND_PERIOD, send_CAN_messages);
    can_queue.call_every(DEBUG_PRINT_PERIOD, print_debug);
    can_thread.start(callback(&can_queue, &EventQueue::dispatch_forever));

    bool motor_was_enabled = false;

    // No need to edit this while loop
    while (true) {
        // Must implement in etc/ subfolder
        etc.update_state();

        // Send zero torque right away (T.4.2.5)
        if (motor_was_enabled && !etc.motor_enabled) {
            can_queue.call(send_CAN_messages);
        }
        motor_was_enabled = etc.motor_enabled;
    }

    return 0;
}

void send_CAN_messages() {
    send_sme_CAN_messages();  // first, so it always gets a TX mailbox
    send_etc_CAN_messages();
}

/* 
    Must send the VCU_TPDO_STATUS CAN message with
    VCU_ETC_READY_TO_DRIVE & VCU_ETC_MOTOR_ENABLED
    set to 1, and VCU_ETC_IMPLAUS_APPS_OUT_OF_RANGE
    & VCU_ETC_IMPLAUS_APPS_DEVIATION properly added.
*/
void send_etc_CAN_messages() {
    uint8_t data[8] = {0};

    data[0] = (1 << 0)                                                   // READY_TO_DRIVE
            | (1 << 1)                                                   // MOTOR_ENABLED
            | (static_cast<uint8_t>(etc.implaus_apps_out_of_range) << 4) // IMPLAUS_APPS_OUT_OF_RANGE
            | (static_cast<uint8_t>(etc.implaus_apps_deviation) << 6);   // IMPLAUS_APPS_DEVIATION

    can.write(CANMessage{VCU_TPDO_STATUS_ID, data, 8});
}

/*
    Must send the SME_RPDO_Throttle_Demand CAN
    message with SME_THROTL_TorqueDemand set to the
    torque demand determined by the ETC.
*/
void send_sme_CAN_messages() {
    static uint8_t mbb_alive = 0;  // only advances on a sent frame
    uint8_t next_mbb_alive = (mbb_alive + 1) & 0x0F;

    bool power_ready = etc.motor_enabled;
    uint16_t torque = static_cast<uint16_t>(power_ready ? etc.torque_demand : 0);
    uint16_t max_speed = static_cast<uint16_t>(SME_MAX_SPEED_RPM);

    uint8_t data[8] = {0};
    data[0] = torque & 0xFF;                                        // TorqueDemand
    data[1] = (torque >> 8) & 0xFF;
    data[2] = max_speed & 0xFF;                                     // MaxSpeed
    data[3] = (max_speed >> 8) & 0xFF;
    data[4] = (1 << 0) | (static_cast<uint8_t>(power_ready) << 3); // Forward, PowerReady
    data[5] = next_mbb_alive;                                       // MBB_Alive

    if (can.write(CANMessage{SME_RPDO_THROTTLE_DEMAND_ID, data, 8})) {
        mbb_alive = next_mbb_alive;
    }
}

void print_debug() {
    printf("APPS1 %.3f V %.3f | APPS2 %.3f V %.3f | pedal %.3f | torque %d | dev %d oor %d | CAN tx err %d\n",
           etc.apps1_voltage, etc.apps1_position,
           etc.apps2_voltage, etc.apps2_position,
           etc.pedal_position, etc.torque_demand,
           etc.implaus_apps_deviation, etc.implaus_apps_out_of_range,
           can.tderror());
}
