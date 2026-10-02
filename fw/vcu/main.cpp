#include "etc_controller.h"
#include "mbed.h"
#include <cstdio>

ETCController etc{PinName PC_1, PinName PC_2};

CAN can{PB_8, PB_9, 500000};

// Predefined for use in main()
void send_etc_CAN_messages();
void send_sme_CAN_messages();

int main() {
    printf("Hello World!!\n");

    /*
        Make send_CAN messages loop consistently
        at 20hz (20 messages / second)
    */



    // No need to edit this while loop
    while (true) {
        // Must implement in etc/ subfolder
        etc.update_state();
    }

    return 0;
}

/* 
    Must send the VCU_TPDO_STATUS CAN message with
    VCU_ETC_READY_TO_DRIVE & VCU_ETC_MOTOR_ENABLED
    set to 1, and VCU_ETC_IMPLAUS_APPS_OUT_OF_RANGE
    & VCU_ETC_IMPLAUS_APPS_DEVIATION properly added.
*/
void send_etc_CAN_messages() {
    // 1 = VCU_ETC_READY_TO_DRIVE
    // 2 = VCU_ETC_MOTOR_ENABLED
    // 4 = VCU_ETC_IMPLAUS_APPS_OUT_OF_RANGE
    // 6 = VCU_ETC_IMPLAUS_APPS_DEVIATION
    uint8_t message[8] = {0};

    message[0] = 1
                | 1 << 1
                | etc.implaus_deviation << 4
                | etc.implaus_out_of_range << 6;

    // 0x193 ID is VCU_TPDO_STATUS
    can.send(CANMessage(0x193, message, 8));
}

/*
    Must send the SME_RPDO_Throttle_Demand CAN
    message with SME_THROTL_TorqueDemand set to the
    torque demand determined by the ETC.
*/
void send_sme_CAN_messages() {
    // 0-15 = SME_THROTL_TorqueDemand

    uint8_t message[8] = {0};
    message[0] |= etc.motor_torque_demand;
    message[1] |= (etc.motor_torque_demand >> 8);

    // 0x186 ID is SME_RPDO_Throttle_Demand
    can.send(CANMessage(0x186, message, 8));
}
